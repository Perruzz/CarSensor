#include "TirePressureSensor.h"

namespace Sensor 
{
    const double TirePressureSensor::min = 0.0;
    const double TirePressureSensor::max = 30.0;
    
    TirePressureSensor::TirePressureSensor(unsigned int id, string n, unsigned int d, double init, double disp, double wL)
    : CarSensor(id, n, d), initial(init), dispersion(disp), warningPressureLevel(wL) {}
    TirePressureSensor::TirePressureSensor(const TirePressureSensor& copy)
    : CarSensor(copy.getIdentifier(), copy.getSensorName(), copy.data), initial(copy.initial), dispersion(copy.dispersion), warningPressureLevel(copy.warningPressureLevel) {}

    double TirePressureSensor::getInitialPressure() const
    {
        return initial;
    }
    double TirePressureSensor::getPressureDispersion() const
    {
        return dispersion;
    }
    double TirePressureSensor::getWarningPressureLevel() const
    {
        return warningPressureLevel;
    }
    bool TirePressureSensor::getAlert() const
    {
        return alert;
    }
    
    vector<double> TirePressureSensor::getPressureData() const
    {
        vector<double> pressure_data;
        for (const auto &it : pressures) 
        {
            pressure_data.push_back(it);
        }
        return pressure_data;
    }
    vector<unsigned int> TirePressureSensor::getAlertPoints() const
    {
        vector<unsigned int> alert_data;
        for (const auto & it : alertPoints) 
        {
            alert_data.push_back( it );
        }
        return alert_data;
    }

    TirePressureSensor& TirePressureSensor::setInitialPressure(const double init)
    {
        this->initial = init;
        return *this;
    }
    TirePressureSensor& TirePressureSensor::setPressureDispersion(const double disp)
    {
        this->dispersion = disp;
        return *this;
    }
    TirePressureSensor& TirePressureSensor::setWarningPressureLevel(const double wL)
    {
        this->warningPressureLevel = wL;
        return *this;
    }

    TirePressureSensor* TirePressureSensor::clone() const
    {
        return new TirePressureSensor(*this);
    }
    void TirePressureSensor::accept(SensorVisitor &v)
    {
        v.visit(*this);
    }
    void TirePressureSensor::simulate()
    {
        clear();

        pressures.push_back(initial);
        alert = false;
        double current_pressure = initial;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> pressure_dist(0.0, dispersion / std::sqrt(static_cast<double>(data)));

        for (unsigned int i = 0; i < data; ++i)
        {
            double variation = pressure_dist(gen);
            current_pressure = std::max(0.0, current_pressure + variation);

            if (current_pressure < warningPressureLevel)
            {
                alert = true;
                alertPoints.push_back(i);
            }
            pressures.push_back(current_pressure);
        }
    }
    void TirePressureSensor::clear() 
    {
        pressures.clear();
        alertPoints.clear();
    }
}
