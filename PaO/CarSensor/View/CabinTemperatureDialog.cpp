#include "CabinTemperatureDialog.h"

namespace View
{
    CabinTemperatureDialog::CabinTemperatureDialog(QWidget* parent) : QDialog(parent)
    {
        setWindowTitle("Cabin Temperature Sensor");

        mainLayout = new QVBoxLayout(this);

        scaleLayout = new QHBoxLayout;
        celsiusRadioButton = new QRadioButton("C°", this);
        fahrenheitRadioButton = new QRadioButton("F°", this);
        scaleButtonGroup = new QButtonGroup(this);
        scaleButtonGroup->addButton(celsiusRadioButton, 0);
        scaleButtonGroup->addButton(fahrenheitRadioButton, 1);
        celsiusRadioButton->setChecked(true);
        scaleLayout->addWidget(celsiusRadioButton);
        scaleLayout->addWidget(fahrenheitRadioButton);

        connect(celsiusRadioButton, &QRadioButton::toggled, this, &CabinTemperatureDialog::updateRanges);
        connect(fahrenheitRadioButton, &QRadioButton::toggled, this, &CabinTemperatureDialog::updateRanges);

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
        initLabel = new QLabel("Initial:", this);
        initSpinBox = new QDoubleSpinBox(this);
        initSpinBox->setSingleStep(1.0);
        initSpinBox->setDecimals(2);
        initLayout->addWidget(initLabel);
        initLayout->addWidget(initSpinBox);

        dispLayout = new QHBoxLayout;
        dispLabel = new QLabel("Dispersion:", this);
        dispSpinBox = new QDoubleSpinBox(this);
        dispSpinBox->setSingleStep(1.0);
        dispSpinBox->setDecimals(2);
        dispLayout->addWidget(dispLabel);
        dispLayout->addWidget(dispSpinBox);

        minLayout = new QHBoxLayout;
        minLabel = new QLabel("Min:", this);
        minSpinBox = new QDoubleSpinBox(this);
        minSpinBox->setSingleStep(1.0);
        minSpinBox->setDecimals(2);
        minLayout->addWidget(minLabel);
        minLayout->addWidget(minSpinBox);

        maxLayout = new QHBoxLayout;
        maxLabel = new QLabel("Max:", this);
        maxSpinBox = new QDoubleSpinBox(this);
        maxSpinBox->setSingleStep(1.0);
        maxSpinBox->setDecimals(2);
        maxLayout->addWidget(maxLabel);
        maxLayout->addWidget(maxSpinBox);

        buttonsLayout = new QHBoxLayout;
        createButton = new QPushButton("Apply", this);
        createButton->setShortcut(Qt::Key_Enter);
        connect(createButton, &QPushButton::clicked, this, &CabinTemperatureDialog::createAndAddSensor);

        discardButton = new QPushButton("Cancel", this);
        discardButton->setShortcut(Qt::Key_Escape);
        connect(discardButton, &QPushButton::clicked, this, &CabinTemperatureDialog::closeWindow);

        buttonsLayout->addWidget(discardButton);
        buttonsLayout->addWidget(createButton);

        mainLayout->addLayout(scaleLayout);
        mainLayout->addLayout(idLayout);
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(dataLayout);
        mainLayout->addLayout(initLayout);
        mainLayout->addLayout(dispLayout);
        mainLayout->addLayout(minLayout);
        mainLayout->addLayout(maxLayout);
        mainLayout->addLayout(buttonsLayout);

        setLayout(mainLayout);
        setFixedSize(400, 330);

        updateRanges();
        initializeForNewSensor();
    }

    void CabinTemperatureDialog::initializeForNewSensor()
    {
        idSpinBox->setValue(0);
        dataSpinBox->setValue(50);
        initSpinBox->setValue(10.0);
        dispSpinBox->setValue(20.0);
        minSpinBox->setValue(-10.0);
        maxSpinBox->setValue(35.0);
    }
    void CabinTemperatureDialog::initializeForExistingSensor(Sensor::CabinTemperatureSensor* sensor)
    {
        char scale = sensor->getScale();
        scale == 'c' ? celsiusRadioButton->setChecked(true) : fahrenheitRadioButton->setChecked(true);
        idSpinBox->setValue(sensor->getIdentifier());
        idSpinBox->setEnabled(false);
        nameLineEdit->setText(QString::fromStdString(sensor->getSensorName()));
        nameLineEdit->setEnabled(false);
        dataSpinBox->setValue(sensor->getData());
        initSpinBox->setValue(sensor->getInitialTemp().getTemp(scale));
        dispSpinBox->setValue(sensor->getTempDispersion().getTemp(scale));
        minSpinBox->setValue(sensor->getMin().getTemp(scale));
        maxSpinBox->setValue(sensor->getMax().getTemp(scale));
    }

    void CabinTemperatureDialog::updateRanges()
    {
        static bool isCelsius = true;

        if (celsiusRadioButton->isChecked())
        {
            if (!isCelsius)
            {
                initSpinBox->setValue((initSpinBox->value() - 32.0) * (5.0 / 9.0));
                dispSpinBox->setValue((dispSpinBox->value() - 32.0) * (5.0 / 9.0));
                minSpinBox->setValue((minSpinBox->value() - 32.0) * (5.0 / 9.0));
                maxSpinBox->setValue((maxSpinBox->value() - 32.0) * (5.0 / 9.0));
                isCelsius = true;
            }

            initSpinBox->setRange(-273.15, 100.0);
            dispSpinBox->setRange(-273.15, 100.0);
            minSpinBox->setRange(-273.15, 100.0);
            maxSpinBox->setRange(-273.15, 100.0);
        }
        else
        {
            if (isCelsius)
            {
                initSpinBox->setValue((initSpinBox->value() * (9.0 / 5.0)) + 32.0);
                dispSpinBox->setValue((dispSpinBox->value() * (9.0 / 5.0)) + 32.0);
                minSpinBox->setValue((minSpinBox->value() * (9.0 / 5.0)) + 32.0);
                maxSpinBox->setValue((maxSpinBox->value() * (9.0 / 5.0)) + 32.0);
                isCelsius = false;
            }

            initSpinBox->setRange(-459.67, 212.0);
            dispSpinBox->setRange(-459.67, 212.0);
            minSpinBox->setRange(-459.67, 212.0);
            maxSpinBox->setRange(-459.67, 212.0);
        }
    }
    void CabinTemperatureDialog::closeWindow()
    {
        setAttribute(Qt::WA_DeleteOnClose);
        close();
    }
    void CabinTemperatureDialog::createAndAddSensor()
    {
        unsigned int id = idSpinBox->value();
        string name = nameLineEdit->text().toStdString();
        unsigned int data = dataSpinBox->value();
        double init = initSpinBox->value();
        double stddev = dispSpinBox->value();
        double min = minSpinBox->value();
        double max = maxSpinBox->value();
        char scale = celsiusRadioButton->isChecked() ? 'c' : 'f';

        Sensor::CarSensor* sensor = new Sensor::CabinTemperatureSensor(id, name, data, Sensor::Temperature(init, scale), Sensor::Temperature(stddev, scale), Sensor::Temperature(min, scale), Sensor::Temperature(max, scale), scale);
        emit sensorAdded(sensor);

        setAttribute(Qt::WA_DeleteOnClose);
        close();
    }
}
