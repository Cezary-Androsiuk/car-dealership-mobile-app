#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>

class DataObject : public QObject
{
    Q_OBJECT
public:
    explicit DataObject(QObject *parent = nullptr);

signals:
};

#endif // DATAOBJECT_H
