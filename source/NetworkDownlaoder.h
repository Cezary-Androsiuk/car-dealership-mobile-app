#ifndef NETWORKDOWNLAODER_H
#define NETWORKDOWNLAODER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMap>

class NetworkDownlaoder : public QObject
{
    Q_OBJECT
public:
    explicit NetworkDownlaoder(QObject *parent = nullptr);

public:
    void addFileToDownload(QString url, QString outputFile);
    void startDownloads();

private slots:
    void handleReply(QNetworkReply *reply);

private:
    void saveDataToFile(const QByteArray &rawData, const QString &outputFile) const;
    void handleProgressCounterChanged();

signals:
    void fileDownloaded(QString outputFile);
    void fileDownloadingFailed(QString details);

    void allFilesDownloadingEnded(int filesToDownload, int downloadedFiles);

private:
    QNetworkAccessManager m_netAccessManager;

    QMap<QNetworkRequest *, QString> m_requestsInQueue; /// [request, outputFile]
    QMap<QNetworkReply *, QString> m_repliesInProcess; /// [reply, outputFile]

    int m_filesToDownload;
    int m_downloadedFiles;
};

#endif // NETWORKDOWNLAODER_H
