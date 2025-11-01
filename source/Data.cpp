#include "Data.h"

Data::Data(QObject *parent)
    : QObject{parent}
{}

DataObjectList Data::getDataObjectList() const
{
    return m_dataObjectList;
}
