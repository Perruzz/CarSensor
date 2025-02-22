#include "SpeedSensor.h"

namespace Sensor
{
    const Speed SpeedSensor::urbanRoads = Speed(50.0);
    const Speed SpeedSensor::ruralRoads = Speed(90.0);
    const Speed SpeedSensor::ringRoads = Speed(110.0);
    const Speed SpeedSensor::motorways = Speed(130.0);

    SpeedSensor::SpeedSensor(unsigned int id, string  n, unsigned int d, Speed init, Speed dist)
    : CarSensor(id, n, d), initial(init), dispersion(dist) {}
    SpeedSensor::SpeedSensor(const SpeedSensor& copy)
    : CarSensor(copy.getIdentifier(), copy.getSensorName(), copy.data), initial(copy.initial), dispersion(copy.dispersion){}

    Speed SpeedSensor::getInitialSpeed() const
    {
        return initial;
    }
    double SpeedSensor::getInitialTime() const
    {
        return initial.getTime();
    }
    double SpeedSensor::getInitialDist() const
    {
        return initial.getDistance();
    }

    Speed SpeedSensor::getSpeedDispersion() const
    {
        return dispersion;
    }
    double SpeedSensor::getTimeDispersion() const
    {
        return dispersion.getTime();
    }
    double SpeedSensor::getDistDispersion() const
    {
        return dispersion.getDistance();
    }

    vector<double> SpeedSensor::getSpeedDataTime() const
    {
        std::vector<double> s;
        for (const auto & it : speedData)
        {
            s.push_back( it.getTime() );
        }
        return s;
    }
    vector<double> SpeedSensor::getSpeedDataDist() const
    {
        vector<double> s;
        for (const auto & it : speedData) 
        {
            s.push_back( it.getDistance() );
        }
        return s;
    }
    vector<double> SpeedSensor::getSpeedDataAvgS() const
    {
        vector<double> s;
        for (const auto & it : speedData) 
        {
            s.push_back( it.getASpeed() );
        }
        return s;
    }

    SpeedSensor& SpeedSensor::setInitialSpeed(const Speed init)
    {
        this->initial = init;
        return *this;
    }
    SpeedSensor& SpeedSensor::setInitialTime(const double t)
    {
        this->initial.setTime(t);
        return *this;
    }
    SpeedSensor& SpeedSensor::setInitialDist(const double d)
    {
        this->initial.setDistance(d);
        return *this;
    }

    SpeedSensor& SpeedSensor::setSpeedDispersion(const Speed disp)
    {
        this->dispersion = disp;
        return *this;
    }
    SpeedSensor& SpeedSensor::setTimeDispersion(const double t)
    {
        this->dispersion.setTime(t);
        return *this;
    }
    SpeedSensor& SpeedSensor::setDistDispersion(const double d)
    {
        this->dispersion.setDistance(d);
        return *this;
    }

    SpeedSensor* SpeedSensor::clone() const
    {
        return new SpeedSensor(*this);
    }
    void SpeedSensor::accept(SensorVisitor &v)
    {
        v.visit(*this);
    }
    void SpeedSensor::simulate()
    {
        clear();

        speedData.push_back(initial);

        double current_speed = initial.getASpeed();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> speed_dist(0.0, dispersion.getASpeed());

        for (unsigned int i = 0; i < data; ++i)
        {
            double variation = speed_dist(gen);
            current_speed += variation;

            current_speed = std::max(0.0, std::min(current_speed, Speed::limitSpeed));

            speedData.emplace_back(current_speed);
        }
    }
    void SpeedSensor::clear()
    {
        speedData.clear();
    }
}
