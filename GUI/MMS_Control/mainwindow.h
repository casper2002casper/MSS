#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QWidget>

#include <basestationserver.h>
#include <basestationthread.h>

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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void enableConnectButton(bool on);

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void command(int command);

private slots:
    void inputData(QString message);
    void on_actionShow_last_command_send_triggered(bool checked);
    void on_actionLast_data_recieved_triggered(bool checked);

    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_pauseButton_clicked();
    void on_resumeButton_clicked();

    void on_actionPrint_triggered();



    void on_connectButton_clicked();

private:
    Ui::MainWindow *ui;
    basestationServer bs;

};

#endif // MAINWINDOW_H
