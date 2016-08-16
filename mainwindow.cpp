#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qaction.h>
#include <qdebug.h>
#include <qkeysequence.h>
//#include <cur

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction *actionTranslate = new QAction();
    actionTranslate->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    connect(actionTranslate,SIGNAL(triggered(bool)),this,SLOT(TranslateSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TranslateSlot()
{
    QString doctype = "json";
    QString url = "http://fanyi.youdao.com/openapi.do?keyfrom=Translate007&"
                  "key=1061359031&type=data&doctype=%1&version=1.1&q=%2";
    QString str = ui->lineEdit->text();
    url.arg(doctype).arg(str);
    qDebug()<<url;
}
