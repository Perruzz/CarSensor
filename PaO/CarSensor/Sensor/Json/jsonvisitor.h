#ifndef JSON_VISITOR_H
#define JSON_VISITOR_H

#include <QJsonObject>

#include "../SensorVisitor.h"
#include "../TirePressureSensor.h"
#include "../SpeedSensor.h"
#include "../CabinTemperatureSensor.h"

namespace Sensor::Json
{
    class JsonVisitor : public SensorVisitor
    {
    private:
        QJsonObject o;

    public:
        QJsonObject getObject() const;

        void visit(TirePressureSensor& TPSensor) override;
        void visit(SpeedSensor& SSensor) override;
        void visit(CabinTemperatureSensor& CTSensor) override;
    };
}
#endif
