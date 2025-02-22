#include "SpeedDialog.h"

namespace View
{
    SpeedDialog::SpeedDialog(QWidget* parent) : QDialog(parent)
    {
        setWindowTitle("Speed Sensor");

        mainLayout = new QVBoxLayout(this);

        idLayout = new QHBoxLayout;
        idLabel = new QLabel("Identifier:", this);
        idSpinBox = new QSpinBox(this);
        idSpinBox->setRange(0, 9999);
        idSpinBox->setSingleStep(1);
        idLayout->addWidget(idLabel);
        idLayout->addWidget(idSpinBox);

        nameLayout = new QHBoxLayout;
        nameLabel = new QLabel("Sensor Name:", this);
        nameLineEdit = new QLineEdit(this);
        nameLineEdit->setPlaceholderText("Insert");
        nameLayout->addWidget(nameLabel);
        nameLayout->addWidget(nameLineEdit);

        dataLayout = new QHBoxLayout;
        dataLabel = new QLabel("Data:", this);
        dataSpinBox = new QSpinBox(this);
        dataSpinBox->setRange(0, 999999);
        dataSpinBox->setSingleStep(1);
        dataLayout->addWidget(dataLabel);
        dataLayout->addWidget(dataSpinBox);

        initTimeLayout = new QHBoxLayout;
        initTimeLabel = new QLabel("Initial Time(seconds):", this);
        initTimeSpinBox = new QDoubleSpinBox(this);
        initTimeSpinBox->setRange(0.0, std::numeric_limits<double>::max());
        initTimeSpinBox->setSingleStep(60.0);
        initTimeSpinBox->setDecimals(2);
        initTimeLayout->addWidget(initTimeLabel);
        initTimeLayout->addWidget(initTimeSpinBox);

        initDistLayout = new QHBoxLayout;
        initDistLabel = new QLabel("Initial Distance(meters):", this);
        initDistSpinBox = new QDoubleSpinBox(this);
        initDistSpinBox->setRange(0.0, 800000.0);
        initDistSpinBox->setSingleStep(500.0);
        initDistSpinBox->setDecimals(2);
        initDistLayout->addWidget(initDistLabel);
        initDistLayout->addWidget(initDistSpinBox);

        dispTimeLayout = new QHBoxLayout;
        dispTimeLabel = new QLabel("Time Dispersion(seconds):", this);
        dispTimeSpinBox = new QDoubleSpinBox(this);
        dispTimeSpinBox->setRange(0.0, std::numeric_limits<double>::max());
        dispTimeSpinBox->setSingleStep(60.0);
        dispTimeSpinBox->setDecimals(2);
        dispTimeLayout->addWidget(dispTimeLabel);
        dispTimeLayout->addWidget(dispTimeSpinBox);

        dispDistLayout = new QHBoxLayout;
        dispDistLabel = new QLabel("Distance Dispersion(meters):", this);
        dispDistSpinBox = new QDoubleSpinBox(this);
        dispDistSpinBox->setRange(0.0, 800000.0);
        dispDistSpinBox->setSingleStep(500.0);
        dispDistSpinBox->setDecimals(2);
        dispDistLayout->addWidget(dispDistLabel);
        dispDistLayout->addWidget(dispDistSpinBox);

        buttonsLayout = new QHBoxLayout;
        createButton = new QPushButton("Apply", this);
        createButton->setShortcut(Qt::Key_Enter);
        connect(createButton, &QPushButton::clicked, this, &SpeedDialog::createAndAddSensor);

        discardButton = new QPushButton("Cancel", this);
        discardButton->setShortcut(Qt::Key_Escape);
        connect(discardButton, &QPushButton::clicked, this, &SpeedDialog::closeWindow);

        buttonsLayout->addWidget(discardButton);
        buttonsLayout->addWidget(createButton);

        mainLayout->addLayout(idLayout);
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(dataLayout);
        mainLayout->addLayout(initTimeLayout);
        mainLayout->addLayout(initDistLayout);
        mainLayout->addLayout(dispTimeLayout);
        mainLayout->addLayout(dispDistLayout);
        mainLayout->addLayout(buttonsLayout);

        setLayout(mainLayout);
        setFixedSize(470, 320);

        initializeForNewSensor();
    }

    void SpeedDialog::initializeForNewSensor()
    {
        idSpinBox->setValue(0);
        dataSpinBox->setValue(50);
        initTimeSpinBox->setValue(900.0);
        initDistSpinBox->setValue(10000.0);
        dispTimeSpinBox->setValue(240.0);
        dispDistSpinBox->setValue(1000.0);
    }
    void SpeedDialog::initializeForExistingSensor(Sensor::SpeedSensor* sensor)
    {
        idSpinBox->setValue(sensor->getIdentifier());
        idSpinBox->setEnabled(false);
        nameLineEdit->setText(QString::fromStdString(sensor->getSensorName()));
        nameLineEdit->setEnabled(false);
        dataSpinBox->setValue(sensor->getData());
        initTimeSpinBox->setValue(sensor->getInitialTime());
        initDistSpinBox->setValue(sensor->getInitialDist());
        dispTimeSpinBox->setValue(sensor->getTimeDispersion());
        dispDistSpinBox->setValue(sensor->getDistDispersion());
    }

    void SpeedDialog::closeWindow()
    {
        setAttribute(Qt::WA_DeleteOnClose);
        close();
    }
    void SpeedDialog::createAndAddSensor()
    {
        unsigned int id = idSpinBox->value();
        string name = nameLineEdit->text().toStdString();
        unsigned int data = dataSpinBox->value();
        double initT = initTimeSpinBox->value();
        double initD = initDistSpinBox->value();
        double dispT = dispTimeSpinBox->value();
        double dispD = dispDistSpinBox->value();

        Sensor::CarSensor* sensor = new Sensor::SpeedSensor(id, name, data, Sensor::Speed(initT, initD), Sensor::Speed(dispT, dispD));
        emit sensorAdded(sensor);

        setAttribute(Qt::WA_DeleteOnClose);
        close();
    }
}
