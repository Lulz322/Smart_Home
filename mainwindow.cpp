#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSocket();
}


void MainWindow::initSocket(){
    udpSocket = new QUdpSocket(this);

    udpSocket->bind(QHostAddress::AnyIPv4, 1488);

    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readPendingDatagrams);
}

void MainWindow::update_text(){
    QString big_msg;

    for (auto it : recv_messages){
        big_msg += it + "\n";
    }
    ui->textBrowser->setText(big_msg);
}

void MainWindow::readPendingDatagrams(){
    QByteArray datagram;

    QString msg;
    while (udpSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        msg = datagram.senderAddress().toString();
        msg += " :" + datagram.data();
        recv_messages.push_back(msg);
        update_text();
    }
}

void MainWindow::sendDatagrams(){
    QByteArray qarray(my_ip.c_str());
    QHostAddress qhost("192.168.13.167");
    udpSocket->writeDatagram(qarray, qhost, PORT);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    sendDatagrams();
}
