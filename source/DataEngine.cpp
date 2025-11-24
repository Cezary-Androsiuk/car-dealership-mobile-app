#include "DataEngine.h"

DataEngine::DataEngine(QObject *parent)
    : QObject{parent}
    , m_fuelType{""}
    , m_horsepower{-1}
    , m_engineCapacity{-1}
{

}

QString DataEngine::getFuelType() const
{
    return m_fuelType;
}

void DataEngine::setFuelType(const QString &fuelType)
{
    if (m_fuelType == fuelType)
        return;
    m_fuelType = fuelType;
    emit fuelTypeChanged();
}

int DataEngine::getHorsepower() const
{
    return m_horsepower;
}

void DataEngine::setHorsepower(int horsepower)
{
    if (m_horsepower == horsepower)
        return;
    m_horsepower = horsepower;
    emit horsepowerChanged();
}

int DataEngine::getEngineCapacity() const
{
    return m_engineCapacity;
}

void DataEngine::setEngineCapacity(int engineCapacity)
{
    if (m_engineCapacity == engineCapacity)
        return;
    m_engineCapacity = engineCapacity;
    emit engineCapacityChanged();
}
