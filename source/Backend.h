#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

#include "NetworkDownlaoder.h"

#include "Data.h"

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Data *data READ getData NOTIFY dataChanged FINAL)
public:
    explicit Backend(QObject *parent = nullptr);

    Data *getData() const;

public slots:
    void downloadNewestData();
    void removeCache();

private slots:
    void downloadDataThread();
    void onInputDataDownloaded(QString outputFile);
    void onImagesDownloadingFinished(int filesToDownload, int downloadedFiles);
    void onInputDataDownloadingFailed();

    void loadCache();

signals:
    void startDownloading();

    void dataStatus(QString status);
    void dataLoaded();
    void showToast(QString message);
    void dataError(QString details);

    void dataChanged();

private:
    NetworkDownlaoder m_networkDownloader;
    Data *m_data;
};

#endif // BACKEND_H
