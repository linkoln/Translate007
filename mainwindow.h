#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkRequest>
#include <qnetworkreply.h>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void TranslateSlot();
    void replyFinished(QNetworkReply * reply);

private:
    QNetworkReply *m_reply;
    QNetworkRequest m_request;
};

#endif // MAINWINDOW_H
