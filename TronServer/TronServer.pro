#-------------------------------------------------
#
# Project created by QtCreator 2012-12-23T14:40:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TronServer
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           tronserver.cpp \
    mapdrawer.cpp

HEADERS  += mainwindow.h \
            tronmap.h \
            tronserver.h \
    mapdrawer.h

FORMS    += mainwindow.ui


OTHER_FILES += \  
    myapp.rc \
    favicon.ico

RC_FILE = myapp.rc









