#ifndef CHARTS_H
#define CHARTS_H

#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QLineSeries>

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class QTabWidget;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE


class ChartsMaker : public QWidget
{
    Q_OBJECT

public:
    ChartsMaker();

    QChart *createChart(QString Title,int XSeries,int YSeries);
    void updateCSV(QString location);

private slots:
    DataTable generateRandomData(int listCount, int valueMax, int valueCount)const;


private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    DataTable m_dataTable;
    QList<QList<float>> data;
    QLineSeries *CreateSeries(int Xindex, int Yindex);
    float getMax(int index);
    float getMin(int index);
};

#endif // CHARTS_H
