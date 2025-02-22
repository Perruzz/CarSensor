#ifndef CABIN_TEMPERATURE_DIALOG_H
#define CABIN_TEMPERATURE_DIALOG_H

#include <QLabel>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QRadioButton>
#include <QButtonGroup>

#include "../Sensor/CarSensor.h"
#include "../Sensor/CabinTemperatureSensor.h"

namespace View
{
    class CabinTemperatureDialog : public QDialog
    {
    Q_OBJECT

    private:
        QRadioButton* celsiusRadioButton;
        QRadioButton* fahrenheitRadioButton;

        QButtonGroup* scaleButtonGroup;

        QLabel* idLabel;
        QLabel* nameLabel;
        QLabel* dataLabel;
        QLabel* initLabel;
        QLabel* dispLabel;
        QLabel* minLabel;
        QLabel* maxLabel;

        QSpinBox* idSpinBox;
        QLineEdit* nameLineEdit;
        QSpinBox* dataSpinBox;
        QDoubleSpinBox* initSpinBox;
        QDoubleSpinBox* dispSpinBox;
        QDoubleSpinBox* minSpinBox;
        QDoubleSpinBox* maxSpinBox;

        QHBoxLayout* scaleLayout;
        QHBoxLayout* idLayout;
        QHBoxLayout* nameLayout;
        QHBoxLayout* dataLayout;
        QHBoxLayout* initLayout;
        QHBoxLayout* dispLayout;
        QHBoxLayout* minLayout;
        QHBoxLayout* maxLayout;

        QVBoxLayout* mainLayout;
        QHBoxLayout* buttonsLayout;
        QPushButton* discardButton;
        QPushButton* createButton;

    public:
        explicit CabinTemperatureDialog(QWidget* parent = nullptr);
        ~CabinTemperatureDialog() = default;

        void initializeForNewSensor();
        void initializeForExistingSensor(Sensor::CabinTemperatureSensor* sensor);      

    public slots:
        void updateRanges();
        void closeWindow();
        void createAndAddSensor();

    signals:
        void sensorAdded(Sensor::CarSensor* sensor);
    };
}
#endif
