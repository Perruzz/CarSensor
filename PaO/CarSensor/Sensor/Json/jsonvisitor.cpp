#include "jsonvisitor.h"

namespace Sensor::Json
{
    QJsonObject JsonVisitor::getObject() const
    {
        return o;
    }

    void JsonVisitor::visit( TirePressureSensor& TPSensor)
    {
        QJsonObject SObject;

        SObject.insert("type", QJsonValue::fromVariant("tire_pressure"));
        SObject.insert("identifier", QJsonValue::fromVariant(TPSensor.getIdentifier()));
        SObject.insert("sensor_name", QJsonValue::fromVariant(TPSensor.getSensorName().c_str()));
        SObject.insert("data", QJsonValue::fromVariant(TPSensor.getData()));
        SObject.insert("initial_pressure_bar", QJsonValue::fromVariant(TPSensor.getInitialPressure()));
        SObject.insert("dispersion_pressure_bar", QJsonValue::fromVariant(TPSensor.getPressureDispersion()));
        SObject.insert("pressure_warning", QJsonValue::fromVariant(TPSensor.getWarningPressureLevel()));

        o = SObject;
    }
    void JsonVisitor::visit( SpeedSensor& SSensor)
    {
        QJsonObject TPObject;

        TPObject.insert("type", QJsonValue::fromVariant("speed"));
        TPObject.insert("identifier", QJsonValue::fromVariant(SSensor.getIdentifier()));
        TPObject.insert("sensor_name", QJsonValue::fromVariant(SSensor.getSensorName().c_str()));
        TPObject.insert("data", QJsonValue::fromVariant(SSensor.getData()));
        TPObject.insert("initial_time_seconds", QJsonValue::fromVariant(SSensor.getInitialTime()));
        TPObject.insert("initial_distance_meters", QJsonValue::fromVariant(SSensor.getInitialDist()));
        TPObject.insert("dispersion_time_seconds", QJsonValue::fromVariant(SSensor.getTimeDispersion()));
        TPObject.insert("dispersion_distance_meters", QJsonValue::fromVariant(SSensor.getDistDispersion()));

        o = TPObject;
    }
    void JsonVisitor::visit( CabinTemperatureSensor& CTSensor)
    {
        char scale = CTSensor.getScale();

        QJsonObject CTObject;
        CTObject.insert("type", QJsonValue::fromVariant("cabin_temperature"));
        CTObject.insert("identifier", QJsonValue::fromVariant(CTSensor.getIdentifier()));
        CTObject.insert("sensor_name", QJsonValue::fromVariant(CTSensor.getSensorName().c_str()));
        CTObject.insert("data", QJsonValue::fromVariant(CTSensor.getData()));

        if(scale == 'c')
        {
            CTObject.insert("initial_temp_C°", QJsonValue::fromVariant(CTSensor.getInitialTemp().getCelsius()));
            CTObject.insert("dispersion_temp_C°", QJsonValue::fromVariant(CTSensor.getTempDispersion().getCelsius()));
            CTObject.insert("min_temp_C°", QJsonValue::fromVariant(CTSensor.getMin().getCelsius()));
            CTObject.insert("max_temp_C°", QJsonValue::fromVariant(CTSensor.getMax().getCelsius()));
        }
        else if(scale == 'f')
        {
            CTObject.insert("initial_temp_F°", QJsonValue::fromVariant(CTSensor.getInitialTemp().getFahrenheit()));
            CTObject.insert("dispersion_temp_F°", QJsonValue::fromVariant(CTSensor.getTempDispersion().getFahrenheit()));
            CTObject.insert("min_temp_F°", QJsonValue::fromVariant(CTSensor.getMin().getFahrenheit()));
            CTObject.insert("max_temp_F°", QJsonValue::fromVariant(CTSensor.getMax().getFahrenheit()));
        }

        CTObject.insert("scale", QJsonValue(QString(scale)));

        o = CTObject;
    }
}
