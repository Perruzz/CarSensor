#ifndef TOOL_BAR_H
#define TOOL_BAR_H

#include <QToolBar>
#include <QFileDialog>
#include <QToolButton>
#include <memory>

#include "CabinTemperatureDialog.h"
#include "SpeedDialog.h"
#include "TirePressureDialog.h"
#include "../Sensor/Json/jsonrepository.h"

namespace View
{
    class ToolBar : public QToolBar
    {
    Q_OBJECT

    private:
        QAction* CTSensor;
        QAction* SSensor;
        QAction* TPSensor;
        QAction* open;
        QAction* save_as;

        CabinTemperatureDialog* CT;
        TirePressureDialog* TP;
        SpeedDialog* S;

    public:
        ToolBar(QToolBar *p = nullptr);
        ~ToolBar() = default;

        void disableSaveButton();
        void enableSaveButton();

    public slots:
        void openSlot();
        void saveAsSlot();
        void openCTWindow();
        void openSWindow();
        void openTPWindow();

        void checkIfSensorIDAreEqual(Sensor::CarSensor* s);

    signals:
        void openSignal();
        void saveAsSignal();

        void checkIfSensorCanBeAddedTB(Sensor::CarSensor* s);
    };
}
#endif
