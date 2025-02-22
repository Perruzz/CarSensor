#ifndef SENSOR_WIDGET_H
#define SENSOR_WIDGET_H

#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QObject>
#include <QEvent>
#include <QVBoxLayout>
#include <QPointer>

#include "../Sensor/SensorVisitor.h"
#include "../Sensor/CarSensor.h"
#include "../Sensor/CabinTemperatureSensor.h"
#include "../Sensor/TirePressureSensor.h"
#include "../Sensor/SpeedSensor.h"

namespace View
{
    class SensorWidget : public QWidget, public Sensor::SensorVisitor
    {
    Q_OBJECT
    private:
        const Sensor::CarSensor* current_sensor;
        QPointer<QWidget> current_widget;
        QPointer<QPushButton> delete_button;

        bool is_selected;

    protected:
        bool eventFilter(QObject* obj, QEvent* event) override;

    public:
        SensorWidget();

        void visit(Sensor::CabinTemperatureSensor& CT) override;
        void visit(Sensor::TirePressureSensor& TP) override;
        void visit(Sensor::SpeedSensor& s) override;

        const Sensor::CarSensor* getCurrentSensor() const;
        unsigned int getWidgetID() const;

        QWidget* getCurrentWidget() const;

        bool isEmpty() const;
        void clearCurrentWidget();

        void setSelected(bool selected);

    signals:
        void deleteRequested(unsigned int sensorID);
        void sensorSelected(Sensor::CarSensor* s);
    };
}
#endif
