#include "Speed.h"

namespace Sensor
{
    const double Speed::maxDistance = 800000.0;
    const double Speed::limitSpeed = 250.0;
    const double Speed::lowestSpeed = 5.0;

    Speed::Speed(double t,  double d): time(t), distance(d)
    {
        updateAvgS();
    }
    Speed::Speed(double aS): averageSpeed(aS)
    {
        updateTimeDist();
    }

    void Speed::updateAvgS()
    {
        if(time < 60.0) time = 60.0;
        if(distance < 500.0) distance = 500.0;
        if(distance > maxDistance) distance = maxDistance;
        averageSpeed = (distance / 1000.0) / (time / 3600.0);
        if(averageSpeed > limitSpeed)
        {
            averageSpeed = limitSpeed;
            updateTimeDist();
        }
        if(averageSpeed < lowestSpeed)
        {
            averageSpeed = lowestSpeed;
            updateTimeDist();
        }
    }
    void Speed::updateTimeDist()
    {
        if(averageSpeed < lowestSpeed) averageSpeed = lowestSpeed;
        if(averageSpeed > limitSpeed) averageSpeed = limitSpeed;
        if(distance != 0.0)
        {
            time = ((distance / 1000.0) * 3600.0) / averageSpeed;
        }
        else
        {
            time = ((maxDistance / 1000.0) * 3600.0) / averageSpeed;
            if(time != 0) distance = maxDistance;
        }
    }

    double Speed::getTime() const
    {
        return time;
    }
    double Speed::getDistance() const
    {
        return distance;
    }
    double Speed::getASpeed() const
    {
        return averageSpeed;
    }
    double Speed::getLimitSpeed() const
    {
        return limitSpeed;
    }

    Speed& Speed::setTime(const double t)
    {
        this->time = t;
        updateAvgS();
        return *this;
    }
    Speed& Speed::setDistance(const double d)
    {
        this->distance = d;
        updateAvgS();
        return *this;
    }
    Speed& Speed::setASpeed(const double aS)
    {
        this->averageSpeed = aS;
        updateTimeDist();
        return *this;
    }

    Speed::operator double() const
    {
        return averageSpeed;
    }
}
