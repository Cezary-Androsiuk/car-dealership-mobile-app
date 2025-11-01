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
    void loadData();

private slots:


signals:
    void dataLoaded();
    void noDataFound();
    void dataError(QString details);

private:
    NetworkDownlaoder m_networkDownloader;
    Data *m_data;
};

#endif // BACKEND_H
