#include "TirePressureDialog.h"

namespace View
{
    TirePressureDialog::TirePressureDialog(QWidget* parent) : QDialog(parent)
    {
        setWindowTitle("Tire Pressure Sensor");

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

        initLayout = new QHBoxLayout;
        initLabel = new QLabel("Initial(bar):", this);
        initSpinBox = new QDoubleSpinBox(this);
        initSpinBox->setRange(0.0, 30.0);
        initSpinBox->setSingleStep(0.2);
        initSpinBox->setDecimals(2);
        initLayout->addWidget(initLabel);
        initLayout->addWidget(initSpinBox);

        dispLayout = new QHBoxLayout;
        dispLabel = new QLabel("Dispersion(bar):", this);
        dispSpinBox = new QDoubleSpinBox(this);
        dispSpinBox->setRange(0.0, 30.0);
        dispSpinBox->setSingleStep(0.2);
        dispSpinBox->setDecimals(2);
        dispLayout->addWidget(dispLabel);
        dispLayout->addWidget(dispSpinBox);

        warningLayout = new QHBoxLayout;
        warningLabel = new QLabel("Warning Level(bar):", this);
        warningSpinBox = new QDoubleSpinBox(this);
        warningSpinBox->setRange(0.0, 25.0);
        warningSpinBox->setSingleStep(0.2);
        warningSpinBox->setDecimals(2);
        warningLayout->addWidget(warningLabel);
        warningLayout->addWidget(warningSpinBox);

        buttonsLayout = new QHBoxLayout;
        createButton = new QPushButton("Apply", this);
        createButton->setShortcut(Qt::Key_Enter);
        connect(createButton, &QPushButton::clicked, this, &TirePressureDialog::createAndAddSensor);

        discardButton = new QPushButton("Cancel", this);
        discardButton->setShortcut(Qt::Key_Escape);
        connect(discardButton, &QPushButton::clicked, this, &TirePressureDialog::closeWindow);

        buttonsLayout->addWidget(discardButton);
        buttonsLayout->addWidget(createButton);

        mainLayout->addLayout(idLayout);
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(dataLayout);
        mainLayout->addLayout(initLayout);
        mainLayout->addLayout(dispLayout);
        mainLayout->addLayout(warningLayout);
        mainLayout->addLayout(buttonsLayout);

        setLayout(mainLayout);
        setFixedSize(400, 270);

        initializeForNewSensor();
    }

    void TirePressureDialog::initializeForNewSensor()
    {
        idSpinBox->setValue(0);
        dataSpinBox->setValue(50);
        initSpinBox->setValue(2.0);
        dispSpinBox->setValue(5.0);
        warningSpinBox->setValue(2.4);
    }
    void TirePressureDialog::initializeForExistingSensor(Sensor::TirePressureSensor* sensor)
    {
        idSpinBox->setValue(sensor->getIdentifier());
        idSpinBox->setEnabled(false);
        nameLineEdit->setText(QString::fromStdString(sensor->getSensorName()));
        nameLineEdit->setEnabled(false);
        dataSpinBox->setValue(sensor->getData());
        initSpinBox->setValue(sensor->getInitialPressure());
        dispSpinBox->setValue(sensor->getPressureDispersion());
        warningSpinBox->setValue(sensor->getWarningPressureLevel());
    }

    void TirePressureDialog::closeWindow()
    {
        setAttribute(Qt::WA_DeleteOnClose);
        close();
    }
    void TirePressureDialog::createAndAddSensor()
    {
        unsigned int id = idSpinBox->value();
        string name = nameLineEdit->text().toStdString();
        unsigned int data = dataSpinBox->value();
        double init = initSpinBox->value();
        double disp = dispSpinBox->value();
        double warning = warningSpinBox->value();

        Sensor::CarSensor* sensor = new Sensor::TirePressureSensor(id, name, data, init, disp, warning);
        emit sensorAdded(sensor);

        setAttribute(Qt::WA_DeleteOnClose);
        close();
    }
}
