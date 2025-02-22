#ifndef CABIN_TEMPERATURE_SENSOR_H
#define CABIN_TEMPERATURE_SENSOR_H

#include "CarSensor.h"
#include "Temperature.h"
#include "ctime"

namespace Sensor
{
    class CabinTemperatureSensor : public CarSensor
    {
    private:
        Temperature initial;
        Temperature dispersion;
        Temperature min;
        Temperature max;
        char scale;

        vector<Temperature> minTemp;
        vector<Temperature> avgTemp;
        vector<Temperature> maxTemp;

    public:
        CabinTemperatureSensor(unsigned int id, string  n, unsigned int d, Temperature init, Temperature stddev, Temperature mn, Temperature mx, char s);
        CabinTemperatureSensor(const CabinTemperatureSensor& copy);

        Temperature getInitialTemp() const;
        Temperature getTempDispersion() const;
        Temperature getMin() const;
        Temperature getMax() const ;
        char getScale() const;

        vector<double> getMinTemp() const;
        vector<double> getAvgTemp() const;
        vector<double> getMaxTemp() const;

        CabinTemperatureSensor& setInitialTemp(const Temperature init);
        CabinTemperatureSensor& setTempDispersion(const Temperature disp);
        CabinTemperatureSensor& setMin(const Temperature mn);
        CabinTemperatureSensor& setMax(const Temperature mx);
        CabinTemperatureSensor& setScale(const char s);

        CabinTemperatureSensor* clone() const override;
        void accept(SensorVisitor& v) override;
        void simulate() override;
        void clear() override;
    };
}
#endif
