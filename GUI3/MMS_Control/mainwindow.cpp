#include "mainwindow.h"
#include "basestationserver.h"

#include "ui_mainwindow.h"
#include "ui_drivedialog.h"
#include "ui_measuredialog.h"
#include "ui_pausedialog.h"
#include "ui_startdialog.h"
#include "ui_automaticmode.h"

#include <QDialog>
#include <QtCharts>
#include <QtWidgets>
#include <QtCore>
#include <QtNetwork>
#include <QtQuick/QQuickItem>

#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    D_drive(new Ui::DriveDialog),
    D_measure(new Ui::MeasureDialog),
    D_pause(new Ui::PauseDialog),
    D_start(new Ui::StartDialog)
{
    ui->setupUi(this);
    D_drive->setupUi(driveUi);
    D_measure->setupUi(measureUi);
    D_pause->setupUi(pauseUi);
    D_start->setupUi(startUi);

    connect(&bs, SIGNAL(newMessage(QString)),this, SLOT(inputData(QString)));
    connect(&bs, SIGNAL(connected()),this, SLOT(connected()));
    connect(&bs, SIGNAL(disconnecting()),this, SLOT(disconnected()));

    connect(driveUi, &QDialog::accepted, this, &MainWindow::driveCommand);
    connect(measureUi, &QDialog::accepted, this, &MainWindow::measureCommand);
    connect(pauseUi, &QDialog::accepted, this, &MainWindow::pauseCommand);
    connect(startUi, &QDialog::accepted, this, &MainWindow::startCommand);

    ui->lastCommandSendList->hide();
    ui->lastDataRecievedList->hide();
    ui->connectButton->setEnabled(true);
    ui->statusbar->addPermanentWidget(ui->projectScout_2);

    /*
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->pauseButton->setEnabled(false);
    ui->resumeButton->setEnabled(false);
    ui->driveButton->setEnabled(false);
    ui->measureButton->setEnabled(false); */
}

MainWindow::~MainWindow()
{    delete ui;}

void MainWindow::enableConnectButton(bool on)
{ui->connectButton->setEnabled(on);}

void MainWindow::on_actionShow_last_command_send_triggered(bool checked)
{    checked ? ui->lastCommandSendList->show() : ui->lastCommandSendList->hide();}

void MainWindow::on_actionLast_data_recieved_triggered(bool checked)
{    checked ? ui->lastDataRecievedList->show() : ui->lastDataRecievedList->hide();}

void MainWindow::on_startButton_clicked()
{(ui->actionAdvanced->isChecked()) ? startUi->show(): qDebug("test");/*bs.makeCommand("2::010::0::1;0;");*/}

void MainWindow::on_stopButton_clicked()
{ bs.makeCommand("2::010::1::5::2.1;5;3;4;2.5;2;2;2;");}

void MainWindow::on_pauseButton_clicked()
{(ui->actionAdvanced->isChecked()) ? pauseUi->show(): qDebug("test");/*bs.makeCommand("2::010::0::1;0;");*/}

void MainWindow::on_resumeButton_clicked()
{bs.makeCommand("2::010::0::5::2.1;5;3;4;2.5;2;2;2;");}

void MainWindow::on_driveButton_clicked()
{(ui->actionAdvanced->isChecked()) ? driveUi->show(): qDebug("test");/*bs.makeCommand("2::010::0::1;0;");*/}

void MainWindow::on_measureButton_clicked()
{(ui->actionAdvanced->isChecked()) ? measureUi->show(): qDebug("test");/*bs.makeCommand("2::010::0::1;0;");*/}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setDocName("naam?");

    QPrintPreviewDialog dialog2 (&printer,this);
    QPrintDialog dialog (&printer,this);
    if(dialog.exec() == QDialog::Rejected) return;
}


void MainWindow::inputData(QString message){
    //qDebug("link: " + message.toLatin1());
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(message);
    ui->lastCommandSendList->addItem(newItem);
    if(message[0] == '0') updateCharts();
}

