#ifndef DATA_H
#define DATA_H

#include <QObject>

#include "DataObject.h"

class Data : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataObjectList dataObjectList READ getDataObjectList NOTIFY dataObjectListChanged FINAL)
public:
    explicit Data(QObject *parent = nullptr);

    DataObjectList getDataObjectList() const;

signals:
    void dataObjectListChanged();

private:
    DataObjectList m_dataObjectList;
};

#endif // DATA_H
