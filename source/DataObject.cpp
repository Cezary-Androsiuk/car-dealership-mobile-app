#include "DataObject.h"

DataObject::DataObject(QObject *parent)
    : QObject{parent}
{}

int DataObject::getId() const
{
    return m_id;
}

void DataObject::setId(int id)
{
    if (m_id == id)
        return;
    m_id = id;
    emit idChanged();
}

QString DataObject::getOfferName() const
{
    return m_offerName;
}

void DataObject::setOfferName(const QString &offerName)
{
    if (m_offerName == offerName)
        return;
    m_offerName = offerName;
    emit offerNameChanged();
}

QString DataObject::getThumbnail() const
{
    return m_thumbnail;
}

void DataObject::setThumbnail(const QString &thumbnail)
{
    if (m_thumbnail == thumbnail)
        return;
    m_thumbnail = thumbnail;
    emit thumbnailChanged();
}

QString DataObject::getMake() const
{
    return m_make;
}

void DataObject::setMake(const QString &make)
{
    if (m_make == make)
        return;
    m_make = make;
    emit makeChanged();
}

QString DataObject::getModel() const
{
    return m_model;
}

void DataObject::setModel(const QString &model)
{
    if (m_model == model)
        return;
    m_model = model;
    emit modelChanged();
}

QString DataObject::getVersion() const
{
    return m_version;
}

void DataObject::setVersion(const QString &version)
{
    if (m_version == version)
        return;
    m_version = version;
    emit versionChanged();
}

QString DataObject::getDescription() const
{
    return m_description;
}

void DataObject::setDescription(const QString &description)
{
    if (m_description == description)
        return;
    m_description = description;
    emit descriptionChanged();
}

QString DataObject::getStatus() const
{
    return m_status;
}

void DataObject::setStatus(const QString &status)
{
    if (m_status == status)
        return;
    m_status = status;
    emit statusChanged();
}

int DataObject::getYear() const
{
    return m_year;
}

void DataObject::setYear(int year)
{
    if (m_year == year)
        return;
    m_year = year;
    emit yearChanged();
}

int DataObject::getPrice() const
{
    return m_price;
}

void DataObject::setPrice(int price)
{
    if (m_price == price)
        return;
    m_price = price;
    emit priceChanged();
}

bool DataObject::getNegotiable() const
{
    return m_negotiable;
}

void DataObject::setNegotiable(bool negotiable)
{
    if (m_negotiable == negotiable)
        return;
    m_negotiable = negotiable;
    emit negotiableChanged();
}

int DataObject::getMileage() const
{
    return m_mileage;
}

void DataObject::setMileage(int mileage)
{
    if (m_mileage == mileage)
        return;
    m_mileage = mileage;
    emit mileageChanged();
}

QString DataObject::getBodyType() const
{
    return m_bodyType;
}

void DataObject::setBodyType(const QString &bodyType)
{
    if (m_bodyType == bodyType)
        return;
    m_bodyType = bodyType;
    emit bodyTypeChanged();
}

QString DataObject::getTransmission() const
{
    return m_transmission;
}

void DataObject::setTransmission(const QString &transmission)
{
    if (m_transmission == transmission)
        return;
    m_transmission = transmission;
    emit transmissionChanged();
}

const DataDetails *DataObject::getDetails() const
{
    return &m_details;
}

DataDetails &DataObject::getDetailsRef()
{
    return m_details;
}
