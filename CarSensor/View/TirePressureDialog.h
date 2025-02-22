#ifndef TIRE_PRESSURE_DIALOG_H
#define TIRE_PRESSURE_DIALOG_H

#include <QLabel>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

#include "../Sensor/CarSensor.h"
#include "../Sensor/TirePressureSensor.h"

namespace View
{
    class TirePressureDialog : public QDialog
    {
    Q_OBJECT

    private:
        QLabel* idLabel;
        QLabel* nameLabel;
        QLabel* dataLabel;
        QLabel* initLabel;
        QLabel* dispLabel;
        QLabel* warningLabel;

        QSpinBox* idSpinBox;
        QLineEdit* nameLineEdit;
        QSpinBox* dataSpinBox;
        QDoubleSpinBox* initSpinBox;
        QDoubleSpinBox* dispSpinBox;
        QDoubleSpinBox* warningSpinBox;

        QHBoxLayout* idLayout;
        QHBoxLayout* nameLayout;
        QHBoxLayout* dataLayout;
        QHBoxLayout* initLayout;
        QHBoxLayout* dispLayout;
        QHBoxLayout* warningLayout;

        QVBoxLayout* mainLayout;
        QHBoxLayout* buttonsLayout;
        QPushButton* discardButton;
        QPushButton* createButton;

    public:
        explicit TirePressureDialog(QWidget* parent = nullptr);
        ~TirePressureDialog() = default;

        void initializeForNewSensor();
        void initializeForExistingSensor(Sensor::TirePressureSensor* sensor);

    public slots:        
        void closeWindow();
        void createAndAddSensor();

    signals:
        void sensorAdded(Sensor::CarSensor* sensor);
    };
}
#endif
