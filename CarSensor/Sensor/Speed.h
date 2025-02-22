#ifndef SPEED_H
#define SPEED_H

namespace Sensor
{
    class Speed
    {
    private:
        double time = 0.0;  // second
        double distance = 0.0;  // meters
        double averageSpeed = 0.0;  // km/h

        void updateAvgS();
        void updateTimeDist();   

    public:
        static const double maxDistance;
        static const double limitSpeed;
        static const double lowestSpeed;

        Speed(double t, double d);
        explicit Speed(double aS);

        double getTime() const;
        double getDistance() const;
        double getASpeed() const;
        double getLimitSpeed() const;

        Speed& setTime(const double t);
        Speed& setDistance(const double d);
        Speed& setASpeed(const double aS);

        explicit operator double() const;
    };
}
#endif
