#ifndef USBCAN_FD_200U_H
#define USBCAN_FD_200U_H

#include <QObject>
#include <QDebug>
#include "zlgcan.h"
#include <QEventLoop>
#include <QThread>
#include <QDateTime>
#include <QTimer>
#include "zdbc_x86/zdbc.h"

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
    void Send_fd_200u();
    // 接收 CANFD 线程函数
    static void thread_task_fd_200u(CHANNEL_HANDLE handle);
    void sleepMs_fd_200u(int msec);
    //===================================================================================
    // 构造各报文函数
    void buildSyncFrame(ZCAN_Transmit_Data &can);
    void buildTimeStampFrame(ZCAN_Transmit_Data &can);
    void buildTractionHBFrame(ZCAN_Transmit_Data &can);
    void buildLiftHBFrame(ZCAN_Transmit_Data &can);
    void buildPowerTracLHBFrame(ZCAN_Transmit_Data &can);
    void buildModuleCtrlFrame(ZCAN_Transmit_Data &can);
    void buildTractionPDO4Frame(ZCAN_Transmit_Data &can);
    // 定时发送CAN报文函数
    bool timerSend_can();
    // 接收 CAN 线程函数
    void thread_task_can(CHANNEL_HANDLE handle);
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
