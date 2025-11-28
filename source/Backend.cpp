#include "Backend.h"

#include <QDir>
#include <QFile>
#include <thread>
#include <QtConcurrent/QtConcurrentRun>
#include <QThreadPool>
#include <QGuiApplication>
#include <QJsonArray>

#include "utils.h"
#include "DataParser.h"
#include "Data.h"
#include "DataBuilder.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
    , m_data{nullptr}
{

}

Data *Backend::getData() const
{
    return m_data;
}

void Backend::initialize()
{
    qDebug() << "starting initializer";

    /// start function asynchronysly;
    QObject::connect(this, &Backend::startInitialization, this, &Backend::downloadData, Qt::SingleShotConnection);
    QFuture<void> future = QtConcurrent::run([this](){
        emit this->startInitialization();
    });
}



void Backend::downloadData()
{
    qDebug() << "loading Data...";

    emit this->dataStatus("Downloading input json...");

    QDir networkDir( NETWORK_PATH );
    if(!networkDir.removeRecursively())
    {
        qWarning() << "Can't clear network directory";
    }

    QObject::connect(
        &m_networkDownloader, &NetworkDownlaoder::fileDownloaded,
        this, &Backend::onInputDataDownloaded,
        Qt::SingleShotConnection);

    QObject::connect(
        &m_networkDownloader, &NetworkDownlaoder::fileDownloadingFailed,
        this, &Backend::onInputDataDownloadingFailed,
        Qt::SingleShotConnection);

    m_networkDownloader.addFileToDownload( INPUT_DATA_URL, NETWORK_PATH INPUT_DATA_FILE_NAME );
    m_networkDownloader.startDownloads();
}

void Backend::onInputDataDownloaded(QString outputFile)
{
    /// disconnect not used (oposite) connection
    QObject::disconnect(
        &m_networkDownloader, &NetworkDownlaoder::fileDownloadingFailed,
        this, &Backend::onInputDataDownloadingFailed);

    qDebug() << "Downloaded!" << outputFile;

    emit this->dataStatus("Parsing data...");
    QGuiApplication::processEvents();


    /// Clear cache directory
    QDir cacheDir( CACHE_PATH );
    if(!cacheDir.removeRecursively())
        qWarning() << "\t" "Unable to remove all files in cache!";

    if(!cacheDir.mkpath("."))
        qWarning() << "\t" "Unable to create new cache directory!";

    /// Move Input File and Urls Hash Map
    if(!QFile::rename( NETWORK_PATH INPUT_DATA_FILE_NAME, CACHE_PATH INPUT_DATA_FILE_NAME ))
            qWarning() << "\t" "Unable to move 'Input data file' to cache location!";

    /// check if file exist
    if(!QFile::exists( CACHE_PATH INPUT_DATA_FILE_NAME ))
    {
        qWarning() << "\t" "Moving 'Input data file' failed!";
        emit this->dataError("Internal data error, can't create a cache!");
        return;
    }

    /// process input file
    StrStrMap urlsHashMap;
    try
    {
        QStringList urls = DataParser::collectUrls( CACHE_PATH INPUT_DATA_FILE_NAME );
        urlsHashMap = DataParser::createUrlFilesHashMap(urls);
        DataParser::saveUrlFilesHashMap(urlsHashMap, CACHE_PATH URLS_HASH_MAP_FILE_NAME);
    }
    catch(const QString &e)
    {
        qWarning() << "Unable to collect urls: " << e;
    }


    emit this->dataStatus("Downloading images...");

    /// start downloading images
    QObject::connect(
        &m_networkDownloader, &NetworkDownlaoder::allFilesDownloadingEnded,
        this, &Backend::onImagesDownloadingFinished, Qt::SingleShotConnection);

    for(auto i=urlsHashMap.keyBegin(); i!=urlsHashMap.keyEnd(); ++i)
    {
        m_networkDownloader.addFileToDownload(
            *i, (NETWORK_IMAGES_PATH) + urlsHashMap[*i]);
    }
    m_networkDownloader.startDownloads();

}

void Backend::onImagesDownloadingFinished(int filesToDownload, int downloadedFiles)
{
    qDebug() << QString::asprintf("downloaded %d/%d", downloadedFiles, filesToDownload)
                    .toStdString().c_str();

    /// Move images
    if(!QFile::rename( NETWORK_IMAGES_PATH, CACHE_IMAGES_PATH ))
        qWarning() << "Unable to move images folder from network to cache";


    /// load cache
    try
    {
        this->loadCache();
    }
    catch(const QString &e)
    {
        /// emit toast info
        emit this->showToast("Failed loading cache memory!");

        emit this->dataError(e);
        return;
    }

    /// emit toast info
    emit this->showToast("Data Downloaded");

    emit this->dataLoaded();
}


void Backend::onInputDataDownloadingFailed()
{
    /// disconnect not used (oposite) connection
    QObject::disconnect(
        &m_networkDownloader, &NetworkDownlaoder::fileDownloaded,
        this, &Backend::onInputDataDownloaded);

    qDebug() << "Download failed!";

    /// chceck if cache exist
    if(!QFile::exists(CACHE_PATH INPUT_DATA_FILE_NAME))
    {
        /// emit toast info
        emit this->showToast("Download failed! No cache yet!");

        emit this->dataError("No Data, please provide an internet connection");
        return;
    }

    /// load cache
    try
    {
        this->loadCache();
    }
    catch(const QString &e)
    {
        /// emit toast info
        emit this->showToast("Download failed! Failed loading cache!");

        emit this->dataError(e);
        return;
    }

    /// emit toast info
    emit this->showToast("Download failed! Using cache.");

    emit this->dataLoaded();
}

void Backend::loadCache()
{
    QJsonDocument jsonDoc;
    try
    {
        jsonDoc = DataParser::readJsonDocFile( CACHE_PATH INPUT_DATA_FILE_NAME);

        if(!jsonDoc.isArray())
        {
            qDebug() << "Invalid json Format (1)";
            throw QString("Invalid json Format (1)");
        }
    }
    catch(const QString &e)
    {
        throw QString("Internal data error, can't read input data file from cache!");
    }

    /// remove data if exist
    if(m_data) delete m_data;
    m_data = nullptr;

    /// buld data from input data
    m_data =  DataBuilder::buildData(jsonDoc.array(), this);
    emit this->dataChanged();

    /// resolve urls, image url to image path
    try
    {
        DataParser::resolveDataThumbnailPaths(CACHE_PATH URLS_HASH_MAP_FILE_NAME, m_data);
    }
    catch(const QString &e)
    {
        qWarning() << "Unable to resolve urls from data: " << e;
    }
}
