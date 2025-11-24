#ifndef DATADETAILS_H
#define DATADETAILS_H

#include <QObject>
#include <QList>

#include "DataEngine.h"

class DataDetails : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataEngine dataEngine READ getDataEngine CONSTANT FINAL)
    Q_PROPERTY(QStringList comfortAndExtras READ getComfortAndExtras WRITE setComfortAndExtras NOTIFY comfortAndExtrasChanged FINAL)

public:
    explicit DataDetails(QObject *parent = nullptr);

    DataEngine &getDataEngine() const;

    QStringList getComfortAndExtras() const;
    void setComfortAndExtras(const QStringList &comfortAndExtras);

signals:
    void comfortAndExtrasChanged();

private:
    DataEngine m_dataEngine;
    QStringList m_comfortAndExtras;
};

#endif // DATADETAILS_H
