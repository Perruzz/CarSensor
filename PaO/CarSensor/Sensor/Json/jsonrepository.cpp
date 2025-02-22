#include "jsonrepository.h"

namespace Sensor::Json
{
    JsonRepository::JsonRepository(JsonFile d_m) : data_mapper(d_m)
    {
        load();
    }
    JsonRepository::~JsonRepository()
    {
        for(const auto& it : repository)
        {
            delete it.second;
        }
        repository.clear();
    }

    void JsonRepository::create(CarSensor* sensor)
    {
        repository[sensor->getIdentifier()] = sensor;
    }
    void JsonRepository::remove(const unsigned int identifier)
    {
        auto it = repository.find(identifier);
        if (it != repository.end())
        {
            delete it->second;
            repository.erase(it);
        }
    }
    void JsonRepository::update(CarSensor* sensor)
    {
        create(sensor);
    }

    CarSensor* JsonRepository::read(const unsigned int identifier) const
    {
        auto it = repository.find(identifier);
        if (it == repository.end())
        {
            throw std::out_of_range("trying to read undefined id");
        }
        return it->second;
    }
    vector<CarSensor*> JsonRepository::readAll() const
    {
        vector<CarSensor*> sensors;
        for (const auto& it : repository)
        {
            sensors.push_back(it.second);
        }
        return sensors;
    }

    JsonRepository JsonRepository::fromPath(const string path)
    {
        JsonFile data_mapper = JsonFile::fromPath(path);
        return JsonRepository(data_mapper);
    }
    const string& JsonRepository::getPath() const
    {
        return data_mapper.getPath();
    }
    void JsonRepository::setPath(string path)
    {
        data_mapper.setPath(path);
    }

    const JsonFile& JsonRepository::getDataMapper() const
    {
        return data_mapper;
    }
    const map<unsigned int, CarSensor*>& JsonRepository::getRepository() const
    {
        return repository;
    }

    void JsonRepository::overwrite(const vector<Sensor::CarSensor*> newSensors)
    {
        for (const auto& pair : repository)
        {
            delete pair.second;
        }
        repository.clear();

        for (CarSensor* sensor : newSensors)
        {
            CarSensor* clonedSensor = sensor->clone();
            repository[clonedSensor->getIdentifier()] = clonedSensor;
        }
    }
    void JsonRepository::store()
    {
        data_mapper.store(readAll());
    }
    void JsonRepository::load()
    {
        vector<CarSensor*> sensors(data_mapper.load());
        for(CarSensor* it : sensors)
        {
            repository[it->getIdentifier()] = it;
        }
    }
}
