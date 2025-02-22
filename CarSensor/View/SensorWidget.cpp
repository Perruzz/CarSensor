#include "SensorWidget.h"

namespace View
{
    bool SensorWidget::eventFilter(QObject* obj, QEvent* event)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if (obj == current_widget)
            {
                setSelected(true);
                emit sensorSelected(const_cast<Sensor::CarSensor*>(current_sensor));
                return true;
            }
        }
        return QObject::eventFilter(obj, event);
    }

    SensorWidget::SensorWidget() : current_widget(nullptr), delete_button(nullptr), is_selected(false){}

    void SensorWidget::visit(Sensor::CabinTemperatureSensor& CT)
    {
        current_sensor = &CT;

        current_widget = new QGroupBox();
        QGridLayout* grid = new QGridLayout();

        current_widget->setMinimumWidth(220);

        QLabel* nameLabel = new QLabel("Name:");
        QLabel* idLabel = new QLabel("ID:");

        nameLabel->setAlignment(Qt::AlignLeft);
        idLabel->setAlignment(Qt::AlignLeft);

        QLabel* nameValue = new QLabel(QString::fromStdString(CT.getSensorName()));
        QLabel* idValue = new QLabel(QString::number(CT.getIdentifier()));

        nameValue->setAlignment(Qt::AlignLeft);
        idValue->setAlignment(Qt::AlignLeft);

        QHBoxLayout* nameLayout = new QHBoxLayout();
        nameLayout->addWidget(nameLabel);
        nameLayout->addWidget(nameValue);
        nameLayout->addStretch();

        QHBoxLayout* idLayout = new QHBoxLayout();
        idLayout->addWidget(idLabel);
        idLayout->addWidget(idValue);
        idLayout->addStretch();

        QLabel* icon = new QLabel();
        icon->setPixmap(QIcon(":/Icons/cabin_temperature_sensor_icon.svg").pixmap(50, 50));

        delete_button = new QPushButton(QIcon(":/Icons/delete_icon.svg"), " Delete");
        delete_button->setFixedWidth(80);
        delete_button->setStyleSheet("color: red;");

        QVBoxLayout* mainLayout = new QVBoxLayout();
        mainLayout->addStretch();
        mainLayout->addWidget(delete_button, 0, Qt::AlignRight | Qt::AlignBottom);

        grid->addWidget(icon, 0, 0, 4, 1);
        grid->addLayout(nameLayout, 0, 1, 1, 1);
        grid->addLayout(idLayout, 1, 1, 1, 1);
        grid->addLayout(mainLayout, 2, 1, 2, 1);

        current_widget->setLayout(grid);

        current_widget->installEventFilter(this);

        connect(delete_button, &QPushButton::clicked, this, [this]() { emit deleteRequested(current_sensor->getIdentifier()); } );
    }
    void SensorWidget::visit(Sensor::TirePressureSensor& TP)
    {
        current_sensor = &TP;

        current_widget = new QGroupBox();
        QGridLayout* grid = new QGridLayout();

        current_widget->setMinimumWidth(220);

        QLabel* nameLabel = new QLabel("Name:");
        QLabel* idLabel = new QLabel("ID:");

        nameLabel->setAlignment(Qt::AlignLeft);
        idLabel->setAlignment(Qt::AlignLeft);

        QLabel* nameValue = new QLabel(QString::fromStdString(TP.getSensorName()));
        QLabel* idValue = new QLabel(QString::number(TP.getIdentifier()));

        nameValue->setAlignment(Qt::AlignLeft);
        idValue->setAlignment(Qt::AlignLeft);

        QHBoxLayout* nameLayout = new QHBoxLayout();
        nameLayout->addWidget(nameLabel);
        nameLayout->addWidget(nameValue);
        nameLayout->addStretch();

        QHBoxLayout* idLayout = new QHBoxLayout();
        idLayout->addWidget(idLabel);
        idLayout->addWidget(idValue);
        idLayout->addStretch();

        QLabel* icon = new QLabel();
        icon->setPixmap(QIcon(":/Icons/tire_pressure_sensor_icon.svg").pixmap(50, 50));

        delete_button = new QPushButton(QIcon(":/Icons/delete_icon.svg"), " Delete");
        delete_button->setFixedWidth(80);
        delete_button->setStyleSheet("color: red;");

        QVBoxLayout* mainLayout = new QVBoxLayout();
        mainLayout->addStretch();
        mainLayout->addWidget(delete_button, 0, Qt::AlignRight | Qt::AlignBottom);

        grid->addWidget(icon, 0, 0, 4, 1);
        grid->addLayout(nameLayout, 0, 1, 1, 1);
        grid->addLayout(idLayout, 1, 1, 1, 1);
        grid->addLayout(mainLayout, 2, 1, 2, 1);

        current_widget->setLayout(grid);

        current_widget->installEventFilter(this);

        connect(delete_button, &QPushButton::clicked, this, [this]() { emit deleteRequested(current_sensor->getIdentifier()); } );
    }
    void SensorWidget::visit(Sensor::SpeedSensor& s)
    {
        current_sensor = &s;

        current_widget = new QGroupBox();
        QGridLayout* grid = new QGridLayout();

        current_widget->setMinimumWidth(220);

        QLabel* nameLabel = new QLabel("Name:");
        QLabel* idLabel = new QLabel("ID:");

        nameLabel->setAlignment(Qt::AlignLeft);
        idLabel->setAlignment(Qt::AlignLeft);

        QLabel* nameValue = new QLabel(QString::fromStdString(s.getSensorName()));
        QLabel* idValue = new QLabel(QString::number(s.getIdentifier()));

        nameValue->setAlignment(Qt::AlignLeft);
        idValue->setAlignment(Qt::AlignLeft);

        QHBoxLayout* nameLayout = new QHBoxLayout();
        nameLayout->addWidget(nameLabel);
        nameLayout->addWidget(nameValue);
        nameLayout->addStretch();

        QHBoxLayout* idLayout = new QHBoxLayout();
        idLayout->addWidget(idLabel);
        idLayout->addWidget(idValue);
        idLayout->addStretch();

        QLabel* icon = new QLabel();
        icon->setPixmap(QIcon(":/Icons/speed_sensor_icon.svg").pixmap(50, 50));

        delete_button = new QPushButton(QIcon(":/Icons/delete_icon.svg"), " Delete");
        delete_button->setFixedWidth(80);
        delete_button->setStyleSheet("color: red;");

        QVBoxLayout* mainLayout = new QVBoxLayout();
        mainLayout->addStretch();
        mainLayout->addWidget(delete_button, 0, Qt::AlignRight | Qt::AlignBottom);

        grid->addWidget(icon, 0, 0, 4, 1);
        grid->addLayout(nameLayout, 0, 1, 1, 1);
        grid->addLayout(idLayout, 1, 1, 1, 1);
        grid->addLayout(mainLayout, 2, 1, 2, 1);

        current_widget->setLayout(grid);

        current_widget->installEventFilter(this);

        connect(delete_button, &QPushButton::clicked, this, [this]() { emit deleteRequested(current_sensor->getIdentifier()); } );
    }

    const Sensor::CarSensor* SensorWidget::getCurrentSensor() const
    {
        return current_sensor;
    }
    unsigned int SensorWidget::getWidgetID() const
    {
        return current_sensor->getIdentifier();
    }

    QWidget* SensorWidget::getCurrentWidget() const
    {
        return current_widget;
    }

    bool SensorWidget::isEmpty() const
    {
        return current_sensor == nullptr;
    }
    void SensorWidget::setSelected(bool selected)
    {
        is_selected = selected;
        if (is_selected)
        {
            current_widget->setStyleSheet("background-color: #DFEFFF;");
        }
        else
        {
            current_widget->setStyleSheet("");
        }
    }
}
