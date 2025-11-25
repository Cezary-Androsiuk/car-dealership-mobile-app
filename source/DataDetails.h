#ifndef DATADETAILS_H
#define DATADETAILS_H

#include <QObject>
#include <QList>

#include "DataEngine.h"

class DataDetails : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const DataEngine *engine READ getEngine CONSTANT FINAL)
    Q_PROPERTY(QStringList comfortAndExtras READ getComfortAndExtras WRITE setComfortAndExtras NOTIFY comfortAndExtrasChanged FINAL)

public:
    explicit DataDetails(QObject *parent = nullptr);

    const DataEngine *getEngine() const;
    DataEngine &getEngineRef();

    QStringList getComfortAndExtras() const;
    void setComfortAndExtras(const QStringList &comfortAndExtras);

signals:
    void comfortAndExtrasChanged();

private:
    DataEngine m_engine;
    QStringList m_comfortAndExtras;
};

#endif // DATADETAILS_H
