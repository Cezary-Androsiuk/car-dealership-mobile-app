#include "Data.h"

Data::Data(QObject *parent)
    : QObject{parent}
{}

DataObjectList Data::getObjects() const
{
    return m_objects;
}

void Data::setObjects(DataObjectList objects)
{
    if (m_objects == objects)
        return;
    m_objects = objects;
    emit objectsChanged();
}

