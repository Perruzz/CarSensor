#include "Temperature.h"

namespace Sensor
{
    const double Temperature::minC = -273.15;
    const double Temperature::minF = -459.67;

    Temperature::Temperature(double temperature, char scale)
    {
        if(scale == 'f')
        {
            fahrenheit = temperature;
            updateFahrenheit();
        }
        else
        {
            celsius = temperature;
            updateCelsius();
        }
    }

    void Temperature::updateCelsius()
    {
        fahrenheit = celsius * (9.0 / 5.0) + 32.0;
    }
    void Temperature::updateFahrenheit()
    {
        celsius = (fahrenheit - 32.0) * (5.0 / 9.0);
    }

    double Temperature::getTemp(const char& scale) const
    {
        if (scale == 'c') return celsius;
        if (scale == 'f') return fahrenheit;
        return 0;
    }
    double Temperature::getCelsius() const
    {
        return celsius;
    }
    double Temperature::getFahrenheit() const
    {
        return fahrenheit;
    }

    Temperature& Temperature::setCelsius(const double c)
    {
        this->celsius = c;
        updateCelsius();
        return *this;
    }
    Temperature& Temperature::setFahrenheit(const double f)
    {
        this->fahrenheit = f;
        updateFahrenheit();
        return *this;
    }

    Temperature::operator double() const
    {
        return celsius;
    }
}
