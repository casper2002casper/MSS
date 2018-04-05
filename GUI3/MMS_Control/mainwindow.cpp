#include "mainwindow.h"
#include "basestationserver.h"

#include "ui_mainwindow.h"

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
    D_start(new Ui::StartDialog),
    D_auto(new Ui::AutomaticMode)
{
    setWindowIcon(QIcon(":/icons/tomato.png"));
    setWindowIconText("MMS Control");

    ui->setupUi(this);
    D_drive->setupUi(driveUi);
    D_measure->setupUi(measureUi);
    D_pause->setupUi(pauseUi);
    D_start->setupUi(startUi);
    D_auto->setupUi(autoUi);

    connect(&bs, SIGNAL(newMessage(QString)),this, SLOT(inputData(QString)));
    connect(&bs, SIGNAL(connected()),this, SLOT(connected()));
    connect(&bs, SIGNAL(disconnecting()),this, SLOT(disconnected()));

    connect(driveUi, &QDialog::accepted, this, &MainWindow::driveCommand);
    connect(measureUi, &QDialog::accepted, this, &MainWindow::measureCommand);
    connect(pauseUi, &QDialog::accepted, this, &MainWindow::pauseCommand);
    connect(startUi, &QDialog::accepted, this, &MainWindow::startCommand);
    connect(D_auto->buttonBox, SIGNAL(accepted()), this, SLOT(autoCommandSave()));
    connect(ui->actionAdvanced, SIGNAL(changed()), this, SLOT(sendInstant()));

    ui->lastCommandSendList->hide();
    ui->lastDataRecievedList->hide();
    ui->sendInstant->hide();
    ui->statusbar->addPermanentWidget(ui->projectScout_2);


    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->pauseButton->setEnabled(false);
    ui->resumeButton->setEnabled(false);
    ui->driveButton->setEnabled(false);
    ui->measureButton->setEnabled(false);
    ui->connectButton->setEnabled(false);
    ui->actionCreate_command_sequence->setEnabled(false);
    ui->sendInstant->setEnabled(false);

    testPlot();
}

MainWindow::~MainWindow()
{    delete ui;}



void MainWindow::on_actionShow_last_command_send_triggered(bool checked)
{    checked ? ui->lastCommandSendList->show() : ui->lastCommandSendList->hide();}

void MainWindow::on_actionLast_data_recieved_triggered(bool checked)
{    checked ? ui->lastDataRecievedList->show() : ui->lastDataRecievedList->hide();}

void MainWindow::on_startButton_clicked()
{
    (ui->actionAdvanced->isChecked()) ? startUi->show(): sendCommand("2::000::0::1::0;");
}

void MainWindow::on_stopButton_clicked()
{
    sendCommand("2::000::0::2");
}

void MainWindow::on_pauseButton_clicked()
{
    (ui->actionAdvanced->isChecked()) ? pauseUi->show(): sendCommand("2::000::0::3::0;");
}

void MainWindow::on_resumeButton_clicked()
{
    sendCommand("2::000::0::4");
}

void MainWindow::on_driveButton_clicked()
{
    (ui->actionAdvanced->isChecked()) ? driveUi->show(): sendCommand("2::000::0::0::1;1;0.5;0.5;0.25;0.25;0.1;");
}

void MainWindow::on_measureButton_clicked()
{
    (ui->actionAdvanced->isChecked()) ? measureUi->show(): sendCommand("2::000::0::5::2;0;0;");
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setDocName("naam?");

    QPrintPreviewDialog dialog2 (&printer,this);
    QPrintDialog dialog (&printer,this);
    if(dialog.exec() == QDialog::Rejected) return;
}

