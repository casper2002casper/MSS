// Made by:
// Casper Pennings & Bram Langerak
// For the minor project SCOUT 2018
// Version 1.07 17-04-2018

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QWidget>
#include <QDialog>
#include <QMediaPlayer>

#include "ui_drivedialog.h"
#include "ui_measuredialog.h"
#include "ui_pausedialog.h"
#include "ui_startdialog.h"
#include "ui_automaticmode.h"

#include "basestationserver.h"

#include "charts.h"

namespace Ui {
class MainWindow;
class DriveDialog;
class MeasureDialog;
class PauseDialog;
class StartDialog;
class AutomaticMode;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

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

    void on_actionOpen_file_triggered();
    void on_actionNew_file_triggered();

    void connected();
    void disconnected();
    void driveCommand();
    void measureCommand();
    void pauseCommand();
    void startCommand();
    void on_actionCreate_command_sequence_triggered();

    void autoCommandSave();
    void sendInstant();
    void music();

private:
    Ui::MainWindow *ui;
    Ui::DriveDialog *D_drive;
    Ui::MeasureDialog *D_measure;
    Ui::PauseDialog *D_pause;
    Ui::StartDialog *D_start;
    Ui::AutomaticMode *D_auto;

    QDialog *driveUi = new QDialog(0,0);
    QDialog *measureUi = new QDialog(0,0);
    QDialog *pauseUi = new QDialog(0,0);
    QDialog *startUi = new QDialog(0,0);
    QDialog *autoUi = new QDialog(0,0);

    ChartsMaker ch;
    basestationServer bs;

    void updateCharts();
    void sendCommand(QString command, bool blocking = false);

    enum Parametertype {Time, PosX, PosY, PosZ, SpeedX, SpeedY, SpeedZ, Temperature1,Temperature2,Temperature3,Temperature4, Humidity1,Humidity2,Humidity3,Humidity4, Lux, Par, CO2};
    enum commandType {Instant,Queue};
    enum commanddataType {Action, Start, Stop, Pause, Resume, Measure};
    QString filepath;
    bool commandPending;
    int togglemusic = 0;

    QMediaPlayer *player = new QMediaPlayer;
};


#endif // MAINWINDOW_H
