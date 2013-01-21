#-------------------------------------------------
#
# Project created by QtCreator 2012-12-23T14:41:35
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TronClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tronclient.cpp \
    baseagent.cpp \
    agent.cpp \
    mapdrawer.cpp

HEADERS  += mainwindow.h \
    tronmap.h \
    tronclient.h \
    baseagent.h \
    agent.h \
    mapdrawer.h

FORMS    += mainwindow.ui


