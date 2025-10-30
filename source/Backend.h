#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

public slots:
    void loadData();

signals:
    void dataLoaded();
    void noDataFound();
    void dataError(QString details);
};

#endif // BACKEND_H
