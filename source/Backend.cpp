#include "Backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
{}

void Backend::loadData()
{
    // emit this->dataLoaded();
    // emit this->noDataFound();
    emit this->dataError("message");
}