void MainWindow::sendCommand(QString command, bool blocking){

    commandPending = true;
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(command);
    ui->lastCommandSendList->addItem(newItem);
    ui->lastCommandSendList->scrollToBottom();
    bs.makeCommand(command);
    if(blocking){
        while(commandPending){
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }
}

void MainWindow::inputData(QString message){
    //qDebug("link: " + message.toLatin1());
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(message);
    ui->lastDataRecievedList->addItem(newItem);
    ui->lastDataRecievedList->scrollToBottom();
    if(message[0] == '0') updateCharts();
    if(message[0] == '1') commandPending = false;
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
        bs.disconnected();
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
    ui->connectButton->setEnabled(true);
}

void MainWindow::on_actionNew_file_triggered()
{
    QString homePath = QDir::homePath();
    filepath=QFileDialog::getSaveFileName(this, tr("Save File"),
                                homePath,
                                "CSV (*.csv*)");
    if(!filepath.isNull()){
            if(!filepath.endsWith(".csv"))filepath.append(".csv");
            bs.setDirectory(filepath);
            updateCharts();
            ui->connectButton->setEnabled(true);
    }
}

void MainWindow::disconnected()
{
    ui->connectButton->setText("Connect");
    bs.close();
    //qDebug("closing");

    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->pauseButton->setEnabled(false);
    ui->resumeButton->setEnabled(false);
    ui->driveButton->setEnabled(false);
    ui->measureButton->setEnabled(false);
    ui->actionCreate_command_sequence->setEnabled(false);
    ui->sendInstant->setEnabled(false);
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
    ui->actionCreate_command_sequence->setEnabled(true);
    ui->sendInstant->setEnabled(true);
}

void MainWindow::updateCharts(){
    ch.updateCSV(filepath);
    //ui->tempChartLayout->addWidget(QChartView *TchartView);

    QLayoutItem *child= ui->tempChartLayout->takeAt(0);
    if(child) delete(child->widget());
    QChartView *TchartView = new QChartView(ch.createChart("Temperature",Time,Temperature1));
    ui->tempChartLayout->addWidget(TchartView);

    child= ui->rhTabLayout->takeAt(0);
    if(child) delete(child->widget());
    QChartView *RHchartView = new QChartView(ch.createChart("Relative Humidity",Time,Humidity1));
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
    QString command = "2::000::0::0::";
    command.append(QString::number(D_drive->doMeasurement->isChecked()));
    command.append(";");
    command.append(QString::number(D_drive->distance->value()));
    command.append(";");
    command.append(QString::number(D_drive->driveSpeed->value()));
    command.append(";");
    command.append(QString::number(D_drive->measurementSpeed->value()));
    command.append(";");
    command.append(QString::number(D_drive->measurementTime->value()));
    command.append(";");
    command.append(QString::number( D_drive->acceleration->value()));
    command.append(";");
    command.append(QString::number(D_drive->deacceleration->value()));
    command.append(";");
    command.append(QString::number(D_drive->marge->value()));
    command.append(";");
    //qDebug(command.toLatin1());
    sendCommand(command);//bs.makeCommand("2::010::0::5::2.1;5;3;4;2.5;2;2;2;");
}
void MainWindow::measureCommand(){
    QString command = "2::000::0::5::";
    command.append(QString::number(D_measure->Maxmeasure->value()));
    command.append(";");
    command.append(QString::number(D_measure->Minmeasure->value()));
    command.append(";");
    command.append(QString::number(D_measure->continues->isChecked()));
    command.append(";");
    sendCommand(command); //bs.makeCommand("2::010::0::5::2.1;5;3;4;2.5;2;2;2;");
}
void MainWindow::pauseCommand(){
    QString command = "2::000::0::3::";
    command.append(QString::number(D_pause->autoResume->value()));
    command.append(";");
    sendCommand(command);//bs.makeCommand("2::010::0::5::2.1;5;3;4;2.5;2;2;2;");
}
void MainWindow::startCommand(){
    QString command = "2::000::0::1::";
    command.append(QString::number(D_start->warmupTime->value()));
    command.append(";");
    sendCommand(command);//bs.makeCommand("2::010::0::5::2.1;5;3;4;2.5;2;2;2;");
}


void MainWindow::on_actionCreate_command_sequence_triggered()
{
    autoUi->show();
    qDebug("show");
}


void MainWindow::autoCommandSave()
{

    D_auto->sendingProgress->setMaximum(qCeil(D_auto->distance->value() / D_auto->measurementInterval->value()));
    float distance = 0;
    int progress = 0;
    D_auto->sendingProgress->setValue(progress);
    while(distance<D_auto->distance->value()){
        QString command = "2::000::1::0::";
        command.append(QString::number(D_auto->doMeasurement->isChecked()));
        command.append(";");
        if(D_auto->measurementInterval->value()<(D_auto->distance->value() - distance)) command.append(QString::number(D_auto->measurementInterval->value()));
        else command.append(QString::number(D_auto->distance->value() - distance));
        command.append(";");
        command.append(QString::number(D_auto->drivingSpeed->value()));
        command.append(";");
        command.append(QString::number(D_auto->measurementSpeed->value()));
        command.append(";");
        command.append(QString::number(D_auto->measurementTime->value()));
        command.append(";");
        command.append(QString::number( D_auto->acceleration->value()));
        command.append(";");
        command.append(QString::number(D_auto->deacceleration->value()));
        command.append(";");
        command.append(QString::number(D_auto->Marge->value()));
        command.append(";");
        qDebug("Sending " + command.toLatin1());
        sendCommand(command,true);//bs.makeCommand("2::010::0::5::2.1;5;3;4;2.5;2;2;2;");
        progress++;
        D_auto->sendingProgress->setValue(progress);
        distance += D_auto->measurementInterval->value();
    }

}

void MainWindow::sendInstant()
{ (ui->actionAdvanced->isChecked()) ? ui->sendInstant->show(): ui->sendInstant->hide();}

void MainWindow::testPlot()
{
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->plotTest->addGraph();
    ui->plotTest->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->plotTest->xAxis->setLabel("x");
    ui->plotTest->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->plotTest->xAxis->setRange(-1, 1);
    ui->plotTest->yAxis->setRange(0, 1);
    ui->plotTest->replot();
}
