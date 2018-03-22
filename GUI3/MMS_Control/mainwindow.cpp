#include "mainwindow.h"
#include "charts.h"
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
    connect(&bs, SIGNAL(newMessage(QString)),this, SLOT(inputData(QString)));
    ui->setupUi(this);
 //   ui->lastCommandSendList->hide();
    ui->lastDataRecievedList->hide();
    ui->connectButton->setEnabled(true);

    ChartsMaker ch;
    QChartView *chartView = new QChartView(ch.createRHChart());

    ui->tempChartLayout->addWidget(chartView);

    ui->statusbar->addPermanentWidget(ui->projectScout_2);

    quint16 port = 8080;
    const QHostAddress &ip = QHostAddress("192.168.1.10");
    if (!bs.listen(ip,port)) {
        QMessageBox::critical(this, tr("Threaded Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(bs.errorString()));
        close();
        return;
    }
    qDebug("Port: %d",(quint16) port);
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
    bs.makeCommand(1);
}

void MainWindow::on_stopButton_clicked()
{
    bs.makeCommand(2);
}

void MainWindow::on_pauseButton_clicked()
{
    bs.makeCommand(3);
}

void MainWindow::on_resumeButton_clicked()
{
    bs.makeCommand(4);
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
   bs.sendPacket();
}
