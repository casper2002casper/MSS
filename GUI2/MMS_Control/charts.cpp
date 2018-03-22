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

void ChartsMaker::updateCSV(QString location)
{
    //location = "/home/casper/BaseStationMeasurementData.csv";
    //QList<QString> labels({"PosX", "PosY","PosZ","SpeedX","SpeedY","SpeedZ","Temperature","Humidity","Lux","Par","CO2"});
    //qDebug("Opening " + location.toLatin1());
    data.clear();
    QFile file(location);
    if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.errorString();
    }
    while (!file.atEnd()) {
       QByteArray line = file.readLine();
       QList<QByteArray> splitline = line.split(',');
       QList<float> row;
       for (int i = 2; i < splitline.size(); ++i) {
           row.append(QString(splitline[i]).toFloat());
           //qDebug(labels[i].toLatin1() + "%f",QString(splitline[i]).toFloat());
       }
       data.append(row);
    }
//    qDebug("updatedone ");
//    for (int i = 0; i < data[5].size(); ++i) {
//         qDebug("%f",data[5][i]);
//    }

}

QLineSeries *ChartsMaker::CreateSeries(int Xindex, int Yindex){
    //qDebug("create ");
    //qDebug("%f",data[0][7]);
    QLineSeries *series = new QLineSeries();
    QList<QPointF> list;
    for (int i = 0; i < data.size(); i++) {
        list.append(QPointF(data[i][Xindex], data[i][Yindex]));
    }
    series->append(list);
    //qDebug("createdone ");
    return series;
}

float ChartsMaker::getMin(int index){
    float min = std::numeric_limits<float>::max();
    for (int i = 0; i < data.size(); i++) {
        if(data[i][index] < min) min = data[i][index];
    }
    //qDebug("min %f",min);
    return min;
}

float ChartsMaker::getMax(int index){
    float max = std::numeric_limits<float>::min();
    for (int i = 0; i < data.size(); i++) {
        if(data[i][index] > max) max = data[i][index];
    }
    //qDebug("max %f",max);
    return max;
}



QChart *ChartsMaker::createChart(QString Title,int XSeries,int YSeries)
{
    QChart *chart = new QChart();
    chart->setTitle(Title);

    chart->addSeries(CreateSeries(XSeries,YSeries));
    chart->createDefaultAxes();

    chart->axisX()->setRange(getMin(XSeries),getMax(XSeries));
    chart->axisY()->setRange(getMin(YSeries) * 0.99,getMax(YSeries) * 1.01);

    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    // Add space to label to add space between labels and axis
    static_cast<QValueAxis *>(chart->axisY())->setLabelFormat("%.1f  ");

    return chart;
}
