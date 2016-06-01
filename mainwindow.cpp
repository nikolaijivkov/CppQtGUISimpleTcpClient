#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    tcpSock(new QTcpSocket(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegExpValidator *ipRegExValidator = new QRegExpValidator(QRegExp(R"(^\d{1,4}\.\d{1,4}\.\d{1,4}\.\d{1,4}$)"), this);
    ui->ipAddressLineEdit->setValidator(ipRegExValidator);

    QRegExpValidator *portRegExValidator = new QRegExpValidator(QRegExp(R"(\d*)"), this);
    ui->portLineEdit->setValidator(portRegExValidator);

    this->setLayout(ui->verticalLayout);
    ui->disconnectBtn->setEnabled(false);

    //tcpSock: connectBtn button clicked and tcpConnected events
    connect(ui->connectBtn, SIGNAL(clicked()), this, SLOT(tcpConnect()));
    connect(tcpSock, SIGNAL(connected()), this, SLOT(tcpConnected()));

    //tcpSock: disconnectBtn button clicked and tcpDisconnected events
    connect(ui->disconnectBtn, SIGNAL(clicked()), this, SLOT(tcpDisconnect()));
    connect(tcpSock, SIGNAL(disconnected()), this, SLOT(tcpDisconnected()));

    //tcp data ready to be read event
    connect(tcpSock, SIGNAL(readyRead()), this, SLOT(tcpReadData()));
}

MainWindow::~MainWindow()
{   // cleanup for tcpSocket and ui
    tcpSock->disconnectFromHost();
    tcpSock->close();
    delete ui;
}

void MainWindow::tcpConnect()
{
    QString address = ui->ipAddressLineEdit->text();
    if(address.isEmpty()){
        address = "127.0.0.1";
        ui->ipAddressLineEdit->setText(address);
    }
    QString port = ui->portLineEdit->text();
    if(port.isEmpty()){
        port = "5005";
        ui->portLineEdit->setText(port);
    }
    tcpSock->connectToHost(address, port.toInt());
}

void MainWindow::tcpConnected()
{
    ui->connectBtn->setText("Connected!");
    ui->connectBtn->setEnabled(false);

    ui->disconnectBtn->setText("Disconect");
    ui->disconnectBtn->setEnabled(true);
}

void MainWindow::tcpDisconnect()
{
    tcpSock->disconnectFromHost();
}

void MainWindow::tcpDisconnected()
{
    ui->connectBtn->setText("Connect");
    ui->connectBtn->setEnabled(true);

    ui->disconnectBtn->setText("Disconected!");
    ui->disconnectBtn->setEnabled(false);
}

void MainWindow::tcpReadData()
{
    QByteArray data = tcpSock->readAll();
    ui->plainTextEdit->appendPlainText(data);  // QString(data));
}
