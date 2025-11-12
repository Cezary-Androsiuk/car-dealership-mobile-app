#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QJsonObject>

typedef QMap<QString, QString> StrStrMap;

class DataParser : public QObject
{
    Q_OBJECT
public:
    explicit DataParser(QObject *parent = nullptr);

    static QStringList collectUrls(QString inputFilePath);

    static StrStrMap createUrlFilesHashMap(const QStringList &urls);

    static bool saveUrlFilesHashMap(const StrStrMap &map, QString filePath);

private:
    /// matching json pattern - explained under class
    static void collectUrlsFromObject(
        QJsonObject &jsonObject,
        QStringList &collectedUrls);

    static QString urlImageSuffix(const QString &url);

signals:
};

/// matching json pattern:  function was adjusted for the specyfic json file pattern
///                         and cannot be used for the other one

#endif // DATAPARSER_H
