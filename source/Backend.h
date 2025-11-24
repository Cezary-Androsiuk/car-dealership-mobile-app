#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

#include "Data.h"
#include "NetworkDownlaoder.h"

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

public slots:
    void initialize();

private slots:
    void loadData();
    void inputDataDownloaded(QString outputFile);
    void onImagesDownloadedFinished(int filesToDownload, int downloadedFiles);
    void imagesDownloaded();
    void inputDataDownloadFailed();


signals:
    void startInitialization();

    void dataStatus(QString status);
    void dataLoaded();
    void noDataFound();
    void showToast(QString message);
    void dataError(QString details);

private:
    NetworkDownlaoder m_networkDownloader;
    Data *m_data;
};

#endif // BACKEND_H
