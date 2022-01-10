#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    status = false;
    connect(&tcpSocket,&QTcpSocket::connected,this,&MainWindow::onConnected);
    connect(&tcpSocket,&QTcpSocket::disconnected,this,&MainWindow::onDisconnected);
    connect(&tcpSocket,&QTcpSocket::readyRead,this,&MainWindow::onReadyRead);
    connect(&tcpSocket,&QTcpSocket::errorOccurred,this,&MainWindow::onError);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sendButton_clicked()
{
    QString msg = ui->sendEdit->text();
    if(msg != "")
    {
        msg = userName + ":" + msg;
        tcpSocket.write(msg.toUtf8());
        ui->sendEdit->clear();
    }
}


void MainWindow::on_connectButton_clicked()
{
    if(status == false)
    {
        serverIP.setAddress(ui->ipEdit->text());
        serverPort = ui->portEdit->text().toShort();
        userName = ui->nameEdit->text();

        tcpSocket.connectToHost(serverIP,serverPort);
    }
    else
    {
        QString msg = userName+":离开了聊天室。";
        tcpSocket.write(msg.toUtf8());
        tcpSocket.disconnectFromHost();
    }
}

void MainWindow::onConnected()
{
    status = true;
    ui->connectButton->setText("断开服务器连接");
    ui->sendButton->setEnabled(true);
    ui->ipEdit->setEnabled(false);
    ui->portEdit->setEnabled(false);
    ui->nameEdit->setEnabled(false);

    QString msg = userName+":进入了聊天室。";
    tcpSocket.write(msg.toUtf8());
}

void MainWindow::onDisconnected()
{
    status = false;
    ui->connectButton->setText("连接服务器");
    ui->sendButton->setEnabled(false);
    ui->ipEdit->setEnabled(true);
    ui->portEdit->setEnabled(true);
    ui->nameEdit->setEnabled(true);
}

void MainWindow::onReadyRead()
{
    if(tcpSocket.bytesAvailable() > 0)
    {
        QByteArray buf = tcpSocket.readAll();
        ui->listWidget->addItem(buf);
        ui->listWidget->scrollToBottom();
    }
}

void MainWindow::onError()
{
    QMessageBox::critical(this,"ERROR",tcpSocket.errorString());
}