void MainWindow::on_connectButton_clicked()
{
    if(filepath.isNull()){
         qDebug("Open file first");
         return;
    }
    if(!bs.isListening()){
        quint16 port = 8080;
        const QHostAddress &ip = QHostAddress("192.168.1.9");
        if (bs.listen(ip,port)) {
            qDebug("Connecting to " + ip.toString().toLatin1() + ":" + QString::number(port).toLatin1());
            qDebug("Waiting for connecting ");
            ui->connectButton->setText("Connecting...");
        }
        else{
            qDebug("Couldn't connect to " + ip.toString().toLatin1() + ":" + QString::number(port).toLatin1());
        }
    }
    else{
        ui->connectButton->setText("Connect");
        bs.close();
        qDebug("closing");
    }

}

void MainWindow::on_actionOpen_file_triggered()
{
    QString homePath = QDir::homePath();
    filepath=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                homePath,
                "CSV (*.csv*)");
    bs.setDirectory(filepath);
    updateCharts();
}

void MainWindow::on_actionNew_file_triggered()
{
    QString homePath = QDir::homePath();
    filepath=QFileDialog::getSaveFileName(this, tr("Save File"),
                                homePath,
                                "CSV (*.csv*)");
    bs.setDirectory(filepath);
    updateCharts();
}

void MainWindow::disconnected()
{
    ui->connectButton->setText("Connect");
    bs.close();
    qDebug("closing");

    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->pauseButton->setEnabled(false);
    ui->resumeButton->setEnabled(false);
    ui->driveButton->setEnabled(false);
    ui->measureButton->setEnabled(false);
}

void MainWindow::connected()
{
    ui->connectButton->setText("Disconnect");
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(true);
    ui->pauseButton->setEnabled(true);
    ui->resumeButton->setEnabled(true);
    ui->driveButton->setEnabled(true);
    ui->measureButton->setEnabled(true);
}

void MainWindow::updateCharts(){
    ch.updateCSV(filepath);
    //ui->tempChartLayout->addWidget(QChartView *TchartView);

    QLayoutItem *child= ui->tempChartLayout->takeAt(0);
    if(child) delete(child->widget());
    QChartView *TchartView = new QChartView(ch.createChart("Temperature",Time,Temperature));
    ui->tempChartLayout->addWidget(TchartView);

    child= ui->rhTabLayout->takeAt(0);
    if(child) delete(child->widget());
    QChartView *RHchartView = new QChartView(ch.createChart("Relative Humidity",Time,Humidity));
    ui->rhTabLayout->addWidget(RHchartView);

    child= ui->luxTabLayout->takeAt(0);
    if(child) delete(child->widget());
    QChartView *LchartView = new QChartView(ch.createChart("Lux",Time,Lux));
    ui->luxTabLayout->addWidget(LchartView);

    child= ui->parTabLayout->takeAt(0);
    if(child) delete(child->widget());
    QChartView *PARchartView = new QChartView(ch.createChart("PAR",Time,Par));
    ui->parTabLayout->addWidget(PARchartView);

    child= ui->co2TabLayout->takeAt(0);
    if(child) delete(child->widget());
    QChartView *COOchartView = new QChartView(ch.createChart("CO2",Time,CO2));
    ui->co2TabLayout->addWidget(COOchartView);
}

void MainWindow::driveCommand(){
    R_distance = D_drive->distance->value();
    R_drivespeed = D_drive->driveSpeed->value();
    R_measurespeed = D_drive->measurementSpeed->value();
    R_measuretime = D_drive->measurementTime->value();
    R_acceleration = D_drive->acceleration->value();
    R_deacceleration = D_drive->deacceleration->value();
    R_domeasurement = D_drive->doMeasurement->isChecked();
    //bs.makeCommand("2::010::0::5::2.1;5;3;4;2.5;2;2;2;");
}
void MainWindow::measureCommand(){
    M_measurementtime = D_measure->measurementTime->value();
    //bs.makeCommand("2::010::0::5::2.1;5;3;4;2.5;2;2;2;");
}
void MainWindow::pauseCommand(){
    P_autoresume = D_pause->autoResume->value();
    //bs.makeCommand("2::010::0::5::2.1;5;3;4;2.5;2;2;2;");
}
void MainWindow::startCommand(){
    S_warmuptime = D_start->warmupTime->value();
    //bs.makeCommand("2::010::0::5::2.1;5;3;4;2.5;2;2;2;");
}

void MainWindow::on_actionCreate_command_sequence_triggered()
{
    qDebug("werkt niet");
    autoUi->show();
}
