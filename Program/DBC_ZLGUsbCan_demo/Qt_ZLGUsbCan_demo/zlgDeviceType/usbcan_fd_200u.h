#ifndef USBCAN_FD_200U_H
#define USBCAN_FD_200U_H

#include <QObject>
#include <QDebug>
#include "zlgcan.h"
#include <QEventLoop>
#include <QThread>
#include <QDateTime>
#include <QTimer>

class USBCAN_FD_200U : public QObject
{
    Q_OBJECT
public:
    explicit USBCAN_FD_200U(QObject *parent = nullptr);

signals:


public slots:


public:
    bool openDevice_fd_200u();
    bool closeDevice_fd_200u();
    bool timerSend_fd_200u();
    void Send_fd_200u();
    // 构造报文函数
    void get_canfd_frame_fd_200u(ZCAN_TransmitFD_Data& canfd_data, canid_t id);
    // 接收线程函数
    static void thread_taskFD_fd_200u(CHANNEL_HANDLE handle);
    //
    void sleepMs_fd_200u(int msec);
private:
    //保存设备句柄
    DEVICE_HANDLE deviceKey;
    //保存通道句柄
    CHANNEL_HANDLE channelKey[2];
    //创建线程
    QThread *canThread;
    // 线程指针数组
    QVector<QThread*> thd_handle;


};

#endif // USBCAN_FD_200U_H
