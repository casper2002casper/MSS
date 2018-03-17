#include "mainwindow.h"
#include "charts.h"
#include "basestationserver.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QtCharts>
#include <QtWidgets>
#include <QtCore>

#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lastCommandSendList->hide();
    ui->lastDataRecievedList->hide();

    ChartsMaker ch;
    QChartView *chartView = new QChartView(ch.createRHChart());

    ui->tempChartLayout->addWidget(chartView);

    ui->statusbar->addPermanentWidget(ui->projectScout_2);
}

MainWindow::~MainWindow()
{    delete ui;}

void MainWindow::on_actionShow_last_command_send_triggered(bool checked)
{    checked ? ui->lastCommandSendList->show() : ui->lastCommandSendList->hide();}

void MainWindow::on_actionLast_data_recieved_triggered(bool checked)
{    checked ? ui->lastDataRecievedList->show() : ui->lastDataRecievedList->hide();}

void MainWindow::on_startButton_clicked()
{

}

void MainWindow::on_stopButton_clicked()
{

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


void MainWindow::on_pushButton_clicked()
{
    basestationServer bs;
    bs.makeConnection();
}
