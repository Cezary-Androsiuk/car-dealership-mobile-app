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
    QObject::connect(this, &Backend::s, this, &Backend::loadData, Qt::SingleShotConnection);
    QFuture<void> future = QtConcurrent::run([this](){
        emit this->s();
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
        this, [&](QString outputFile){

        qDebug() << "Downloaded!" << outputFile;
        emit this->dataLoaded();
    }, Qt::SingleShotConnection);

    QObject::connect(
        &m_networkDownloader, &NetworkDownlaoder::fileDownloadingFailed,
        this, [&](QString details){
        qDebug() << "Download failed!" << details;
        emit this->dataError(details);
    }, Qt::SingleShotConnection);


    std::this_thread::sleep_for(std::chrono::seconds(5));

    m_networkDownloader.downloadFile( INPUT_DATA_URL, INPUT_DATA_FILE_PATH );
}
