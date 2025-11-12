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

    QObject::connect(this, &NetworkDownlaoder::fileDownloaded, this, &NetworkDownlaoder::handleProgressCounterChanged);
    QObject::connect(this, &NetworkDownlaoder::fileDownloadingFailed, this, &NetworkDownlaoder::handleProgressCounterChanged);
}

void NetworkDownlaoder::addFileToDownload(QString url, QString outputFile)
{
    m_requestsInQueue[new QNetworkRequest( QUrl(url) )] = outputFile;
}

void NetworkDownlaoder::startDownloads()
{
    if(m_requestsInQueue.empty())
    {
        qWarning() << "Nothing added to download!";
        emit this->allFilesDownloaded();
    }

    for(auto i=m_requestsInQueue.keyBegin(); i!=m_requestsInQueue.keyEnd(); ++i)
    {
        QNetworkRequest *request = *i;
        /// following code will emit signal handled by NetworkDownlaoder::handleReply
        QNetworkReply *reply = m_netAccessManager.get(*request);

        m_repliesInProcess[reply] = m_requestsInQueue[request];
        delete request;
    }

    m_requestsInQueue.clear();
}


void NetworkDownlaoder::handleReply(QNetworkReply *reply)
{
    qDebug() << "reply received\n";

    /// get outputFile path
    QString outputFile = m_repliesInProcess[reply]; /// need to contain the value
    m_repliesInProcess.remove(reply);

    if(reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "Downloading Failed! Reason: " << reply->errorString();
        emit this->fileDownloadingFailed( "Downloading Failed! Reason: " + reply->errorString() );
        reply->deleteLater();
        return;
    }

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
    /// create path
    QFileInfo fileInfo(outputFile);
    QDir dir(fileInfo.absoluteDir());
    if(!dir.exists())
    {
        if(!dir.mkpath("."))
        {
            qWarning() << "Can't create info file output path" << dir;
            throw "Can't create info file output path";
        }
    }

    /// create file
    QFile file(outputFile);
    if(!file.open(QFile::WriteOnly))
    {
        qWarning() << "Can't open file to write" << outputFile;
        throw "Can't open file to write";
    }

    /// save file
    file.write(rawData);
    file.close();
}

void NetworkDownlaoder::handleProgressCounterChanged()
{
    if(m_repliesInProcess.isEmpty())
    {
        emit this->allFilesDownloaded();
    }
}

