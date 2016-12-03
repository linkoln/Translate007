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

RESOURCES += resources.qrc

unix{
    LIBS += -L"/usr/local/lib" -lcurl
}

win32{
    INCLUDEPATH += "E:\\LinLianQin\\lib\\Librarys\\curl_7_50_0\\include"
    INCLUDEPATH += "E:\\LinLianQin\\lib\\Librarys\\jsoncpp\\include"

    LIBS += -L"E:\\LinLianQin\\lib\\Librarys\\curl_7_50_0\\lib" -llibcurl
    LIBS += -L"E:\\LinLianQin\\lib\\Librarys\\jsoncpp\\lib" -ljsoncpp
}
