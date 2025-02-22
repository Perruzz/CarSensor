#ifndef CHART_INFO_H
#define CHART_INFO_H

#include <QGridLayout>
#include <QtCharts>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPainter>

#include "../Sensor/CarSensor.h"
#include "TirePressureDialog.h"
#include "CabinTemperatureDialog.h"
#include "SpeedDialog.h"
#include "Chart.h"

namespace View
{
    class ChartInfo : public QWidget, public Sensor::SensorVisitor
    {
    Q_OBJECT

    private:
        Sensor::CarSensor* current_sensor;
        QLabel* data;
        QPushButton* simulate_button;
        QPushButton* edit_button;

        Chart* chart;

        TirePressureDialog* editTP;
        SpeedDialog* editS;
        CabinTemperatureDialog* editCT;

        bool editMode;

    private slots:
        void onSimulateClicked(Sensor::CarSensor* sensor);

    public:
        ChartInfo();
        ~ChartInfo();

        void visit(Sensor::CabinTemperatureSensor& CT) override;
        void visit(Sensor::TirePressureSensor& TP) override;
        void visit(Sensor::SpeedSensor& s) override;

        QLabel* getData() const;
        QPushButton* getSimulateButton() const;
        QPushButton* getEditButton() const;
        Chart* getChart() const;

    public slots:
        void onEditClicked(Sensor::CarSensor* s);
        void editChartInfo(Sensor::CarSensor* s);

    signals:
        void editSignalCI(Sensor::CarSensor* s);
    };
}
#endif