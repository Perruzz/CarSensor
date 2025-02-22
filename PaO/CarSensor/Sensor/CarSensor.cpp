#include "CarSensor.h"

namespace Sensor
{
    CarSensor::CarSensor(unsigned int id, string n, unsigned int d): identifier(id), sensor_name(n), data(d){}
    CarSensor::CarSensor(const CarSensor& copy) : identifier(copy.identifier), sensor_name(copy.sensor_name), data(copy.data) {}

    unsigned int CarSensor::getIdentifier() const
    {
        return identifier;
    }
    const string& CarSensor::getSensorName() const
    {
        return sensor_name;
    }
    unsigned int CarSensor::getData() const
    {
        return data;
    }
    
    CarSensor& CarSensor::setSensorName(const std::string& s)
    {
        this->sensor_name = s;
        return *this;
    }
    CarSensor& CarSensor::setData(const unsigned int d)
    {
        this->data = d;
        return *this;
    }
}
