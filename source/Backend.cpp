#include "Backend.h"

#include <QDir>
#include <thread>
#include <QtConcurrent/QtConcurrentRun>
#include <QThreadPool>

#include "utils.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
{

}

void Backend::initialize()
{
    /// start function asynchronysly;
    QObject::connect(this, &Backend::startInitialization, this, &Backend::loadData, Qt::SingleShotConnection);
    QFuture<void> future = QtConcurrent::run([this](){
        emit this->startInitialization();
    });
}



void Backend::loadData()
{
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

    m_networkDownloader.downloadFile( INPUT_DATA_URL, NETWORK_PATH INPUT_DATA_FILE_NAME );
}

void Backend::inputDataDownloaded(QString outputFile)
{
    qDebug() << "Downloaded!" << outputFile;

    // process input file
    // create image names hash map
    // download images
    // react on allFilesDownloaded signal

    emit this->dataLoaded();
}

void Backend::inputDataDownloadFailed(QString details)
{
    qDebug() << "Download failed!" << details;
    /// emit toast info
    emit this->dataError(details);
}
