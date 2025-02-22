#ifndef SPEED_DIALOG_H
#define SPEED_DIALOG_H

#include <QLabel>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

#include "../Sensor/CarSensor.h"
#include "../Sensor/SpeedSensor.h"

namespace View
{
    class SpeedDialog : public QDialog
    {
    Q_OBJECT

    private:
        QLabel* idLabel;
        QLabel* nameLabel;
        QLabel* dataLabel;
        QLabel* initTimeLabel;
        QLabel* initDistLabel;
        QLabel* dispTimeLabel;
        QLabel* dispDistLabel;

        QSpinBox* idSpinBox;
        QLineEdit* nameLineEdit;
        QSpinBox* dataSpinBox;
        QDoubleSpinBox* initTimeSpinBox;
        QDoubleSpinBox* initDistSpinBox;
        QDoubleSpinBox* dispTimeSpinBox;
        QDoubleSpinBox* dispDistSpinBox;

        QHBoxLayout* idLayout;
        QHBoxLayout* nameLayout;
        QHBoxLayout* dataLayout;
        QHBoxLayout* initTimeLayout;
        QHBoxLayout* initDistLayout;
        QHBoxLayout* dispTimeLayout;
        QHBoxLayout* dispDistLayout;

        QVBoxLayout* mainLayout;
        QHBoxLayout* buttonsLayout;
        QPushButton* discardButton;
        QPushButton* createButton;

    public:
        explicit SpeedDialog(QWidget* parent = nullptr);
        ~SpeedDialog() = default;

        void initializeForNewSensor();
        void initializeForExistingSensor(Sensor::SpeedSensor* sensor);

    public slots:
        void closeWindow();
        void createAndAddSensor();

    signals:       
        void sensorAdded(Sensor::CarSensor* sensor);
    };
}
#endif
