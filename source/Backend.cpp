#include "Backend.h"

#include <QDir>
#include <thread>
#include <QtConcurrent/QtConcurrentRun>
#include <QThreadPool>

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

    // emit this->dataLoaded();
    // emit this->noDataFound();
    // emit this->dataError("message");

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

    QStringList urls = {
        "https://cdn.pixabay.com/photo/2015/04/23/22/00/tree-736885_1280.jpg",
        "https://ui-avatars.com/api/name=Jan+Kowalski&background=random.png?v=1.2",
        "https://upload.wikimedia.org/wikipedia/commons/f/f7/Stack_Overflow_logo.svg",
        "https://www.mojastrona.pl/gallery/Moje%20Wakacje%202024/Zdjęcie%20z%20plaży%20(1).jpeg",
        "https://images.unsplash.com/photo-1518791841217-8f162f1e1131?ixlib=rb-4.0.3&ixid=M3wxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D&auto=format&fit=crop"
    };

    StrStrMap map = DataParser::createUrlFilesHashMap(urls);

    qDebug() << "map:";
    for(const auto &key : map.keys())
    {
        qDebug() << key << " : " << map[key];
    }


    m_networkDownloader.addFileToDownload( INPUT_DATA_URL, NETWORK_PATH INPUT_DATA_FILE_NAME );
    m_networkDownloader.startDownloads();
}

void Backend::inputDataDownloaded(QString outputFile)
{
    qDebug() << "Downloaded!" << outputFile;

    /// process input file
    QStringList urls = DataParser::collectUrls( NETWORK_PATH INPUT_DATA_FILE_NAME );
    StrStrMap urlsHashMap = DataParser::createUrlFilesHashMap(urls);
    DataParser::saveUrlFilesHashMap(urlsHashMap, NETWORK_PATH URLS_HASH_MAP_FILE_NAME);

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
}



void Backend::inputDataDownloadFailed(QString details)
{
    qDebug() << "Download failed!" << details;
    /// emit toast info
    emit this->dataError(details);
}
