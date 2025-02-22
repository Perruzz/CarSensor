#ifndef READER_H
#define READER_H

#include <map>
#include <QJsonObject>

#include "../CarSensor.h"
#include "../TirePressureSensor.h"
#include "../SpeedSensor.h"
#include "../CabinTemperatureSensor.h"
using std::map;

namespace Sensor::Json
{
    class Reader
    {
    private:
        map<unsigned int, CarSensor*> cache;
        static CarSensor* readTirePressure(const QJsonObject& o);
        static CarSensor* readSpeed(const QJsonObject& o);
        static CarSensor* readCabinTemperature(const QJsonObject& o);

    public:
        ~Reader() = default;

        const map<unsigned int, CarSensor*>& getCache() const;

        Reader& clear();

        CarSensor* read(const QJsonObject& o);
    };
}
#endif
