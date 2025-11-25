#include "DataDetails.h"

DataDetails::DataDetails(QObject *parent)
    : QObject{parent}
{}

const DataEngine *DataDetails::getEngine() const
{
    return &m_engine;
}

DataEngine &DataDetails::getEngineRef()
{
    return m_engine;
}

QStringList DataDetails::getComfortAndExtras() const
{
    return m_comfortAndExtras;
}

void DataDetails::setComfortAndExtras(const QStringList &comfortAndExtras)
{
    if (m_comfortAndExtras == comfortAndExtras)
        return;
    m_comfortAndExtras = comfortAndExtras;
    emit comfortAndExtrasChanged();
}
