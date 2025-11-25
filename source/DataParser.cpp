#include "DataParser.h"

#include <QDebug>
#include <QFile>
#include <QList>
#include <QMap>
#include <QUrl>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDir>

DataParser::DataParser(QObject *parent)
    : QObject{parent}
{}

QJsonDocument DataParser::readJsonDocFile(QString inputFilePath)
{
    /// read input json file
    QFile file(inputFilePath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Reading file" << inputFilePath << "failed!";
        throw "Reading file " + inputFilePath + " failed!";
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

    return jsonDoc;

}

QStringList DataParser::collectUrls(QString inputFilePath)
{
    qDebug() << "Collecting urls...";

    QJsonDocument jsonDoc = DataParser::readJsonDocFile(inputFilePath); // throws QString

    if(!jsonDoc.isArray())
    {
        qDebug() << "Invalid json Format (1)";
        throw QString("Invalid json Format (1)");
    }

    QJsonArray inputArray = jsonDoc.array();

    QStringList collectedUrls;

    /// iterate over object elements
    for(int i=0; i<inputArray.size(); i++)
    {
        QJsonObject jsonObj = inputArray[i].toObject();

        /// collect urls for each object
        DataParser::collectUrlsFromObject(jsonObj, collectedUrls);
    }

    qDebug() << "collected urls: " << collectedUrls.size();


    return collectedUrls;
}

StrStrMap DataParser::createUrlFilesHashMap(const QStringList &urls)
{
    const QCryptographicHash::Algorithm hashMethod = QCryptographicHash::Algorithm::Sha256;

    StrStrMap map;
    for(int i=0; i<urls.size(); i++)
    {
        QString url = urls[i];

        /// duplicates are allowed
        if(map.contains(url))
            continue;

        // QString urlImageSuffix = DataParser::urlImageSuffix(url);
        QByteArray urlByteArray = QCryptographicHash::hash(url.toUtf8(), hashMethod);
        QString urlHash = QString::fromUtf8(urlByteArray.toHex());

        map[url] = urlHash ;//+ "." + urlImageSuffix;
    }

    return map;
}

bool DataParser::saveUrlFilesHashMap(const StrStrMap &map, QString filePath)
{
    QJsonObject object;
    for(auto i=map.keyBegin(); i!=map.keyEnd(); i++)
    {
        object[*i] = map[*i];
    }

    QJsonDocument jsonDoc;
    jsonDoc.setObject(object);


    if(QFile::exists(filePath))
    {
        if(!QFile::remove(filePath))
            qWarning() << "deleting" << filePath << "failed!";
    }

    /// create path
    QFileInfo fileInfo(filePath);
    QDir fileDir = fileInfo.dir();
    if(!fileDir.exists())
    {
        fileDir.mkpath(".");
    }


    QFile file(filePath);
    if(!file.open(QFile::WriteOnly))
    {
        qCritical() << "Can't open file for write" << filePath;
        return false;
    }

    file.write(jsonDoc.toJson());
    file.close();

    return true;
}

void DataParser::resolveDataThumbnailPaths(QString hashMapFile, Data *data)
{
    /// read heashmap
    QJsonDocument jsonDoc = DataParser::readJsonDocFile(hashMapFile);

    if(!jsonDoc.isObject())
    {
        qDebug() << "Invalid json Format (1)";
        throw QString("Invalid json Format (1)");
    }

    Json

    /// change for each dataobject, their thumbnail url based on the map
}

void DataParser::collectUrlsFromObject(QJsonObject &jsonObject, QStringList &collectedUrls)
{
    /// collect urls for each object
    if(jsonObject.contains("thumbnail"))
    {
        QString url = jsonObject["thumbnail"].toString();
        collectedUrls.append(url);
    }
}

QString DataParser::urlImageSuffix(const QString &url)
{
    QString urlPath = QUrl(url).path();
    QFileInfo fileInfo(urlPath);
    return fileInfo.suffix();
}
