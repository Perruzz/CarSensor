#include "SensorsPanel.h"

namespace View
{
    SensorsPanel::SensorsPanel(QWidget* parent) : QWidget(parent)
    {
        setFixedWidth(250);

        QVBoxLayout* vbox = new QVBoxLayout(this);
        vbox->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        QHBoxLayout* search_layout = new QHBoxLayout();
        query = new QLineEdit();
        query->setPlaceholderText("Search...");
        search_button = new QPushButton(QIcon(":/Icons/search_icon.svg"), "");
        search_button->setFixedSize(24, 24);
        search_layout->addWidget(query);
        search_layout->addWidget(search_button);
        vbox->addLayout(search_layout);

        sort_button_name = new QPushButton("Sort Name");
        vbox->addWidget(sort_button_name);

        layout = new QGridLayout();
        layout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        QWidget* container = new QWidget();
        container->setLayout(layout);
        QScrollArea* scroll_area = new QScrollArea();
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scroll_area->setWidgetResizable(true);
        scroll_area->setWidget(container);
        scroll_area->setFrameShape(QFrame::NoFrame);
        vbox->addWidget(scroll_area);

        connect(search_button, &QPushButton::clicked, this, &SensorsPanel::search);
        connect(sort_button_name, &QPushButton::clicked, this, &SensorsPanel::sortName);
    }
    SensorsPanel::~SensorsPanel()
    {
        clean();
    }

    void SensorsPanel::addSensor(Sensor::CarSensor* sensor)
    {
        SensorWidget* sensor_widget = new SensorWidget();
        sensor->accept(*sensor_widget);

        layout->addWidget(sensor_widget->getCurrentWidget(), layout->rowCount(), 0);
        lookup.push_back(sensor_widget);

        connect(query, &QLineEdit::textChanged, this, &SensorsPanel::search);
        connect(sensor_widget, &SensorWidget::deleteRequested, this, &SensorsPanel::deleteSensorWidget);
        connect(sensor_widget, &SensorWidget::sensorSelected, this, &SensorsPanel::showChartInfo);
    }
    void SensorsPanel::showList(vector<Sensor::CarSensor*> sensors)
    {
        clean();

        for (auto* sensor : sensors)
        {
            addSensor(sensor);
        }
    }
    void SensorsPanel::clean()
    {
        while (!lookup.isEmpty())
        {
            SensorWidget* info = lookup.takeLast();
            info->getCurrentWidget()->deleteLater();
            delete info;
        }
    }

    void SensorsPanel::search()
    {
        std::string query_text = query->text().toLower().toStdString();
        for (auto* widget : lookup)
        {
            const Sensor::CarSensor* sensor = widget->getCurrentSensor();
            std::string sensor_name = sensor->getSensorName();
            std::string sensor_id = std::to_string(sensor->getIdentifier());

            std::transform(sensor_name.begin(), sensor_name.end(), sensor_name.begin(),
                [](unsigned char c){ return std::tolower(c); });

            bool match = sensor_name.find(query_text) != std::string::npos || sensor_id.find(query_text) != std::string::npos;

            widget->getCurrentWidget()->setVisible(match);
        }
    }
    void SensorsPanel::sortName()
    {
        std::sort(lookup.begin(), lookup.end(), [](SensorWidget* a, SensorWidget* b) {
            return a->getCurrentSensor()->getSensorName() < b->getCurrentSensor()->getSensorName();
        });

        for (int i = 0; i < lookup.size(); ++i)
        {
            layout->removeWidget(lookup[i]->getCurrentWidget());
            layout->addWidget(lookup[i]->getCurrentWidget(), i, 0);
        }
    }
    void SensorsPanel::deleteSensorWidget(unsigned int sensorId)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm Deletion", "Are you sure to delete?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            for (int i = 0; i < lookup.size(); ++i)
            {
                if (lookup[i]->getWidgetID() == sensorId)
                {
                    QWidget* widgetToRemove = lookup[i]->getCurrentWidget();
                    if (widgetToRemove)
                    {
                        layout->removeWidget(widgetToRemove);
                        widgetToRemove->deleteLater();
                    }

                    delete lookup[i];
                    lookup.removeAt(i);

                    emit sensorDeleted(sensorId);
                    return;
                }
            }
        }
    }
    void SensorsPanel::showChartInfo(Sensor::CarSensor* s)
    {
        for (auto* widget : lookup)
        {
            widget->setSelected(false);
        }
        for (auto* widget : lookup)
        {
            if (widget->getCurrentSensor()->getIdentifier() == s->getIdentifier())
            {
                widget->setSelected(true);
                break;
            }
        }
        emit showChartInfoSignal(s);
    }
}