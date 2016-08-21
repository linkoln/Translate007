#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qaction.h>
#include <qdebug.h>
#include <qkeysequence.h>
#include <qdatastream.h>
#include <qfile.h>
#include <qnetworkaccessmanager.h>
#include <qurl.h>
#include <qjsondocument.h>

//#include <curl/easy.h>
#include <curl/curl.h>
#include <curl/multi.h>
#ifndef WIN32
#  include <unistd.h>
#endif
#include <iostream>
#include <assert.h>
#include <string>

FILE * headerfile;
FILE * bodyfile;
CURL *curl_handle;

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Translate"));
    setToolTip(tr("Translate"));
    setWindowIconText(tr("Translate"));
    setWindowIcon(QIcon(":/Image/logo.jpg"));

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

//    m_reply = new QNetworkReply();
//    m_request = new QNetworkRequest();

    ui->pushButton->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(TranslateSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

struct stStu
{
    int no;
    string name;
    string address;
};

size_t print_data(void*ptr,size_t size,size_t nmemb,void*stream)
{
    QFile file("file.txt");
    file.open(QIODevice::ReadWrite);
    QDataStream stream2(&file);
    stream2<<(char*)stream;
    file.close();
//    printf("body: %p stream: %p head: %p\n", bodyfile, stream, headerfile);
//    printf("ptr: %p size: %d nmemb: %d: ",ptr,size,nmemb);
//    cout<<(char*)stream<<endl;
    int written = fwrite(ptr, size, nmemb, (FILE *)stream);
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

#define HEAD_OUT "/home/lin/Documents/head.out"
#define BODY_OUT "/home/lin/Documents/body.out"

void MainWindow::TranslateSlot()
{
//    FILE * headerfile;
//    FILE * bodyfile;
//    static const char * headerfilename = HEAD_OUT;
//    static const char * bodyfilename = BODY_OUT;
    int res = 0;
    QString doctype = "json";
    QString str = ui->lineEdit->text();
    QString urlstr = QString("http://fanyi.youdao.com/openapi.do?keyfrom=Translate007&"
                  "key=1061359031&type=data&doctype=%1&version=1.1&q=%2").arg(doctype).arg(str);
//    curl_easy_setopt(curl_handle,CURLOPT_VERBOSE,1);
//    curl_easy_setopt(curl_handle,CURLOPT_URL,url.toLocal8Bit().data());
//    curl_easy_setopt(curl_handle,CURLOPT_WRITEFUNCTION,print_data);

//    headerfile = fopen(headerfilename, "wb");
//    if(headerfilename == NULL)
//    {
//        curl_easy_cleanup(curl_handle);
//        return;
//    }

//    bodyfile = fopen(bodyfilename, "wb");
//    if(bodyfile == NULL)
//    {
//        curl_easy_cleanup(curl_handle);
//        return;
//    }

//    printf("head: %p body: %p\n", headerfile, bodyfile);

//    char *data = new char[100];
//    curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, headerfile);
//    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
//    curl_easy_setopt(curl_handle,CURLOPT_WRITEDATA,data);

//    res = curl_easy_perform(curl_handle);
//    if (res != CURLE_OK) {
//        qDebug()<<url<<"is not performing successfully";
//    }else{
//        qDebug() << url << "is performing successfully";
//    }


    QUrl url(urlstr);
    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    m_request.setUrl(url);
    m_reply = accessManager->get(m_request);
    connect(accessManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    QString result;
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    const QByteArray bytes = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes);
    QVariantMap varMap = jsonDoc.toVariant().toMap();

    {
        QVariant basicVar = varMap["basic"];
        QVariantMap basicMap = basicVar.toMap();

        QVariant explainVar = basicMap["explains"];
        QVariantList explainList = explainVar.toList();

        result = result + "[basic explains]:\n";

        foreach (const QVariant & item, explainList) {
            QString itemStr = item.toString();
            result = result + itemStr + "\n";
        }
    }

    ui->textEdit->setText(result);
}

