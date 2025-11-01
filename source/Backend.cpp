#include "Backend.h"

#include "utils.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
{

}

void Backend::loadData()
{
    // emit this->dataLoaded();
    // emit this->noDataFound();
    // emit this->dataError("message");

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

    m_networkDownloader.downloadFile( INPUT_DATA_URL, INPUT_DATA_FILE_PATH );
}
