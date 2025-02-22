#include "Chart.h"

namespace View
{
    QLineSeries* Chart::createLineSeries(double value, size_t maxIndex, const QString& name, const QColor& color)
    {
        QLineSeries* series = new QLineSeries();
        series->append(0, value);
        series->append(maxIndex, value);
        series->setName(name);
        QPen pen(color);
        pen.setStyle(Qt::DashLine);
        series->setPen(pen);
        return series;
    }
    void Chart::attachAxes(QAbstractSeries* series)
    {
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }
    void Chart::updateAxisRange()
    {
        qreal maxX = 0;
        qreal maxY = 0;
        for (QAbstractSeries* series : chart->series())
        {
            QLineSeries* lineSeries = dynamic_cast<QLineSeries*>(series);
            if (lineSeries != nullptr)
            {
                for (const QPointF& point : lineSeries->points())
                {
                    maxX = std::max(maxX, point.x());
                    maxY = std::max(maxY, point.y());
                }
            }
        }
    }
    void Chart::setSeriesNames(QScatterSeries* series_aSpeed)
    {
        series_aSpeed->setName("Average Speed (km/h)");
    }
    void Chart::styleSeries(QLineSeries* series, Qt::PenStyle style, const QColor& color)
    {
        QPen pen(color);
        pen.setStyle(style);
        pen.setWidth(2);
        series->setPen(pen);
    }

    Chart::Chart()
    {
        chart = new QChart();
        view_chart = new QChartView(chart);
    }

    void Chart::visit(Sensor::SpeedSensor& s)
    {
        const vector<double>& time_data = s.getSpeedDataTime();
        const vector<double>& dist_data = s.getSpeedDataDist();
        const vector<double>& aSpeed_data = s.getSpeedDataAvgS();

        double max = *std::max_element(aSpeed_data.begin(), aSpeed_data.end());

        const double urbanR = Sensor::SpeedSensor::urbanRoads.getASpeed();
        const double ruralR = Sensor::SpeedSensor::ruralRoads.getASpeed();
        const double ringR = Sensor::SpeedSensor::ringRoads.getASpeed();
        const double motorW = Sensor::SpeedSensor::motorways.getASpeed();

        const size_t data_size = time_data.size();
        size_t max_index = std::max(data_size, dist_data.size());

        QLineSeries* series_aSpeed = new QLineSeries();
        series_aSpeed->setName("Average Speed (km/h)");

        for (size_t i = 0; i < data_size; ++i)
        {
            series_aSpeed->append(i, aSpeed_data[i]);
        }

        series_aSpeed->setPointsVisible(true);
        series_aSpeed->setMarkerSize(3.0);

        QLineSeries* urban = createLineSeries(urbanR, max_index, "Urban Roads", QColor(255, 165, 0));
        QLineSeries* rural = createLineSeries(ruralR, max_index, "Rural Roads", QColor(135, 206, 235));
        QLineSeries* ring = createLineSeries(ringR, max_index, "Ring Roads", QColor(0, 0, 255));
        QLineSeries* motor = createLineSeries(motorW, max_index, "Motorways", QColor(0, 255, 0));

        chart->addSeries(urban);
        chart->addSeries(rural);
        chart->addSeries(ring);
        chart->addSeries(motor);
        chart->addSeries(series_aSpeed);

        attachAxes(urban);
        attachAxes(rural);
        attachAxes(ring);
        attachAxes(motor);
        attachAxes(series_aSpeed);

        axisX->setRange(0, s.getData());
        axisY->setRange(0, max + 50);
        axisY->setTitleText("Km / h");

        styleSeries(urban, Qt::DashLine, QColor(255, 165, 0));
        styleSeries(rural, Qt::DashLine, QColor(135, 206, 235));
        styleSeries(ring, Qt::DashLine, QColor(0, 0, 255));
        styleSeries(motor, Qt::DashLine, QColor(0, 255, 0));

        QPen pen(QColor(255, 0, 0));
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(1);
        series_aSpeed->setPen(pen);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);
        chart->setAnimationOptions(QChart::SeriesAnimations);

