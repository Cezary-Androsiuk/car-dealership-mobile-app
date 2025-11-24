#include "DataBuilder.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "Data.h"

DataObject *DataBuilder::buildDataObject(const QJsonObject &jObject, QObject *parent)
{
    DataObject *data = new DataObject(parent);

    if(jObject.contains("id"))
        data->setId( jObject["id"].toInt(-1) );

    if(jObject.contains("offerName"))
        data->setOfferName( jObject["offerName"].toString() );

    if(jObject.contains("thumbnail"))
        data->setThumbnail( jObject["thumbnail"].toString() );

    if(jObject.contains("make"))
        data->setMake( jObject["make"].toString() );

    if(jObject.contains("model"))
        data->setModel( jObject["model"].toString() );

    if(jObject.contains("version"))
        data->setVersion( jObject["version"].toString() );

    if(jObject.contains("description"))
        data->setDescription( jObject["description"].toString() );

    if(jObject.contains("status"))
        data->setStatus( jObject["status"].toString() );

    if(jObject.contains("year"))
        data->setYear( jObject["year"].toInt(-1) );

    if(jObject.contains("price"))
        data->setPrice( jObject["price"].toInt(-1) );

    if(jObject.contains("negotiable"))
        data->setNegotiable( jObject["negotiable"].toBool());

    if(jObject.contains("mileage"))
        data->setMileage( jObject["mileage"].toInt(-1) );

    if(jObject.contains("bodyType"))
        data->setBodyType( jObject["bodyType"].toString() );

    if(jObject.contains("transmission"))
        data->setTransmission( jObject["transmission"].toString() );


    DataBuilder::buildDetails()
    DataDetails &dataDetails = data->getDataDetails();

    if(jObject.contains("details"))
    {
        QJsonObject jDetails = jObject["details"];

        if(jDetails.contains("comfortAndExtras"))
        {
            QJsonArray jArray = jDetails["comfortAndExtras"].toArray();

            QStringList array;
            array.reserve(jArray.size());

            for(int i=0; i<jArray.size(); i++)
                array.append(jArray[i].toString());

            dataDetails.setComfortAndExtras( jArray );
        }

        DataEngine &dataEngine = dataDetails.getDataEngine();

        if(jDetails.contains("engine"))
        {
            QJsonObject jEngine = jDetails["engine"];

        }
    }



    return data;
}

void DataBuilder::buildDetails(const QJsonObject jDetails, DataDetails &dataDetails)
{

}

void DataBuilder::buildEngine(const QJsonObject jEngine, DataEngine &dataEngine)
{

}
