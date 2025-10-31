#ifndef NETWORKDOWNLAODER_H
#define NETWORKDOWNLAODER_H

#include <QObject>

class NetworkDownlaoder : public QObject
{
    Q_OBJECT
public:
    explicit NetworkDownlaoder(QObject *parent = nullptr);

signals:
};

#endif // NETWORKDOWNLAODER_H
