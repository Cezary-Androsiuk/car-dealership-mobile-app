#include "DataDetails.h"

DataDetails::DataDetails(QObject *parent)
    : QObject{parent}
{}

DataEngine DataDetails::getDataEngine() const
{
    return m_dataEngine;
}

void DataDetails::setDataEngine(const DataEngine &dataEngine)
{
    if (m_dataEngine == dataEngine)
        return;
    m_dataEngine = dataEngine;
    emit dataEngineChanged();
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
