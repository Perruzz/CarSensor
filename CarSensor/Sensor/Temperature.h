#ifndef TEMPERATURE_H
#define TEMPERATURE_H

namespace Sensor
{
    class Temperature
    {
    private:
        double celsius;
        double fahrenheit;

        void updateCelsius();
        void updateFahrenheit();

    public:
        static const double minC;
        static const double minF;

        Temperature(double temperature, char scale = 'c');

        double getTemp(const char& scale) const;
        
        double getCelsius() const;
        double getFahrenheit() const;

        Temperature& setCelsius(const double c);
        Temperature& setFahrenheit(const double f);

        explicit operator double()const;
    };
}
#endif
