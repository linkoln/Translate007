#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
=======
#include <QNetworkRequest>
#include <qnetworkreply.h>
#include <QKeyEvent>
>>>>>>> 757405f74b555d7edf5869bcd8120b86bdac4680

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

<<<<<<< HEAD
private:
    Ui::MainWindow *ui;
=======
protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void TranslateSlot();
    void replyFinished(QNetworkReply * reply);

private:
    Ui::MainWindow *ui;
    QNetworkReply *m_reply;
    QNetworkRequest m_request;
>>>>>>> 757405f74b555d7edf5869bcd8120b86bdac4680
};

#endif // MAINWINDOW_H
