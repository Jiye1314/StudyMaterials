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
    //更新计数
    void signalsSendNum(int num);
    // 将收到的 CAN 帧数据发给 UI 显示
    void signalsReceivedFrame(uint32_t canId, uint8_t dlc, const QByteArray &data);

public slots:
    void slotsSetSpeedSet1PWMenable1(uint8 num1,uint8 num2);

    void onTimerLiftPDO();      // LiftPDO1 定时回调
    void onTimerTractionPDO();  // TractionPDOF 定时回调

public:
    bool openDevice_fd_200u();
    bool closeDevice_fd_200u();
    void Send_fd_200u();
    // 接收 CANFD 线程函数
    void thread_task_fd_200u(CHANNEL_HANDLE handle);
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
    void buildLiftPDO1Can1Frame(ZCAN_Transmit_Data &can, uint8_t messCount);
    void buildTractionPDOFFrame(ZCAN_Transmit_Data &can, uint8_t messCountF);
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

    uint8 L_speedSet1 = 0;
    uint8 L_PWMenable1 = 1;

    QTimer *m_timerLiftPDO;     // LiftPDO1 定时器 (10ms)
    QTimer *m_timerTractionPDO; // TractionPDOF 定时器 (2ms)
    //等差循环计算
    uint8_t m_messCountL = 0;   // L_MessCount1 计数器
    uint8_t m_messCountT = 0;   // T_MessCountF 计数器
private:

};

#endif // USBCAN_FD_200U_H
