#include "DataDetails.h"

DataDetails::DataDetails(QObject *parent)
    : QObject{parent}
{}

DataEngine &DataDetails::getDataEngine() const
{
    return m_dataEngine;
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
