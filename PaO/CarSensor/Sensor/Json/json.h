#ifndef JSON_H
#define JSON_H

#include "reader.h"
#include "jsonvisitor.h"

namespace Sensor::Json
{
    class Json
    {
    public:
        static QJsonObject fromObject(const CarSensor& sensor);
        static CarSensor& toObject(const QJsonObject& json);
    };
}
#endif
