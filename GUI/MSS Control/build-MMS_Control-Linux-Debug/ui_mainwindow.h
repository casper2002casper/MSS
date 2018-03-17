/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_file;
    QAction *actionShow_last_command_send;
    QAction *actionLast_data_recieved;
    QAction *actionPrint;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *startButton;
    QPushButton *stopButton;
    QSpacerItem *verticalSpacer;
    QPushButton *pauseButton;
    QPushButton *resumeButton;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QListWidget *lastCommandSendList;
    QListWidget *lastDataRecievedList;
    QTabWidget *chartTabs;
    QWidget *temperatureTab;
    QGridLayout *gridLayout;
    QGridLayout *tempChartLayout;
    QWidget *rhTab;
    QGridLayout *gridLayout_3;
    QGridLayout *rhTabLayout;
    QWidget *co2Tab;
    QGridLayout *gridLayout_4;
    QGridLayout *co2TabLayout;
    QWidget *tab_2;
    QGridLayout *gridLayout_5;
    QGridLayout *parTabLayout;
    QWidget *luxTab;
    QGridLayout *gridLayout_6;
    QGridLayout *luxTabLayout;
    QWidget *projectScout_2;
    QHBoxLayout *projectScout;
    QFrame *line;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuCommands;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(962, 656);
        actionOpen_file = new QAction(MainWindow);
        actionOpen_file->setObjectName(QStringLiteral("actionOpen_file"));
        actionShow_last_command_send = new QAction(MainWindow);
        actionShow_last_command_send->setObjectName(QStringLiteral("actionShow_last_command_send"));
        actionShow_last_command_send->setCheckable(true);
        actionLast_data_recieved = new QAction(MainWindow);
        actionLast_data_recieved->setObjectName(QStringLiteral("actionLast_data_recieved"));
        actionLast_data_recieved->setCheckable(true);
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        verticalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(startButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        sizePolicy.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(stopButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        pauseButton = new QPushButton(centralwidget);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        sizePolicy.setHeightForWidth(pauseButton->sizePolicy().hasHeightForWidth());
        pauseButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pauseButton);

        resumeButton = new QPushButton(centralwidget);
        resumeButton->setObjectName(QStringLiteral("resumeButton"));
        sizePolicy.setHeightForWidth(resumeButton->sizePolicy().hasHeightForWidth());
        resumeButton->setSizePolicy(sizePolicy);
        resumeButton->setFlat(false);

        verticalLayout->addWidget(resumeButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        lastCommandSendList = new QListWidget(centralwidget);
        lastCommandSendList->setObjectName(QStringLiteral("lastCommandSendList"));
        lastCommandSendList->setMaximumSize(QSize(16777215, 100));

        verticalLayout_2->addWidget(lastCommandSendList);

        lastDataRecievedList = new QListWidget(centralwidget);
        lastDataRecievedList->setObjectName(QStringLiteral("lastDataRecievedList"));
        lastDataRecievedList->setMaximumSize(QSize(16777215, 100));
        lastDataRecievedList->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_2->addWidget(lastDataRecievedList);

        chartTabs = new QTabWidget(centralwidget);
        chartTabs->setObjectName(QStringLiteral("chartTabs"));
        chartTabs->setTabShape(QTabWidget::Triangular);
        temperatureTab = new QWidget();
        temperatureTab->setObjectName(QStringLiteral("temperatureTab"));
        temperatureTab->setAutoFillBackground(false);
        gridLayout = new QGridLayout(temperatureTab);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tempChartLayout = new QGridLayout();
        tempChartLayout->setObjectName(QStringLiteral("tempChartLayout"));
        tempChartLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout->addLayout(tempChartLayout, 0, 0, 1, 1);

        chartTabs->addTab(temperatureTab, QString());
        rhTab = new QWidget();
        rhTab->setObjectName(QStringLiteral("rhTab"));
        gridLayout_3 = new QGridLayout(rhTab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        rhTabLayout = new QGridLayout();
        rhTabLayout->setObjectName(QStringLiteral("rhTabLayout"));

        gridLayout_3->addLayout(rhTabLayout, 0, 0, 1, 1);

        chartTabs->addTab(rhTab, QString());
        co2Tab = new QWidget();
        co2Tab->setObjectName(QStringLiteral("co2Tab"));
        gridLayout_4 = new QGridLayout(co2Tab);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        co2TabLayout = new QGridLayout();
        co2TabLayout->setObjectName(QStringLiteral("co2TabLayout"));

        gridLayout_4->addLayout(co2TabLayout, 0, 0, 1, 1);

        chartTabs->addTab(co2Tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_5 = new QGridLayout(tab_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        parTabLayout = new QGridLayout();
        parTabLayout->setObjectName(QStringLiteral("parTabLayout"));

        gridLayout_5->addLayout(parTabLayout, 0, 0, 1, 1);

        chartTabs->addTab(tab_2, QString());
        luxTab = new QWidget();
        luxTab->setObjectName(QStringLiteral("luxTab"));
        gridLayout_6 = new QGridLayout(luxTab);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        luxTabLayout = new QGridLayout();
        luxTabLayout->setObjectName(QStringLiteral("luxTabLayout"));

        gridLayout_6->addLayout(luxTabLayout, 0, 0, 1, 1);

        chartTabs->addTab(luxTab, QString());

        verticalLayout_2->addWidget(chartTabs);


        gridLayout_2->addLayout(verticalLayout_2, 0, 1, 1, 1);

        projectScout_2 = new QWidget(centralwidget);
        projectScout_2->setObjectName(QStringLiteral("projectScout_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(projectScout_2->sizePolicy().hasHeightForWidth());
        projectScout_2->setSizePolicy(sizePolicy1);
        projectScout = new QHBoxLayout(projectScout_2);
        projectScout->setObjectName(QStringLiteral("projectScout"));
        line = new QFrame(projectScout_2);
        line->setObjectName(QStringLiteral("line"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy2);
        line->setLineWidth(1);
        line->setMidLineWidth(2);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        projectScout->addWidget(line);

        label = new QLabel(projectScout_2);
        label->setObjectName(QStringLiteral("label"));

        projectScout->addWidget(label);


        gridLayout_2->addWidget(projectScout_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 962, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuCommands = new QMenu(menubar);
        menuCommands->setObjectName(QStringLiteral("menuCommands"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuCommands->menuAction());
        menuFile->addAction(actionOpen_file);
        menuFile->addSeparator();
        menuFile->addAction(actionPrint);
        menuCommands->addAction(actionShow_last_command_send);
        menuCommands->addAction(actionLast_data_recieved);

        retranslateUi(MainWindow);

        chartTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen_file->setText(QApplication::translate("MainWindow", "Open file", nullptr));
        actionShow_last_command_send->setText(QApplication::translate("MainWindow", "Last command send", nullptr));
        actionLast_data_recieved->setText(QApplication::translate("MainWindow", "Last data recieved", nullptr));
        actionPrint->setText(QApplication::translate("MainWindow", "Print", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        startButton->setText(QApplication::translate("MainWindow", "Start", nullptr));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        pauseButton->setText(QApplication::translate("MainWindow", "Pause", nullptr));
        resumeButton->setText(QApplication::translate("MainWindow", "Resume", nullptr));
        chartTabs->setTabText(chartTabs->indexOf(temperatureTab), QApplication::translate("MainWindow", "Temperature", nullptr));
        chartTabs->setTabToolTip(chartTabs->indexOf(temperatureTab), QApplication::translate("MainWindow", "Temperature chart", nullptr));
        chartTabs->setTabText(chartTabs->indexOf(rhTab), QApplication::translate("MainWindow", "RH", nullptr));
        chartTabs->setTabToolTip(chartTabs->indexOf(rhTab), QApplication::translate("MainWindow", "Relative Humidity chart", nullptr));
        chartTabs->setTabText(chartTabs->indexOf(co2Tab), QApplication::translate("MainWindow", "CO2", nullptr));
        chartTabs->setTabToolTip(chartTabs->indexOf(co2Tab), QApplication::translate("MainWindow", "Carbon dioxide chart", nullptr));
        chartTabs->setTabText(chartTabs->indexOf(tab_2), QApplication::translate("MainWindow", "PAR", nullptr));
        chartTabs->setTabToolTip(chartTabs->indexOf(tab_2), QApplication::translate("MainWindow", "Photosynthetically active radiation chart", nullptr));
        chartTabs->setTabText(chartTabs->indexOf(luxTab), QApplication::translate("MainWindow", "Lux", nullptr));
        chartTabs->setTabToolTip(chartTabs->indexOf(luxTab), QApplication::translate("MainWindow", "Illuminance chart", nullptr));
        label->setText(QApplication::translate("MainWindow", "Project SCOUT - 2018", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuCommands->setTitle(QApplication::translate("MainWindow", "Commands", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
