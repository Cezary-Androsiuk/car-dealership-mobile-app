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
    void inputDataDownloadFailed(QString details);

signals:
    void startInitialization();
    void dataLoaded();
    void noDataFound();
    void dataError(QString details);

private:
    NetworkDownlaoder m_networkDownloader;
    Data *m_data;
};

#endif // BACKEND_H
