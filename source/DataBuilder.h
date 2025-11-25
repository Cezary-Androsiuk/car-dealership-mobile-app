#ifndef DATABUILDER_H
#define DATABUILDER_H

#include <QObject>
#include <QJsonObject>

class Data;
class DataObject;
class DataDetails;
class DataEngine;

class DataBuilder
{
    static DataObject *buildDataObject(const QJsonObject &jObject, QObject *parent = nullptr);
    static void buildDetails(const QJsonObject jDetails, DataDetails &dataDetails);
    static void buildEngine(const QJsonObject jEngine, DataEngine &dataEngine);
public:
    static Data *buildData(const QJsonArray &jArray, QObject *parent = nullptr);
};

#endif // DATABUILDER_H
