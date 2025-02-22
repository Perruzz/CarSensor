#include "jsonfile.h"

namespace Sensor::Json
{
    JsonFile::JsonFile(string p) : path(p) {}

    JsonFile JsonFile::fromPath(const string& p)
    {
        JsonFile data_mapper(p);
        return data_mapper;
    }

    const string& JsonFile::getPath() const
    {
        return path;
    }
    void JsonFile::setPath(const string& p)
    {
        this->path = p;
    }

    void JsonFile::store(const vector<CarSensor*> s)
    {
        QJsonArray json_sensors;
        for(const CarSensor* it : s)
        {
            json_sensors.push_back(Json::fromObject(*it));
        }
        QJsonDocument document(json_sensors);
        QFile json_file(path.c_str());
        json_file.open(QFile::WriteOnly);
        json_file.write(document.toJson());
        json_file.close();
    }
    vector<CarSensor*> JsonFile::load()
    {
        vector<CarSensor*> sensors;
        QFile json_file(path.c_str());
        json_file.open(QFile::ReadOnly);
        QByteArray data = json_file.readAll();
        json_file.close();
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonArray json_sensors = document.array();
        for (const QJsonValue& it: json_sensors)
        {
            QJsonObject json_object = it.toObject();
            sensors.push_back(&(Json::toObject(json_object)));
        }
        return sensors;
    }
}
