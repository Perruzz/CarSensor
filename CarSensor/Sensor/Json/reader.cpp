#include "reader.h"

namespace Sensor::Json
{
    CarSensor* Reader::readTirePressure(const QJsonObject &o)
    {
        return new TirePressureSensor
        (
            o.value("identifier").toInt(),
            o.value("sensor_name").toString().toStdString(),
            o.value("data").toInt(),
            o.value("initial_pressure_bar").toDouble(),
            o.value("dispersion_pressure_bar").toDouble(),
            o.value("pressure_warning").toDouble()
        );
    }
    CarSensor* Reader::readSpeed(const QJsonObject &o)
    {
        return new SpeedSensor
        (
            o.value("identifier").toInt(),
            o.value("sensor_name").toString().toStdString(),
            o.value("data").toInt(),
            Sensor::Speed(o.value("initial_time_seconds").toDouble(), o.value("initial_distance_meters").toDouble()),
            Sensor::Speed(o.value("dispersion_time_seconds").toDouble(), o.value("dispersion_distance_meters").toDouble())
        );
    }
    CarSensor* Reader::readCabinTemperature(const QJsonObject& o)
    {
        char scale = ' ';

        QString string = o["scale"].toString();
        if(!string.isEmpty())
        {
            scale = string.at(0).toLatin1();
        }

        if(scale == 'c')
        {
            return new CabinTemperatureSensor
            (
                o.value("identifier").toInt(),
                o.value("sensor_name").toString().toStdString(),
                o.value("data").toInt(),
                Sensor::Temperature(o.value("initial_temp_C°").toDouble(), 'c'),
                Sensor::Temperature(o.value("dispersion_temp_C°").toDouble(), 'c'),
                Sensor::Temperature(o.value("min_temp_C°").toDouble(), 'c'),
                Sensor::Temperature(o.value("max_temp_C°").toDouble(), 'c'),
                'c'
            );
        }
        else if(scale == 'f')
        {
            return new CabinTemperatureSensor
            (
                o.value("identifier").toInt(),
                o.value("sensor_name").toString().toStdString(),
                o.value("data").toInt(),
                Sensor::Temperature( o.value("initial_temp_F°").toDouble(), 'f'),
                Sensor::Temperature( o.value("dispersion_temp_F°").toDouble(), 'f'),
                Sensor::Temperature( o.value("min_temp_F°").toDouble(), 'f'),
                Sensor::Temperature( o.value("max_temp_F°").toDouble(), 'f'),
                'f'
            );
        }
        throw std::invalid_argument("error reading scale json file");
    }

    const map<unsigned int, CarSensor*>& Reader::getCache() const
    {
        return cache;
    }
    Reader& Reader::clear()
    {
        cache.clear();
        return *this;
    }

    CarSensor* Reader::read(const QJsonObject& o)
    {
        QJsonValue type = o.value("type");

        if (type.isUndefined())
        {
            throw std::invalid_argument("missing sensor type");
        }

        const unsigned int identifier = o.value("identifier").toInt();

        if (cache.count(identifier) > 0)
        {
            return cache[identifier];
        }
        else if (type.toString().compare("tire_pressure") == 0)
        {
            cache[identifier] = readTirePressure(o);
        }
        else if (type.toString().compare("speed") == 0)
        {
            cache[identifier] = readSpeed(o);
        }
        else if (type.toString().compare("cabin_temperature") == 0)
        {
            cache[identifier] = readCabinTemperature(o);
        }
        else
        {
            throw std::invalid_argument("Unknown type");
        }
        return cache[identifier];
    }
}
