#include "json.h"

namespace Sensor::Json
{
    QJsonObject Json::fromObject(const CarSensor& sensor)
    {
        JsonVisitor json_visitor;
        const_cast<CarSensor&>(sensor).accept(json_visitor);
        return json_visitor.getObject();
    }
    CarSensor& Json::toObject(const QJsonObject& json)
    {
        Reader reader;
        return *(reader.read(json));
    }
}
