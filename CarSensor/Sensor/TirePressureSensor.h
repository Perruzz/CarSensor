#ifndef TIRE_PRESSURE_SENSOR_H
#define TIRE_PRESSURE_SENSOR_H

#include "CarSensor.h"
#include <QDebug>

namespace Sensor 
{
    class TirePressureSensor : public CarSensor 
    {
    private:
        double initial;     //bar
        double dispersion;     //bar
        double warningPressureLevel;  //bar
        bool alert;
        vector<double> pressures;     //bar
        vector<unsigned int> alertPoints;

    public:
        static const double min;   //bar
        static const double max;   //bar

        TirePressureSensor(unsigned int id, string n, unsigned int d, double init, double disp, double wL);
        TirePressureSensor(const TirePressureSensor& copy);

        double getInitialPressure() const;
        double getPressureDispersion() const;
        double getWarningPressureLevel() const;
        bool getAlert() const;

        vector<double> getPressureData() const;
        vector<unsigned int> getAlertPoints() const;
    
        TirePressureSensor& setInitialPressure(const double init);
        TirePressureSensor& setPressureDispersion(const double disp);
        TirePressureSensor& setWarningPressureLevel(const double wL);

        TirePressureSensor* clone() const override;
        void accept(SensorVisitor& v) override;
        void simulate() override;    
        void clear() override;
    };
}
#endif 
