#pragma once

#include <QApplication>
#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QRegExpValidator>
#include <QRegExp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QTcpSocket *tcpSock;
    Ui::MainWindow *ui;
private slots:
    void tcpConnect();
    void tcpConnected();
    void tcpDisconnect();
    void tcpDisconnected();
    void tcpReadData();
//signals:
    //signals here
};
