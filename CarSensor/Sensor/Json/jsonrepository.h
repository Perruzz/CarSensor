#ifndef JSON_REPOSITORY_H
#define JSON_REPOSITORY_H

#include <stdexcept>

#include "../CarSensor.h"
#include "jsonfile.h"
#include "reader.h"

using namespace std;

namespace Sensor::Json
{
    class JsonRepository
    {
    private:
        JsonFile data_mapper;
        map<unsigned int, CarSensor*> repository;

    public:
        JsonRepository(JsonFile d_m);
        ~JsonRepository();

        void create(CarSensor* sensor);
        void remove(const unsigned int identifier);
        void update(CarSensor* sensor);

        CarSensor* read(const unsigned int identifier) const;
        vector<CarSensor*> readAll() const;

        static JsonRepository fromPath(const string path);
        const string& getPath() const;
        void setPath(string path);

        const JsonFile& getDataMapper() const;
        const map<unsigned int, CarSensor*>& getRepository() const;

        void overwrite(const vector<Sensor::CarSensor*> newSensors);
        void store();
        void load();
    };
}

#endif