        updateAxisRange();
    }
    void Chart::visit(Sensor::TirePressureSensor& TP)
    {
        const vector<double>& bar_data = TP.getPressureData();
        const double minPressure = Sensor::TirePressureSensor::min;
        const double maxPressure = Sensor::TirePressureSensor::max;
        const double warningPressureLevel = TP.getWarningPressureLevel();

        double max = *std::max_element(bar_data.begin(), bar_data.end());

        QSplineSeries* series = new QSplineSeries();
        for (unsigned int i = 0; i < bar_data.size(); ++i) series->append(i, bar_data[i]);

        chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
        series->setName("Tire Pressure");

        QPen lowPen(QColor(255, 0, 0));
        QPen normalPen(QColor(0, 255, 0));
        lowPen.setStyle(Qt::DashLine);
        normalPen.setStyle(Qt::DashLine);
        lowPen.setWidth(1);
        normalPen.setWidth(1);

        QLineSeries* lowLegendSeries = new QLineSeries();
        QLineSeries* normalLegendSeries = new QLineSeries();
        lowLegendSeries->setName("Pressure Low");
        normalLegendSeries->setName("Pressure Normal");
        lowLegendSeries->setPen(lowPen);
        normalLegendSeries->setPen(normalPen);
        chart->addSeries(lowLegendSeries);
        chart->addSeries(normalLegendSeries);

        bool isLow = false;

        for (unsigned int i = 0; i < bar_data.size(); ++i)
        {
            if (!isLow && bar_data[i] < warningPressureLevel)
            {
                QLineSeries* lowLine = new QLineSeries();
                lowLine->setPen(lowPen);
                lowLine->append(i, minPressure);
                lowLine->append(i, maxPressure);
                chart->addSeries(lowLine);
                lowLine->attachAxis(axisX);
                lowLine->attachAxis(axisY);
                isLow = true;
            }
            else if (isLow && bar_data[i] >= warningPressureLevel)
            {
                QLineSeries* normalLine = new QLineSeries();
                normalLine->setPen(normalPen);
                normalLine->append(i, minPressure);
                normalLine->append(i, maxPressure);
                chart->addSeries(normalLine);
                normalLine->attachAxis(axisX);
                normalLine->attachAxis(axisY);
                isLow = false;
            }
        }

        axisX->setRange(0, TP.getData());
        axisY->setRange(0, max + 3);
        axisY->setTitleText("Bar");

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);
        chart->setAnimationOptions(QChart::SeriesAnimations);

        int count = 0;
        for (QLegendMarker* marker : chart->legend()->markers())
        {
            marker->setVisible(count < 3);
            count++;
        }

        updateAxisRange();
    }
    void Chart::visit(Sensor::CabinTemperatureSensor& CT)
    {
        const vector<double>& min_data = CT.getMinTemp();
        const vector<double>& avg_data = CT.getAvgTemp();
        const vector<double>& max_data = CT.getMaxTemp();

        double min = *std::min_element(min_data.begin(), min_data.end());
        double max = *std::max_element(max_data.begin(), max_data.end());

        unsigned int dataSize = min_data.size();

        QLineSeries* series_min = new QLineSeries();
        QLineSeries* series_max = new QLineSeries();

        for (unsigned int i = 0; i < dataSize; ++i)
        {
            series_min->append(i, min_data[i]);
            series_max->append(i, max_data[i]);
        }

        QAreaSeries* area_series = new QAreaSeries(series_max, series_min);
        area_series->setName("Temperature Range");

        QPen pen(Qt::NoPen);
        area_series->setPen(pen);
        QBrush brush(QColor(135, 206, 250, 80));
        area_series->setBrush(brush);

        chart->addSeries(area_series);
        area_series->attachAxis(axisX);
        area_series->attachAxis(axisY);

        QLineSeries* series_mean = new QLineSeries();
        for (unsigned int i = 0; i < dataSize; ++i) series_mean->append(i, avg_data[i]);

        chart->addSeries(series_mean);
        series_mean->attachAxis(axisX);
        series_mean->attachAxis(axisY);
        series_mean->setName("Set Temperature");

        axisX->setRange(0, CT.getData());
        axisY->setRange(min - 5, max + 5);
        axisY->setTitleText(CT.getScale() == 'c' ? "Celsius" : "Fahrenheit");

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);
        chart->setAnimationOptions(QChart::SeriesAnimations);

        updateAxisRange();
    }

    void Chart::update(Sensor::CarSensor* sensor)
    {
        chart->removeAllSeries();

        if (auto* speedSensor = dynamic_cast<Sensor::SpeedSensor*>(sensor))
        {
            this->visit(*speedSensor);
        }
        else if (auto* tirePressureSensor = dynamic_cast<Sensor::TirePressureSensor*>(sensor))
        {
            this->visit(*tirePressureSensor);
        }
        else if (auto* cabinTemperatureSensor = dynamic_cast<Sensor::CabinTemperatureSensor*>(sensor))
        {
            this->visit(*cabinTemperatureSensor);
        }
    }

    QChart* Chart::getChart() const
    {
        return chart;
    }

    QValueAxis* Chart::getXAxis() const
    {
        return axisX;
    }

    QValueAxis* Chart::getYAxis() const
    {
        return axisY;
    }

    QChartView* Chart::getChartView() const
    {
        return view_chart;
    }

    Chart& Chart::setChart(QChart* c)
    {
        this->chart = c;
        return *this;
    }
    Chart& Chart::setXAxis(QValueAxis* x)
    {
        this->axisX = x;
        return *this;
    }
    Chart& Chart::setYAxis(QValueAxis* y)
    {
        this->axisY = y;
        return *this;
    }
    Chart& Chart::setChartView(QChartView* vc)
    {
        this->view_chart = vc;
        return *this;
    }
}
