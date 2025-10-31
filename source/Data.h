#ifndef DATA_H
#define DATA_H

#include <QObject>

class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr);

signals:
};

#endif // DATA_H
