#include "Backend.h"

#include <QDir>
#include <thread>
#include <QtConcurrent/QtConcurrentRun>
#include <QThreadPool>
#include <QGuiApplication>

#include "utils.h"
#include "DataParser.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
{

}

void Backend::initialize()
{
    qDebug() << "starting initializer";

    /// start function asynchronysly;
    QObject::connect(this, &Backend::startInitialization, this, &Backend::loadData, Qt::SingleShotConnection);
    QFuture<void> future = QtConcurrent::run([this](){
        emit this->startInitialization();
    });
}



void Backend::loadData()
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
        this, &Backend::inputDataDownloaded,
        Qt::SingleShotConnection);

    QObject::connect(
        &m_networkDownloader, &NetworkDownlaoder::fileDownloadingFailed,
        this, &Backend::inputDataDownloadFailed,
        Qt::SingleShotConnection);

    m_networkDownloader.addFileToDownload( INPUT_DATA_URL, NETWORK_PATH INPUT_DATA_FILE_NAME );
    m_networkDownloader.startDownloads();
}

void Backend::inputDataDownloaded(QString outputFile)
{
    /// disconnect not used (oposite) connection
    QObject::disconnect(
        &m_networkDownloader, &NetworkDownlaoder::fileDownloadingFailed,
        this, &Backend::inputDataDownloadFailed);

    qDebug() << "Downloaded!" << outputFile;

    emit this->dataStatus("Parsing data...");
    QGuiApplication::processEvents();

    /// process input file
    QStringList urls = DataParser::collectUrls( NETWORK_PATH INPUT_DATA_FILE_NAME );
    StrStrMap urlsHashMap = DataParser::createUrlFilesHashMap(urls);
    DataParser::saveUrlFilesHashMap(urlsHashMap, NETWORK_PATH URLS_HASH_MAP_FILE_NAME);

    emit this->dataStatus("Downloading images...");

    /// start downloading images
    QObject::connect(
        &m_networkDownloader, &NetworkDownlaoder::allFilesDownloaded,
        this, &Backend::imagesDownloaded, Qt::SingleShotConnection);

    for(auto i=urlsHashMap.keyBegin(); i!=urlsHashMap.keyEnd(); ++i)
    {
        m_networkDownloader.addFileToDownload(
            *i, (NETWORK_IMAGES_PATH) + urlsHashMap[*i]);
    }
    m_networkDownloader.startDownloads();

}

void Backend::imagesDownloaded()
{
    emit this->dataLoaded();

    /// move downloaded data to cache

    /// load cache
}



void Backend::inputDataDownloadFailed(QString details)
{
    /// disconnect not used (oposite) connection
    QObject::disconnect(
        &m_networkDownloader, &NetworkDownlaoder::fileDownloaded,
        this, &Backend::inputDataDownloaded);

    qDebug() << "Download failed!";

    /// emit toast info
    emit this->showToast("Download failed!");

    QString errorDetails = details;


    /// chceck if cache exist
    /// if not emit
    emit this->dataError("No Data, please provide an internet connection");


    /// load cache

}
