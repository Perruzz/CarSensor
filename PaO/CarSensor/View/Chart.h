#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <vector>
#include <QLineSeries>
#include <QBarSet>
#include <QStackedBarSeries>
#include <QLegendMarker>
#include <QScatterSeries>
#include <QSplineSeries>
#include <QAreaSeries>

#include "../Sensor/SensorVisitor.h"
#include "../Sensor/CabinTemperatureSensor.h"
#include "../Sensor/TirePressureSensor.h"
#include "../Sensor/SpeedSensor.h"

namespace View
{
    class Chart : public Sensor::SensorVisitor
    {
    private:
        QChart* chart;
        QValueAxis *axisX;
        QValueAxis *axisY;
        QChartView* view_chart;

        QLineSeries* createLineSeries(double value, size_t maxIndex, const QString& name, const QColor& color);
        void attachAxes(QAbstractSeries* series);
        void updateAxisRange();
        void setSeriesNames(QScatterSeries* series_aSpeed);
        void styleSeries(QLineSeries* series, Qt::PenStyle style, const QColor& color);

    public:
        Chart();

        void visit(Sensor::SpeedSensor& s) override;
        void visit(Sensor::TirePressureSensor& TP) override;
        void visit(Sensor::CabinTemperatureSensor& CT) override;

        void update(Sensor::CarSensor* s);

        virtual QChart* getChart() const;
        QValueAxis* getXAxis() const;
        QValueAxis* getYAxis() const;
        virtual QChartView* getChartView() const;

        Chart& setChart(QChart* chart);
        Chart& setXAxis(QValueAxis* x);
        Chart& setYAxis(QValueAxis* y);
        Chart& setChartView(QChartView* view_chart);
    };
}
#endif
