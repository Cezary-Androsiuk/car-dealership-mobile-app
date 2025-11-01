#include "NetworkDownlaoder.h"

#include <QFileInfo>
#include <QFile>
#include <QUrl>
#include <QDir>
#include <QDebug>
#include <exception>

#include "utils.h"

NetworkDownlaoder::NetworkDownlaoder(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&m_netAccessManager, &QNetworkAccessManager::finished, this, &NetworkDownlaoder::handleReply);
}

void NetworkDownlaoder::downloadFile(QString url, QString outputFile)
{
    /// following code will emit signal handled by NetworkDownlaoder::handleReply
    QNetworkReply *reply = m_netAccessManager.get(
        QNetworkRequest( QUrl(url) )
    );

    m_repliesInProcess[reply] = outputFile;
}


void NetworkDownlaoder::handleReply(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "Downloading Failed! Reason: " << reply->errorString();
        emit this->fileDownloadingFailed( "Downloading Failed! Reason: " + reply->errorString() );
        reply->deleteLater();
        return;
    }

    /// get outputFile path
    QString outputFile = m_repliesInProcess[reply]; /// need to contain the value
    m_repliesInProcess.remove(reply);

    /// read data from reply
    QByteArray rawData = reply->readAll();
    reply->deleteLater();

    /// save data to file
    try
    {
        this->saveDataToFile(rawData, outputFile);
    }
    catch (const std::exception &e)
    {
        qWarning() << "Saving File Failed! Reason: "<< e.what();
        emit this->fileDownloadingFailed(
            QString::asprintf("Saving File Failed! Reason: %s", e.what()) );
        return;
    }

    emit this->fileDownloaded(outputFile);
}

void NetworkDownlaoder::saveDataToFile(const QByteArray &rawData, const QString &outputFile) const
{
    QFileInfo fileInfo(INPUT_DATA_FILE_PATH);
    QDir dir(fileInfo.absoluteDir());
    if(!dir.exists())
    {
        if(!dir.mkpath("."))
        {
            qWarning() << "Can't create info file output path" << dir;
            throw "Can't create info file output path";
        }
    }

    QFile file(INPUT_DATA_FILE_PATH);
    if(!file.open(QFile::WriteOnly))
    {
        qWarning() << "Can't open file to write" << INPUT_DATA_FILE_PATH;
        throw "Can't open file to write";
    }

    file.write(rawData);
    file.close();
}
