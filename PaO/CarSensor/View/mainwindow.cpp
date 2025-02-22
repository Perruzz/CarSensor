#include "mainwindow.h"

namespace View
{
    MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), repo(nullptr)
    {
        toolbar = new ToolBar();
        toolbar->setOrientation(Qt::Horizontal);
        addToolBar(Qt::BottomToolBarArea, toolbar);
        toolbar->setMovable(false);

        connect(toolbar, &ToolBar::openSignal, this, &MainWindow::open);
        connect(toolbar, &ToolBar::saveAsSignal, this, &MainWindow::save_as);
        connect(toolbar, &ToolBar::checkIfSensorCanBeAddedTB, this, &MainWindow::checkIfSensorCanBeAddedMW);

        centralWidget = new QWidget(this);
        mainLayout = new QHBoxLayout(centralWidget);

        panel = new SensorsPanel();
        mainLayout->addWidget(panel);

        QFrame* line = new QFrame();
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setStyleSheet("color: black;");
        mainLayout->addWidget(line);

        placeholder = new QWidget();
        placeholder->setMinimumWidth(600);
        placeholder->setMinimumHeight(500);
        mainLayout->addWidget(placeholder, 2);
        mainLayout->addStretch();

        setCentralWidget(centralWidget);

        connect(panel, &SensorsPanel::sensorDeleted, this, &MainWindow::deleteSensorMW);
        connect(panel, &SensorsPanel::showChartInfoSignal, this, &MainWindow::displaySensorInfo);

        chart_info = nullptr;
    }
    void MainWindow::closeEvent(QCloseEvent* event)
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Exit Confirmation",
            tr("Are you sure to quit CarSensor?\n"),
            QMessageBox::No | QMessageBox::Yes,
            QMessageBox::Yes);

        if (resBtn != QMessageBox::Yes)
        {
            event->ignore();
        }
        else
        {
            event->accept();
        }
    }

    void MainWindow::open()
    {
        QString defaultFolder = "../";
        QFileDialog dialog(this);
        dialog.setDirectory(defaultFolder);
        QString fileName = dialog.getOpenFileName(this, "Open Json File", defaultFolder, "JSON Files (*.json);;All Files (*)");

        if (!fileName.isEmpty())
        {
            repo = nullptr;
            delete repo;
            if(!sensors.empty())
            {
                for (auto sensor : sensors)
                {
                    delete sensor;
                }
                sensors.clear();
            }
            repo = new Sensor::Json::JsonRepository(Sensor::Json::JsonRepository::fromPath(fileName.toStdString()));
            repo->load();

            sensors = repo->readAll();
            panel->showList(sensors);
        }
        toolbar->disableSaveButton();
        repo = nullptr;
        delete repo;
        if(chart_info)
        {
            mainLayout->removeWidget(chart_info);
            chart_info->hide();
        }
    }
    void MainWindow::save_as()
    {
        QString defaultFolder = "../";
        QFileDialog dialog(this);
        dialog.setDirectory(defaultFolder);

        QString fileName = dialog.getSaveFileName(this, "Save Json as", defaultFolder, "JSON Files (*.json)");

        if (!fileName.isEmpty())
        {
            if (!fileName.endsWith(".json", Qt::CaseSensitive))
            {
                fileName += ".json";
            }

            if(repo==nullptr)
                repo = new Sensor::Json::JsonRepository(Sensor::Json::JsonRepository::fromPath(fileName.toStdString()));
            else
                repo->setPath(fileName.toStdString());

            repo->overwrite(sensors);
            repo->store();

            toolbar->disableSaveButton();
        }
    }

    void MainWindow::checkIfSensorCanBeAddedMW(Sensor::CarSensor* s)
    {
        for(auto* it : sensors)
        {
            if(it->getIdentifier() == s->getIdentifier())
            {
                QMessageBox::critical(this, "Error", "ID already used", QMessageBox::Ok);
                delete s;
                return;
            }
        }
        sensors.push_back(s);
        toolbar->enableSaveButton();
        panel->addSensor(s);
    }
    void MainWindow::deleteSensorMW(unsigned int sensorId)
    {
        auto it = std::remove_if(sensors.begin(), sensors.end(), [sensorId](Sensor::CarSensor* sensor)
        {
            if (sensor->getIdentifier() == sensorId)
            {
                delete sensor;
                return true;
            }
            return false;
        } );
        sensors.erase(it, sensors.end());
        if(chart_info)
        {
            mainLayout->removeWidget(chart_info);
            chart_info->hide();
        }
        if(sensors.empty()) toolbar->disableSaveButton();
        else toolbar->enableSaveButton();
    }
    void MainWindow::displaySensorInfo(Sensor::CarSensor* sensor)
    {
        if(placeholder)
        {
            mainLayout->removeWidget(placeholder);
            delete placeholder;
            placeholder = nullptr;
        }
        if(chart_info)
        {
            mainLayout->removeWidget(chart_info);
            chart_info->hide();
        }
        chart_info = new ChartInfo;
        chart_info->setMinimumWidth(600);
        chart_info->setMinimumHeight(500);
        mainLayout->addWidget(chart_info, 2);
        mainLayout->addStretch();
        chart_info->hide();

        if (auto* cabinSensor = dynamic_cast<Sensor::CabinTemperatureSensor*>(sensor))
        {
            chart_info->visit(*cabinSensor);
        }
        else if (auto* tireSensor = dynamic_cast<Sensor::TirePressureSensor*>(sensor))
        {
            chart_info->visit(*tireSensor);
        }
        else if (auto* speedSensor = dynamic_cast<Sensor::SpeedSensor*>(sensor))
        {
            chart_info->visit(*speedSensor);
        }

        chart_info->show();

        connect(chart_info, &ChartInfo::editSignalCI, this, &MainWindow::editSensorMW);
    }
    void MainWindow::editSensorMW(Sensor::CarSensor* s)
    {
        if(chart_info)
        {
            mainLayout->removeWidget(chart_info);
            chart_info->hide();
        }
        for (Sensor::CarSensor*& it : sensors)
        {
            if (it->getIdentifier() == s->getIdentifier())
            {
                delete it;
                it = s;
                panel->showList(sensors);
                toolbar->enableSaveButton();
                return;
            }
        }
    }
} 

