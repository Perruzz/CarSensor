#include "ChartInfo.h"

namespace View
{
    void ChartInfo::onSimulateClicked(Sensor::CarSensor* sensor)
    {
        if (sensor)
        {
            sensor->simulate();
            chart->update(sensor);
        }
    }

    ChartInfo::ChartInfo()
    : data(nullptr), simulate_button(nullptr), edit_button(nullptr), chart(nullptr), editMode(false){}
    ChartInfo::~ChartInfo()
    {
        delete data;
        delete simulate_button;
        delete edit_button;
        delete chart;
    }

    void ChartInfo::visit(Sensor::CabinTemperatureSensor& CT)
    {
        current_sensor = &CT;
        QVBoxLayout* layout = new QVBoxLayout(this);

        QWidget* topWidget = new QWidget();
        QHBoxLayout* topLayout = new QHBoxLayout(topWidget);

        simulate_button = new QPushButton(QIcon(QPixmap((":/Icons/simulate_icon.svg"))), "");
        edit_button = new QPushButton(QIcon(QPixmap((":/Icons/edit_icon.svg"))), "");

        QSize iconSize(40, 40); QSize iconSize1(32, 32);
        simulate_button->setIconSize(iconSize);
        edit_button->setIconSize(iconSize1);
        simulate_button->setToolTip("Simulate");
        edit_button->setToolTip("Edit");

        simulate_button->setAttribute(Qt::WA_Hover, true);
        edit_button->setAttribute(Qt::WA_Hover, true);

        simulate_button->setFixedSize(50, 50);
        edit_button->setFixedSize(50, 50);

        topLayout->addWidget(simulate_button);
        topLayout->addStretch();
        topLayout->addWidget(edit_button);

        QLabel* type = new QLabel("CABIN TEMPERATURE SENSOR");
        type->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        QFont font = type->font();
        font.setBold(true);
        type->setFont(font);

        layout->addWidget(topWidget);
        layout->addWidget(type);

        QWidget* dataWidget = new QWidget();
        QGridLayout* dataLayout = new QGridLayout(dataWidget);

        data = new QLabel("Data: " + QString::number(CT.getData()));

        QLabel* initial, *dispersion, *min, *max, *sim_scale;

        char scale = CT.getScale();

        initial = new QLabel("Initial: " + QString::number(CT.getInitialTemp().getTemp(scale)) + (scale == 'c' ? " C°" : " F°"));
        dispersion = new QLabel("Dispersion: " + QString::number(CT.getTempDispersion().getTemp(scale)) + (scale == 'c' ? " C°" : " F°"));
        min = new QLabel("Min: " + QString::number(CT.getMin().getTemp(scale)) + (scale == 'c' ? " C°" : " F°"));
        max = new QLabel("Max: " + QString::number(CT.getMax().getTemp(scale)) + (scale == 'c' ? " C°" : " F°"));
        sim_scale = scale == 'c' ? new QLabel("Celsius(C°)") : new QLabel("Fahrenheit(F°)");

        dataLayout->addWidget(data, 0, 0);
        dataLayout->addWidget(initial, 1, 0);
        dataLayout->addWidget(dispersion, 2, 0);
        dataLayout->addWidget(min, 0, 1);
        dataLayout->addWidget(max, 1, 1);
        dataLayout->addWidget(sim_scale, 2, 1);

        layout->addWidget(dataWidget);

        if(chart)
        {
            chart = nullptr;
            delete chart;
        }
        chart = new Chart();

        chart->setChart(new QChart());
        chart->setXAxis(new QValueAxis());
        chart->getXAxis()->setTitleText("Data");
        chart->getXAxis()->setRange(0, 100);
        chart->setYAxis(new QValueAxis());
        chart->getYAxis()->setRange(0, 100);

        chart->getChart()->addAxis(chart->getXAxis(), Qt::AlignBottom);
        chart->getChart()->addAxis(chart->getYAxis(), Qt::AlignLeft);

        chart->setChartView(new QChartView(chart->getChart()));
        chart->getChartView()->setRenderHint(QPainter::Antialiasing);
        chart->getChartView()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        layout->addWidget(chart->getChartView());
        connect(simulate_button, &QPushButton::clicked, this, [this]() { onSimulateClicked(current_sensor); });
        connect(edit_button, &QPushButton::clicked, this, [this]() { onEditClicked(current_sensor);});

        if(editMode)
        {
            editCT = new CabinTemperatureDialog(this);
            editCT->initializeForExistingSensor(&CT);
            connect(editCT, &CabinTemperatureDialog::sensorAdded, this, &ChartInfo::editChartInfo);
            editCT->exec();
        }
    }
    void ChartInfo::visit(Sensor::TirePressureSensor& TP)
    {
        current_sensor = &TP;
        QVBoxLayout* layout = new QVBoxLayout(this);

        QWidget* topWidget = new QWidget();
        QHBoxLayout* topLayout = new QHBoxLayout(topWidget);

        simulate_button = new QPushButton(QIcon(QPixmap((":/Icons/simulate_icon.svg"))), "");
        edit_button = new QPushButton(QIcon(QPixmap((":/Icons/edit_icon.svg"))), "");

        QSize iconSize(40, 40); QSize iconSize1(32, 32);
        simulate_button->setIconSize(iconSize);
        edit_button->setIconSize(iconSize1);
        simulate_button->setToolTip("Simulate");
        edit_button->setToolTip("Edit");

        simulate_button->setAttribute(Qt::WA_Hover, true);
        edit_button->setAttribute(Qt::WA_Hover, true);

        simulate_button->setFixedSize(50, 50);
        edit_button->setFixedSize(50, 50);

        topLayout->addWidget(simulate_button);
        topLayout->addStretch();
        topLayout->addWidget(edit_button);

        QLabel* type = new QLabel("TIRE PRESSURE SENSOR");
        type->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        QFont font = type->font();
        font.setBold(true);
        type->setFont(font);

        layout->addWidget(topWidget);
        layout->addWidget(type);

        QWidget* dataWidget = new QWidget();
        QGridLayout* dataLayout = new QGridLayout(dataWidget);

        data = new QLabel("Data: " + QString::number(TP.getData()));

        QLabel* initial = new QLabel("Initial: " + QString::number(double(TP.getInitialPressure())) + " bar");
        QLabel* dispersion = new QLabel("Dispersion: " + QString::number(double(TP.getPressureDispersion()))+ " bar");
        QLabel* warning = new QLabel("Warning Level: " + QString::number(double(TP.getWarningPressureLevel()))+ " bar");

        dataLayout->addWidget(data, 0, 0);
        dataLayout->addWidget(initial, 1, 0);
        dataLayout->addWidget(dispersion, 2, 0);
        dataLayout->addWidget(warning, 0, 1);

        layout->addWidget(dataWidget);

        if(chart)
        {
            chart = nullptr;
            delete chart;
        }
        chart = new Chart();

        chart->setChart(new QChart());
        chart->setXAxis(new QValueAxis());
        chart->getXAxis()->setTitleText("Data");
        chart->getXAxis()->setRange(0, 100);
        chart->setYAxis(new QValueAxis());
        chart->getYAxis()->setRange(0, 100);

        chart->getChart()->addAxis(chart->getXAxis(), Qt::AlignBottom);
        chart->getChart()->addAxis(chart->getYAxis(), Qt::AlignLeft);

        chart->setChartView(new QChartView(chart->getChart()));
        chart->getChartView()->setRenderHint(QPainter::Antialiasing);
        chart->getChartView()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        layout->addWidget(chart->getChartView());
        connect(simulate_button, &QPushButton::clicked, this, [this]() { onSimulateClicked(current_sensor); });
        connect(edit_button, &QPushButton::clicked, this, [this]() { onEditClicked(current_sensor);});

        if(editMode)
        {
            editTP = new TirePressureDialog(this);
            editTP->initializeForExistingSensor(&TP);
            connect(editTP, &TirePressureDialog::sensorAdded, this, &ChartInfo::editChartInfo);
            editTP->exec();
        }
    }
    void ChartInfo::visit(Sensor::SpeedSensor& s)
    {
        current_sensor = &s;
        QVBoxLayout* layout = new QVBoxLayout(this);

        QWidget* topWidget = new QWidget();
        QHBoxLayout* topLayout = new QHBoxLayout(topWidget);

        simulate_button = new QPushButton(QIcon(QPixmap((":/Icons/simulate_icon.svg"))), "");
        edit_button = new QPushButton(QIcon(QPixmap((":/Icons/edit_icon.svg"))), "");

        QSize iconSize(40, 40); QSize iconSize1(32, 32);
        simulate_button->setIconSize(iconSize);
        edit_button->setIconSize(iconSize1);
        simulate_button->setToolTip("Simulate");
        edit_button->setToolTip("Edit");

        simulate_button->setAttribute(Qt::WA_Hover, true);
        edit_button->setAttribute(Qt::WA_Hover, true);

        simulate_button->setFixedSize(50, 50);
        edit_button->setFixedSize(50, 50);

        topLayout->addWidget(simulate_button);
        topLayout->addStretch();
        topLayout->addWidget(edit_button);

        QLabel* type = new QLabel("SPEED SENSOR");
        type->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        QFont font = type->font();
        font.setBold(true);
        type->setFont(font);

        layout->addWidget(topWidget);
        layout->addWidget(type);

        QWidget* dataWidget = new QWidget();
        QGridLayout* dataLayout = new QGridLayout(dataWidget);

        data = new QLabel("Data: " + QString::number(s.getData()));
        QLabel* initial_time = new QLabel("Initial Time: " + QString::number(s.getInitialTime()) + " s");
        QLabel* initial_dist = new QLabel("Initial Distance: " + QString::number(s.getInitialDist()) + " m");
        QLabel* dispersion_time = new QLabel("Time Dispersion: " + QString::number(s.getTimeDispersion()) + " s");
        QLabel* dispersion_dist = new QLabel("Distance Dispersion: " + QString::number(s.getDistDispersion()) + " m");

        dataLayout->addWidget(data, 0, 0);
        dataLayout->addWidget(initial_time, 1, 0);
        dataLayout->addWidget(initial_dist, 2, 0);
        dataLayout->addWidget(dispersion_time, 0, 1);
        dataLayout->addWidget(dispersion_dist, 1, 1);

        layout->addWidget(dataWidget);

        if(chart)
        {
            chart = nullptr;
            delete chart;
        }
        chart = new Chart();

        chart->setChart(new QChart());
        chart->setXAxis(new QValueAxis());
        chart->getXAxis()->setTitleText("Data");
        chart->getXAxis()->setRange(0, 100);
        chart->setYAxis(new QValueAxis());
        chart->getYAxis()->setRange(0, 100);

        chart->getChart()->addAxis(chart->getXAxis(), Qt::AlignBottom);
        chart->getChart()->addAxis(chart->getYAxis(), Qt::AlignLeft);

        chart->setChartView(new QChartView(chart->getChart()));
        chart->getChartView()->setRenderHint(QPainter::Antialiasing);
        chart->getChartView()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        layout->addWidget(chart->getChartView());
        connect(simulate_button, &QPushButton::clicked, this, [this]() { onSimulateClicked(current_sensor); });
        connect(edit_button, &QPushButton::clicked, this, [this]() { onEditClicked(current_sensor);});

        if(editMode)
        {
            editS = new SpeedDialog(this);
            editS->initializeForExistingSensor(&s);
            connect(editS, &SpeedDialog::sensorAdded, this, &ChartInfo::editChartInfo);
            editS->exec();
        }
    }

    QLabel* ChartInfo::getData() const
    {
        return data;
    }
    QPushButton* ChartInfo::getSimulateButton() const
    {
        return simulate_button;
    }
    QPushButton* ChartInfo::getEditButton() const
    {
        return edit_button;
    }
    Chart* ChartInfo::getChart() const
    {
        return chart;
    }  

    void ChartInfo::onEditClicked(Sensor::CarSensor* sensor)
    {
        if (sensor)
        {
            editMode = true;
            sensor->accept(*this);
            editMode = false;
        }
    }
    void ChartInfo::editChartInfo(Sensor::CarSensor* s)
    {
        emit editSignalCI(s);
    }
}