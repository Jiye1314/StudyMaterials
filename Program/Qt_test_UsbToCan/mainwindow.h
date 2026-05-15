#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "zlgcan.h"
#include <QEventLoop>
#include <QTimer>
#include <QThread>



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

    void on_bt_getDeviceInf_clicked();

    void on_bt_closeDev_clicked();

    void on_bt_send_clicked();

private:
    void OpenDevice();
    void get_can_frame(ZCAN_Transmit_Data& can_data, canid_t id);
    // 静态线程函数
    static void thread_task(CHANNEL_HANDLE channelKey);
    // 线程指针数组
    QVector<QThread*> thd_handle;
    //
    void sleepMs(int msec);

private:
    Ui::MainWindow *ui;

    //保存设备句柄
    DEVICE_HANDLE deviceKey;

    //保存通道句柄
    CHANNEL_HANDLE channelKey[2];

    //创建线程
    QThread *canThread;
};
#endif // MAINWINDOW_H
