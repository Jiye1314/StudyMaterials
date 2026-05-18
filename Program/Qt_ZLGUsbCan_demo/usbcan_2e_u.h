#ifndef USBCAN_2E_U_H
#define USBCAN_2E_U_H

#include <QObject>
#include <QDebug>
#include "zlgcan.h"
#include <QEventLoop>
#include <QThread>
#include <QDateTime>
#include <QTimer>

class USBCAN_2E_U : public QObject
{
    Q_OBJECT
public:
    explicit USBCAN_2E_U(QObject *parent = nullptr);

signals:

public:
//    bool openDevice();
//    bool closeDevice();
//    bool timerSend();
//    bool send();
//    void get_can_frame(ZCAN_Transmit_Data& can_data, canid_t id);
//    void thread_task(CHANNEL_HANDLE handle);

private:
//    //保存设备句柄
//    DEVICE_HANDLE deviceKey;
//    //保存通道句柄
//    CHANNEL_HANDLE channelKey[2];

//    //线程指针数组
//    QVector<QThread*> thd_handle;

};

#endif // USBCAN_2E_U_H
