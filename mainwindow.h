#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QNetworkDatagram>

#define PORT 1488

const std::string my_ip = "192.168.13.79";

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

    void initSocket();
    void readPendingDatagrams();
    void sendDatagrams();

    void on_pushButton_clicked();

    void update_text();

private:
    Ui::MainWindow *ui;
    QUdpSocket * udpSocket;
    std::vector<QString> recv_messages;



};
#endif // MAINWINDOW_H
