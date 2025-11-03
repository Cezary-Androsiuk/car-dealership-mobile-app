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

public slots:
    void downloadFile(QString url, QString outputFile);

private slots:
    void handleReply(QNetworkReply *reply);

private:
    void saveDataToFile(const QByteArray &rawData, const QString &outputFile) const;
    void handleProgressCounterChanged();

signals:
    void fileDownloaded(QString outputFile);
    void fileDownloadingFailed(QString details);

    void allFilesDownloaded();

private:
    QNetworkAccessManager m_netAccessManager;
    QMap<QNetworkReply *, QString> m_repliesInProcess; /// [reply, outputFile]
};

#endif // NETWORKDOWNLAODER_H
