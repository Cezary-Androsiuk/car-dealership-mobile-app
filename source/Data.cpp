#include "Data.h"

Data::Data(QObject *parent)
    : QObject{parent}
{}

QList<Data *> Data::getDataList() const
{
    return m_dataList;
}
