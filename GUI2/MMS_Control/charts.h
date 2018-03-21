#ifndef CHARTS_H
#define CHARTS_H

#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

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

    QChart *createRHChart() const;
    DataTable updateCSV(QString location) const;

private slots:
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;


private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    DataTable m_dataTable;
};

#endif // CHARTS_H
