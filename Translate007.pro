#-------------------------------------------------
#
# Project created by QtCreator 2016-08-16T21:59:21
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Translate007
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -L"/usr/local/lib" -lcurl

RESOURCES += \
    resources.qrc
