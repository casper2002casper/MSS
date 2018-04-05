#-------------------------------------------------
#
# Project created by QtCreator 2018-03-11T17:46:02
#
#-------------------------------------------------

QT       += core gui\
            printsupport\
            charts\
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MMS_Control
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    charts.cpp \
    main.cpp \
    mainwindow.cpp \
    basestationserver.cpp \
    basestationthread.cpp

HEADERS += \
    mainwindow.h \
    charts.h \
    basestationserver.h \
    basestationthread.h
FORMS += \
    mainwindow.ui \
    startdialog.ui \
    pausedialog.ui \
    measuredialog.ui \
    drivedialog.ui \
    automaticmode.ui

SUBDIRS += \
    MMS_Control.pro

RC_FILE = MMS_Control.rc

ICON = MMS_Control.icns

RESOURCES += \
    resources.qrc
