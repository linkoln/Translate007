#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qaction.h>
#include <qdebug.h>
#include <qkeysequence.h>
#include <qdatastream.h>
#include <qfile.h>
#include <qnetworkaccessmanager.h>
#include <qurl.h>

#ifndef WIN32
#  include <unistd.h>
#endif

#include <iostream>
#include <assert.h>
#include <string>

using namespace std;

//curl
#include <curl/curl.h>
#include <curl/multi.h>
#include <curl/easy.h>

//jsoncpp
#include <json/json.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Translate"));
    setToolTip(tr("Translate"));
    setWindowIconText(tr("Translate"));
    setWindowIcon(QIcon(":/Image/logo.jpg"));

    ui->pushButton->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(TranslateSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

size_t print_data(void*ptr,size_t size,size_t nmemb,void*stream)
{
    QFile file("file.txt");
    file.open(QIODevice::ReadWrite);
    QDataStream stream2(&file);
    stream2<<(char*)stream;
    file.close();

    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
        TranslateSlot();
        break;
    default:
        break;
    }
}

void MainWindow::TranslateSlot()
{
    QString doctype = "json";
    QString str = ui->lineEdit->text();
    QString urlstr = QString("http://fanyi.youdao.com/openapi.do?keyfrom=Translate007&"
                  "key=1061359031&type=data&doctype=%1&version=1.1&q=%2").arg(doctype).arg(str);

    QUrl url(urlstr);
    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    m_request.setUrl(url);
    m_request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json;charset:utf-8");
    m_reply = accessManager->get(m_request);

    connect(accessManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}

//注意QString::fromUtf8的使用
void MainWindow::replyFinished(QNetworkReply *reply)
{
    QByteArray bytes = reply->readAll();

    qDebug()<<QString::fromUtf8(bytes.data());

    Json::Reader reader;
    Json::Value root;
    const char * str = bytes.data();
    if (!reader.parse(str,root)) {
        return;
    }

    Json::Value basicarray = root["basic"];
    Json::Value explains = basicarray["explains"];

    QString result;
    result = result + "[basic explains]:\n";

    //如果没有解释,则直接返回
    if (!explains.isArray() || explains.size() < 0) {
        return;
    }

    for (int i = 0;i < explains.size();i++) {
        QString itemStr = QString::fromUtf8(explains[i].asString().c_str());
        result = result + itemStr + "\n";
    }

    ui->textEdit->setText(result);
}
