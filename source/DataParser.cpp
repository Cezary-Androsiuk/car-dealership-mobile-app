#include "DataParser.h"

#include <QDebug>
#include <QFile>
#include <QList>
#include <QMap>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

DataParser::DataParser(QObject *parent)
    : QObject{parent}
{}

QStringList DataParser::collectUrls(QString inputFilePath)
{
    qDebug() << "Collecting urls...";

    /// read input json file
    QFile file(inputFilePath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Reading file" << inputFilePath << "failed!";
        throw "Reading file" + inputFilePath + "failed!";
    }

    QByteArray data = file.readAll();
    file.close();

    /// parse json
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &jsonError);
    if(jsonDoc.isNull())
    {
        qDebug() << "Parsing JSON failed, details: " << jsonError.errorString();
        throw "Parsing JSON failed, details: " + jsonError.errorString();
    }

    if(!jsonDoc.isArray())
    {
        qDebug() << "Invalid json Format (1)";
        throw "Invalid json Format (1)";
    }

    QJsonArray inputArray = jsonDoc.array();

    QStringList collectedUrls;

    /// iterate over object elements
    for(int i=0; i<inputArray.size(); i++)
    {
        QJsonObject jsonObj = inputArray[i];

        /// collect urls for each object
        DataParser::collectUrlsFromObject(jsonObj, collectedUrls);
    }


    return collectedUrls;
}

StrStrMap DataParser::createUrlFilesHashMap(const QStringList &urls)
{
    StrStrMap map;

}

void DataParser::collectUrlsFromObject(QJsonObject &jsonObject, QStringList &collectedFiles)
{
    /// collect urls for each object
}
