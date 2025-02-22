#ifndef SENSOR_VISITOR_H
#define SENSOR_VISITOR_H

namespace Sensor 
{
    class TirePressureSensor;
    class SpeedSensor;
    class CabinTemperatureSensor;

    class SensorVisitor 
    {
    public:
        virtual ~SensorVisitor() = default;

        virtual void visit(TirePressureSensor& TPSensor) = 0;
        virtual void visit(SpeedSensor& SSensor) = 0;
        virtual void visit(CabinTemperatureSensor& CTSensor) = 0;
    };
}
#endif 
