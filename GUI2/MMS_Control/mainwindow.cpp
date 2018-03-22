#include "mainwindow.h"

#include "basestationserver.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QtCharts>
#include <QtWidgets>
#include <QtCore>
#include <QtNetwork>

#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
    connect(&bs, SIGNAL(newMessage()),this, SLOT(inputData()));
    ui->setupUi(this);
 //   ui->lastCommandSendList->hide();
    ui->lastDataRecievedList->hide();
    ui->connectButton->setEnabled(true);


    //QString homePath = QDir::homePath();
    //ch.updateCSV(homePath + "/BaseStationMeasurementData.csv");



    ui->statusbar->addPermanentWidget(ui->projectScout_2);

    quint16 port = 8080;
    const QHostAddress &ip = QHostAddress("192.168.1.9");
    if (!bs.listen(ip,port)) {
        QMessageBox::critical(this, tr("Threaded Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(bs.errorString()));
        close();
        return;
    }
    qDebug("Port: %d\n",(quint16) port);
    qDebug("IP: " + ip.toString().toLatin1());
}

MainWindow::~MainWindow()
{    delete ui;}

void MainWindow::enableConnectButton(bool on)
{
    ui->connectButton->setEnabled(on);

}

void MainWindow::on_actionShow_last_command_send_triggered(bool checked)
{    checked ? ui->lastCommandSendList->show() : ui->lastCommandSendList->hide();}

void MainWindow::on_actionLast_data_recieved_triggered(bool checked)
{    checked ? ui->lastDataRecievedList->show() : ui->lastDataRecievedList->hide();}

void MainWindow::on_startButton_clicked()
{
    bs.sendCommand();
}

void MainWindow::on_stopButton_clicked()
{
    QString homePath = QDir::homePath();
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                homePath,
                "CSV (*.csv*)");

    ch.updateCSV(filename);
    QChartView *TchartView = new QChartView(ch.createChart("Temperature",PosX,Temperature));
    ui->tempChartLayout->addWidget(TchartView);
    QChartView *RHchartView = new QChartView(ch.createChart("Relative Humidity",PosX,Humidity));
    ui->rhTabLayout->addWidget(RHchartView);
    QChartView *LchartView = new QChartView(ch.createChart("Lux",PosX,Lux));
    ui->luxTabLayout->addWidget(LchartView);
    QChartView *PARchartView = new QChartView(ch.createChart("PAR",PosX,Par));
    ui->parTabLayout->addWidget(PARchartView);
    QChartView *COOchartView = new QChartView(ch.createChart("CO2",PosX,CO2));
    ui->co2TabLayout->addWidget(COOchartView);
}

void MainWindow::on_pauseButton_clicked()
{

}

void MainWindow::on_resumeButton_clicked()
{

}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setDocName("naam?");

    QPrintPreviewDialog dialog2 (&printer,this);
    QPrintDialog dialog (&printer,this);
    if(dialog.exec() == QDialog::Rejected) return;
}


void MainWindow::inputData(QString message){
    qDebug("link: %s", message.toStdString());
    QString text = bs.lastmessage;
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(text);
    ui->lastCommandSendList->addItem(newItem);
}

void MainWindow::on_connectButton_clicked()
{
   // basestationServer bs;
    //bs.startUp();
    //inputData("aan");
}
