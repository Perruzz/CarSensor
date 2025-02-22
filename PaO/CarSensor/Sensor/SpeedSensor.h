#ifndef SPEED_SENSOR_H
#define SPEED_SENSOR_H

#include "CarSensor.h"
#include "Speed.h"

namespace Sensor
{
    class SpeedSensor : public CarSensor
    {
    private:
        Speed initial;
        Speed dispersion;
        vector<Speed> speedData;
        
    public:
        static const Speed urbanRoads;
        static const Speed ruralRoads;
        static const Speed ringRoads;
        static const Speed motorways;

        SpeedSensor(unsigned int id, string  n, unsigned int d, Speed init, Speed stddev);
        SpeedSensor(const SpeedSensor& copy);

        Speed getInitialSpeed()const;
        double getInitialTime()const;
        double getInitialDist()const;

        Speed getSpeedDispersion()const;
        double getTimeDispersion()const;
        double getDistDispersion()const;

        vector<double> getSpeedDataTime()const;
        vector<double> getSpeedDataDist()const;
        vector<double> getSpeedDataAvgS()const;

        SpeedSensor& setInitialSpeed(const Speed init);
        SpeedSensor& setInitialTime(const double t);
        SpeedSensor& setInitialDist(const double d);
    
        SpeedSensor& setSpeedDispersion(const Speed disp);
        SpeedSensor& setTimeDispersion(const double t);
        SpeedSensor& setDistDispersion(const double d);

        SpeedSensor* clone() const override;
        void accept(SensorVisitor& v) override;
        void simulate() override;
        void clear() override;
    };
}
#endif
