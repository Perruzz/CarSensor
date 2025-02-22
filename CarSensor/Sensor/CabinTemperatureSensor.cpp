#include"CabinTemperatureSensor.h"

namespace Sensor 
{
    CabinTemperatureSensor::CabinTemperatureSensor(unsigned int id, string  n, unsigned int d, Temperature init, Temperature disp, Temperature mn, Temperature mx, char s)
    : CarSensor(id, n, d),  initial(init), dispersion(disp), min(mn), max(mx), scale(s) {}
    CabinTemperatureSensor::CabinTemperatureSensor(const CabinTemperatureSensor& copy)
    : CarSensor(copy.getIdentifier(), copy.getSensorName(), copy.data), initial(copy.initial), dispersion(copy.dispersion), min(copy.min), max(copy.max), scale(copy.scale) {}

    Temperature CabinTemperatureSensor::getInitialTemp() const 
    {
        return initial;
    }
    Temperature CabinTemperatureSensor::getTempDispersion() const
    {
        return dispersion;
    }
    Temperature CabinTemperatureSensor::getMin() const
    {
        return min;
    }
    Temperature CabinTemperatureSensor::getMax() const 
    {
        return max;
    }
    char CabinTemperatureSensor::getScale() const
    {
        return scale;
    }

    vector<double> CabinTemperatureSensor::getMinTemp() const
    {
        std::vector<double> min_data;
        for (const auto & it : minTemp)
        {
            min_data.push_back( it.getTemp(scale) );
        }
        return min_data;
    }
    vector<double> CabinTemperatureSensor::getMaxTemp() const
    {
        vector<double> max_data;
        for(const auto & it : maxTemp) 
        {
            max_data.push_back( it.getTemp(scale) );
        }
        return max_data;
    }
    vector<double> CabinTemperatureSensor::getAvgTemp() const
    {
        vector<double> mean_data;
        for(const auto & it : avgTemp) 
        {
            mean_data.push_back( it.getTemp(scale) );
        }
        return mean_data;
    }

    CabinTemperatureSensor& CabinTemperatureSensor::setInitialTemp(const Temperature init)
    {
        this->initial = init;
        return *this;
    }
    CabinTemperatureSensor& CabinTemperatureSensor::setTempDispersion(const Temperature stddev)
    {
        this->dispersion = stddev;
        return *this;
    }
    CabinTemperatureSensor& CabinTemperatureSensor::setMin(const Temperature m)
    {
        this->min = m;
        return *this;
    }
    CabinTemperatureSensor& CabinTemperatureSensor::setMax(const Temperature m)
    {
        this->max = m;
        return *this;
    }
    CabinTemperatureSensor& CabinTemperatureSensor::setScale(const char s)
    {
        this->scale = s;
        return *this;
    }

    CabinTemperatureSensor* CabinTemperatureSensor::clone() const
    {
        return new CabinTemperatureSensor(*this);
    }
    void CabinTemperatureSensor::accept(SensorVisitor &v)
    {
        v.visit(*this);
    }
    void CabinTemperatureSensor::simulate()
    {
        clear();

        std::random_device rd;
        std::mt19937 gen(rd());

        double phase_shift = 2 * M_PI * gen() / gen.max();
        double amplitude = 5.0 + (gen() % 3);
        double range_width = 2.0 + (gen() % 2);

        for (unsigned int i = 0; i < data; ++i)
        {
            double time = static_cast<double>(i) / (data - 1);
            double diurnal_variation = amplitude * std::sin(2 * M_PI * time + phase_shift);

            double current_temp = initial.getTemp(scale) + diurnal_variation;

            double current_min = current_temp - range_width;
            double current_max = current_temp + range_width;

            current_min = std::max(current_min, min.getTemp(scale));
            current_max = std::min(current_max, max.getTemp(scale));

            minTemp.push_back(Sensor::Temperature(current_min, scale));
            avgTemp.push_back(Sensor::Temperature(current_temp, scale));
            maxTemp.push_back(Sensor::Temperature(current_max, scale));
        }
    }
    void CabinTemperatureSensor::clear() 
    {
        minTemp.clear();
        avgTemp.clear();
        maxTemp.clear();
    }
}
