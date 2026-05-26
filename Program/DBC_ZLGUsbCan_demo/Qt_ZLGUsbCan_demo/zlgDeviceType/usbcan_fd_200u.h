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
    void signalsReceivedFrame(int channel,int canId, int dlc, const QByteArray &data);
    //数据断开信号
    void signalsStatus();

public slots:
    void slotsSetLSpeedSet1(double num);
    void slotsSetLPWMenable1(int num);
    void onTimerLiftPDO();      // LiftPDO1 定时回调
    void onTimerTractionPDO();  // TractionPDOF 定时回调
    void onTimerStatus();   //检测发送状态定时

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
    void buildLiftPDO1Can1Frame(ZCAN_Transmit_Data &can, int messCount);
    void buildTractionPDOFFrame(ZCAN_Transmit_Data &can, int messCountF);
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

    int L_speedSet1 = 0;
    int L_PWMenable1 = 1;

    QTimer *m_timerLiftPDO;     // LiftPDO1 定时器 (10ms)
    QTimer *m_timerTractionPDO; // TractionPDOF 定时器 (2ms)
    QTimer *m_timerStatus;  //检测发送状态定时器
    //等差循环计算
    int m_messCountL = 0;   // L_MessCount1 计数器
    int m_messCountT = 0;   // T_MessCountF 计数器

    int idcount = 0;//ui计数显示
private:

};

#endif // USBCAN_FD_200U_H
