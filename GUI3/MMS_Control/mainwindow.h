#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QWidget>
#include <QDialog>
#include "ui_drivedialog.h"
#include "ui_measuredialog.h"
#include "ui_pausedialog.h"
#include "ui_startdialog.h"

#include "basestationserver.h"
//#include "basestationthread.h"
#include "charts.h"

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
class DriveDialog;
class MeasureDialog;
class PauseDialog;
class StartDialog;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    void enableConnectButton(bool on);

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void inputData(QString message);
    void on_actionShow_last_command_send_triggered(bool checked);
    void on_actionLast_data_recieved_triggered(bool checked);

    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_pauseButton_clicked();
    void on_resumeButton_clicked();
    void on_driveButton_clicked();
    void on_measureButton_clicked();

    void on_connectButton_clicked();

    void on_actionPrint_triggered();
    void on_actionOpen_file_triggered();
    void on_actionNew_file_triggered();

    void connected();
    void disconnected();
    void pauseCommand();

private:
    Ui::MainWindow *ui;
    Ui::DriveDialog *D_drive;
    Ui::MeasureDialog *D_measure;
    Ui::PauseDialog *D_pause;
    Ui::StartDialog *D_start;

    QDialog *driveUi = new QDialog(0,0);
    QDialog *measureUi = new QDialog(0,0);
    QDialog *pauseUi = new QDialog(0,0);
    QDialog *startUi = new QDialog(0,0);

    ChartsMaker ch;
    basestationServer bs;

    void updateCharts();

    enum type {Time, PosX, PosY, PosZ, SpeedX, SpeedY, SpeedZ, Temperature, Humidity, Lux, Par, CO2};
    QString filepath;
    int advancedTriggerd = 0;
    double R_distance, R_drivespeed, R_measurespeed, R_measuretime, R_acceleration, R_deacceleration, S_warmuptime, P_autoresume, M_measuretime;

};


#endif // MAINWINDOW_H
