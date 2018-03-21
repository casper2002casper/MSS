//#include "mainwindow.h"
#include "charts.h"

#include <QDialog>
#include <QtCharts>
#include <QtWidgets>
#include <QtCore>


ChartsMaker::ChartsMaker():
    m_listCount(1),
    m_valueMax(30),
    m_valueCount(24),
    m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount))

{

}


DataTable ChartsMaker::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + QRandomGenerator::global()->bounded(valueMax / (qreal) valueCount);
            QPointF value((j + QRandomGenerator::global()->generateDouble()) * ((qreal) m_valueMax / (qreal) valueCount),
                          yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

DataTable ChartsMaker::updateCSV(QString location) const
{
//    DataTable dataTable;
//    QFile file(location);
//    if (!file.open(QIODevice::ReadOnly)) {
//            qDebug() << file.errorString();
//            return 1;
//    }
//    while (!file.atEnd()) {
//       QByteArray line = file.readLine();
//       QByteArray splitline = line.split(';');

//   }

}

QChart *ChartsMaker::createRHChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("RH chart");

    // The lower series initialized to zero values
    QLineSeries *lowerSeries = 0;
    QString name("Series ");
    int nameIndex = 0;
    for (int i(0); i < m_dataTable.count(); i++) {
        QLineSeries *upperSeries = new QLineSeries(chart);
        for (int j(0); j < m_dataTable[i].count(); j++) {
            Data data = m_dataTable[i].at(j);
            if (lowerSeries) {
                const QVector<QPointF>& points = lowerSeries->pointsVector();
                upperSeries->append(QPointF(j, points[i].y() + data.first.y()));
            } else {
                upperSeries->append(QPointF(j, data.first.y()));
            }
        }
        QAreaSeries *area = new QAreaSeries(upperSeries, lowerSeries);
        area->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(area);
        lowerSeries = upperSeries;
    }

    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 24 - 1);
    chart->axisY()->setRange(0, 30);

    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");

    return chart;
}
