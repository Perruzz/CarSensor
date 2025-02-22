#ifndef CAR_SENSOR_H
#define CAR_SENSOR_H

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <vector>
#include <cmath>
#include "SensorVisitor.h"
using std::string;
using std::vector;

namespace Sensor
{
    class CarSensor
    {
    private:
        unsigned int identifier;
        string sensor_name;

    protected:
        unsigned int data;

    public:
        CarSensor(unsigned int id, string n, unsigned int d);
        CarSensor(const CarSensor& copy);
        virtual ~CarSensor() = default;

        unsigned int getIdentifier() const;
        const string& getSensorName() const;
        unsigned int getData() const;

        CarSensor& setSensorName(const string& s);
        CarSensor& setData(const unsigned int d);
    
        virtual CarSensor* clone() const = 0;
        virtual void accept(SensorVisitor& v) = 0;
        virtual void simulate() = 0;
        virtual void clear() = 0;
    };
}
#endif
