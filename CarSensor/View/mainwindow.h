#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QSplitter>
#include <QLabel>
#include <QWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "ChartInfo.h"
#include "SensorsPanel.h"
#include "ToolBar.h"

namespace View
{
    class MainWindow : public QMainWindow
    {
    Q_OBJECT
    private:     
        Sensor::Json::JsonRepository* repo;
        std::vector<Sensor::CarSensor*> sensors;

        ToolBar* toolbar;
        SensorsPanel* panel;
        ChartInfo* chart_info;

        QWidget* placeholder;
        QWidget* centralWidget;
        QHBoxLayout* mainLayout;

    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow() = default;

        void closeEvent(QCloseEvent* event);

    public slots:
        void open();
        void save_as();

        void checkIfSensorCanBeAddedMW(Sensor::CarSensor* s);
        void deleteSensorMW(unsigned int sensorId);
        void displaySensorInfo(Sensor::CarSensor* sensor);
        void editSensorMW(Sensor::CarSensor* s);        
    };
}
#endif
