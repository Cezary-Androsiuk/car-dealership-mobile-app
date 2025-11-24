#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>

#include "DataDetails.h"

class DataObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(QString offerName READ getOfferName WRITE setOfferName NOTIFY offerNameChanged FINAL)
    Q_PROPERTY(QString thumbnail READ getThumbnail WRITE setThumbnail NOTIFY thumbnailChanged FINAL)
    Q_PROPERTY(QString make READ getMake WRITE setMake NOTIFY makeChanged FINAL)
    Q_PROPERTY(QString version READ getVersion WRITE setVersion NOTIFY versionChanged FINAL)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY descriptionChanged FINAL)
    Q_PROPERTY(QString status READ getStatus WRITE setStatus NOTIFY statusChanged FINAL)
    Q_PROPERTY(int year READ getYear WRITE setYear NOTIFY yearChanged FINAL)
    Q_PROPERTY(int price READ getPrice WRITE setPrice NOTIFY priceChanged FINAL)
    Q_PROPERTY(bool negotiable READ getNegotiable WRITE setNegotiable NOTIFY negotiableChanged FINAL)
    Q_PROPERTY(int mileage READ getMileage WRITE setMileage NOTIFY mileageChanged FINAL)
    Q_PROPERTY(QString bodyType READ getBodyType WRITE setBodyType NOTIFY bodyTypeChanged FINAL)
    Q_PROPERTY(QString transmission READ getTransmission WRITE setTransmission NOTIFY transmissionChanged FINAL)
    Q_PROPERTY(DataDetails dataDetails READ getDataDetails WRITE setDataDetails NOTIFY dataDetailsChanged FINAL)

public:
    explicit DataObject(QObject *parent = nullptr);

    int getId() const;
    void setId(int id);

    QString getOfferName() const;
    void setOfferName(const QString &offerName);

    QString getThumbnail() const;
    void setThumbnail(const QString &thumbnail);

    QString getMake() const;
    void setMake(const QString &make);

    QString getVersion() const;
    void setVersion(const QString &version);

    QString getDescription() const;
    void setDescription(const QString &description);

    QString getStatus() const;
    void setStatus(const QString &status);

    int getYear() const;
    void setYear(int year);

    int getPrice() const;
    void setPrice(int price);

    bool getNegotiable() const;
    void setNegotiable(bool negotiable);

    int getMileage() const;
    void setMileage(int mileage);

    QString getBodyType() const;
    void setBodyType(const QString &bodyType);

    QString getTransmission() const;
    void setTransmission(const QString &transmission);

    DataDetails getDataDetails() const;
    void setDataDetails(const DataDetails &dataDetails);

signals:
    void idChanged();
    void offerNameChanged();
    void thumbnailChanged();
    void makeChanged();
    void versionChanged();
    void descriptionChanged();
    void statusChanged();
    void yearChanged();
    void priceChanged();
    void negotiableChanged();
    void mileageChanged();
    void bodyTypeChanged();
    void transmissionChanged();
    void dataDetailsChanged();

private:
    int m_id;
    // QString m_source;

    QString m_offerName;
    QString m_thumbnail;
    QString m_make;
    QString m_model;
    QString m_version;
    QString m_description;
    QString m_status;
    int m_year;
    int m_price;
    bool m_negotiable;
    int m_mileage;
    QString m_bodyType;
    QString m_transmission;

    DataDetails m_dataDetails;
};

typedef QList<DataObject *> DataObjectList;

#endif // DATAOBJECT_H
