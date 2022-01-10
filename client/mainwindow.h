#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();

    void on_connectButton_clicked();

    void onConnected();

    void onDisconnected();

    void onReadyRead();

    void onError();

private:
    Ui::MainWindow *ui;
    bool status;
    QTcpSocket tcpSocket;
    QHostAddress serverIP;
    quint16 serverPort;
    QString userName;
};
#endif // MAINWINDOW_H
