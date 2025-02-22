#ifndef JSON_FILE_H
#define JSON_FILE_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

#include "../CarSensor.h"
#include "json.h"

namespace Sensor::Json
{
    class JsonFile
    {
    private:
        string path;

    public:
        JsonFile(string  p);

        static JsonFile fromPath(const string& p);

        const string& getPath() const;
        void setPath(const string& p);

        void store(const vector<CarSensor*> s);
        vector<CarSensor*> load();
    };
}
#endif
