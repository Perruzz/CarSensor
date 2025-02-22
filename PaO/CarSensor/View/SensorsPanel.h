#ifndef SENSORS_PANEL_H
#define SENSORS_PANEL_H

#include <QVector>
#include <QLineEdit>
#include <QScrollArea>

#include "SensorWidget.h"
#include "../Sensor/Json/jsonrepository.h"
#include "TirePressureDialog.h"
#include "CabinTemperatureDialog.h"
#include "SpeedDialog.h"

namespace View
{
    class SensorsPanel : public QWidget
    {
    Q_OBJECT
    private:
        QVector<SensorWidget*> lookup;
        QGridLayout* layout;

        QLineEdit* query;
        QPushButton* search_button;
        QPushButton* sort_button_name;

    public:
        explicit SensorsPanel(QWidget* parent = nullptr);
        ~SensorsPanel() override;

        void addSensor(Sensor::CarSensor* sensor);
        void showList(std::vector<Sensor::CarSensor*> sensors);
        void clean();

    public slots:
        void search();
        void sortName();

        void deleteSensorWidget(unsigned int sensorId);
        void showChartInfo(Sensor::CarSensor* s);

    signals:
        void search_event(std::string query_text);
        void sortName_event();
        void sensorDeleted(unsigned int sensorId);
        void showChartInfoSignal(Sensor::CarSensor* sensor);
    };
}
#endif
