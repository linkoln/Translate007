#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qaction.h>
#include <qdebug.h>
#include <qkeysequence.h>
//#include <curl/easy.h>
#include <curl/curl.h>
#include <curl/multi.h>
#ifndef WIN32
#  include <unistd.h>
#endif
#include <iostream>


CURL *curl_handle;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

//    QAction *actionTranslate = new QAction();
//    actionTranslate->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
//    connect(actionTranslate,SIGNAL(triggered(bool)),this,SLOT(TranslateSlot()));
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(TranslateSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

size_t print_data(void*ptr,size_t size,size_t mem,void*stream)
{
    std::cout<<"ptr"<<(char*)ptr<<" size: "<<size<<" mem: "<<mem<<" stream: "<<(char*)stream<<endl;
    return 0;
}

void MainWindow::TranslateSlot()
{
    int res = 0;
    QString doctype = "json";
    QString str = ui->lineEdit->text();
    QString url = QString("http://fanyi.youdao.com/openapi.do?keyfrom=Translate007&"
                  "key=1061359031&type=data&doctype=%1&version=1.1&q=%2").arg(doctype).arg(str);
    curl_easy_setopt(curl_handle,CURLOPT_URL,url.toLocal8Bit().data());
    curl_easy_setopt(curl_handle,CURLOPT_WRITEFUNCTION,print_data);
    res = curl_easy_perform(curl_handle);
    if (res != CURLE_OK) {
        qDebug()<<url<<"is not performing successfully";
    }else{
        qDebug() << url << "is performing successfully";
    }
}
