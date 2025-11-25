#ifndef DATA_H
#define DATA_H

#include <QObject>

#include "DataObject.h"

class Data : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataObjectList objects READ getObjects NOTIFY objectsChanged FINAL)
public:
    explicit Data(QObject *parent = nullptr);

    DataObjectList getObjects() const;
    void setObjects(DataObjectList objects);

signals:
    void objectsChanged();

private:
    DataObjectList m_objects;
};

#endif // DATA_H
