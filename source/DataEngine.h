#ifndef DATAENGINE_H
#define DATAENGINE_H

#include <QObject>

class DataEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fuelType READ getFuelType WRITE setFuelType NOTIFY fuelTypeChanged FINAL)
    Q_PROPERTY(int horsepower READ getHorsepower WRITE setHorsepower NOTIFY horsepowerChanged FINAL)
    Q_PROPERTY(int engineCapacity READ getEngineCapacity WRITE setEngineCapacity NOTIFY engineCapacityChanged FINAL)

public:
    explicit DataEngine(QObject *parent = nullptr);

    QString getFuelType() const;
    void setFuelType(const QString &fuelType);

    int getHorsepower() const;
    void setHorsepower(int horsepower);

    int getEngineCapacity() const;
    void setEngineCapacity(int engineCapacity);

signals:
    void fuelTypeChanged();
    void horsepowerChanged();
    void engineCapacityChanged();

private:
    QString m_fuelType;
    int m_horsepower;
    int m_engineCapacity;
};

#endif // DATAENGINE_H
