#include "ToolBar.h"

namespace View
{
    ToolBar::ToolBar(QToolBar *p) : QToolBar(p)
    {
        CTSensor = new QAction(QIcon(QPixmap((":/Icons/cabin_temperature_sensor_icon.svg"))), "Add Cabin Temperature Sensor");
        SSensor = new QAction(QIcon(QPixmap((":/Icons/speed_sensor_icon.svg"))), "Add Speed Sensor");
        TPSensor = new QAction(QIcon(QPixmap((":/Icons/tire_pressure_sensor_icon.svg"))), "Add Tire Pressure Sensor");
        open = new QAction(QIcon(QPixmap((":/Icons/open_icon.svg"))), "Open");
        save_as = new QAction(QIcon(QPixmap((":/Icons/save_as_icon.svg"))), "Save as");

        QWidget *spacerLeft = new QWidget(this);
        spacerLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        addWidget(spacerLeft);

        addAction(CTSensor);
        addAction(TPSensor);
        addAction(SSensor);
        addAction(open);
        addAction(save_as);

        QWidget *spacerRight = new QWidget(this);
        spacerRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        addWidget(spacerRight);

        open->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
        save_as->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));

        save_as->setEnabled(false);

        connect(open, &QAction::triggered, this, &ToolBar::openSlot);
        connect(save_as, &QAction::triggered, this, &ToolBar::saveAsSlot);
        connect(CTSensor, &QAction::triggered, this, &ToolBar::openCTWindow);
        connect(SSensor, &QAction::triggered, this, &ToolBar::openSWindow);
        connect(TPSensor, &QAction::triggered, this, &ToolBar::openTPWindow);
    }
    void ToolBar::disableSaveButton()
    {
        save_as->setEnabled(false);
    }
    void ToolBar::enableSaveButton()
    {
        save_as->setEnabled(true);
    }

    void ToolBar::openSlot()
    {
        emit openSignal();
    }
    void ToolBar::saveAsSlot()
    {
        emit saveAsSignal();
    }
    void ToolBar::openCTWindow()
    {
        CT = new CabinTemperatureDialog(this);
        connect(CT, &CabinTemperatureDialog::sensorAdded, this, &ToolBar::checkIfSensorIDAreEqual);
        CT->exec();
    }
    void ToolBar::openSWindow()
    {
        S = new SpeedDialog(this);
        connect(S, &SpeedDialog::sensorAdded, this, &ToolBar::checkIfSensorIDAreEqual);
        S->exec();
    }
    void ToolBar::openTPWindow()
    {
        TP = new TirePressureDialog(this);
        connect(TP, &TirePressureDialog::sensorAdded, this, &ToolBar::checkIfSensorIDAreEqual);
        TP->exec();
    }

    void ToolBar::checkIfSensorIDAreEqual(Sensor::CarSensor* s)
    {
        emit checkIfSensorCanBeAddedTB(s);
    }
}
