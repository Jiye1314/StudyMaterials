#include "usbcan_fd_200u.h"

bool g_thd_run_fd_200u = 0;
bool timer_send_fd_200u = 0;

USBCAN_FD_200U::USBCAN_FD_200U(QObject *parent) : QObject(parent)
{
    //初始化定时器
    initAllTimer();
}


bool USBCAN_FD_200U::openDevice_fd_200u()
{
    char path[20] = {0};

    //打开设备
    DEVICE_HANDLE retOpenDev = ZCAN_OpenDevice(ZCAN_USBCANFD_200U, 0, 0);

    qDebug() << "打开设备返回:" << retOpenDev;
    if (retOpenDev == INVALID_DEVICE_HANDLE) {
        qDebug() << "打开设备失败";
        return false;
    }else{
        qDebug() << "打开设备成功";
    }

    //保存设备句柄
    deviceKey = retOpenDev;

    for (int i=0;i<2;i++)
    {
        // 设置 CANFD 标准为 ISO
        sprintf_s(path, "%d/can_standard", i);
        if (0 == ZCAN_SetValue(deviceKey, path, "0")) {
            qDebug()<< "set canfd standard ok";
        }

        // 设置仲裁域波特率
        sprintf(path, "%d/canfd_abit_baud_rate", i);
        if (!ZCAN_SetValue(deviceKey, path, "500000")) {
            qDebug() << "设置仲裁域波特率失败 " << i;
            closeDevice_fd_200u();
            break;
        } else {
            qDebug() << "设置仲裁域波特率成功 " << i;
        }

        // 设置数据域波特率
        sprintf(path, "%d/canfd_dbit_baud_rate", i);
        if (!ZCAN_SetValue(deviceKey, path, "500000")) {
            qDebug() << "设置数据域波特率失败 " << i;
            closeDevice_fd_200u();
            break;
        } else {
            qDebug() << "设置数据域波特率成功 " << i;
        }

        //初始化通道
        ZCAN_CHANNEL_INIT_CONFIG channelConfig;
        memset(&channelConfig, 0, sizeof(channelConfig));

        channelConfig.can_type = TYPE_CANFD;  // CANFD模式 TYPE_CANFD 或 1  CAN模式为TYPE_CAN
        channelConfig.can.mode = 0;

        //初始化
        channelKey[i] = ZCAN_InitCAN(deviceKey,i, &channelConfig);
        if (channelKey[i] == INVALID_CHANNEL_HANDLE)
        {
            qDebug()<< "初始化通道失败 "<<i;
            closeDevice_fd_200u();
            return false;
        }else{
            qDebug()<< "初始化通道成功 "<<i;
        }

        // 复位 CAN 控制器，清除 Bus Off 状态（Bus Off 时发不出帧）
        UINT retReset = ZCAN_ResetCAN(channelKey[i]);
        qDebug()<<"CAN 复位返回:"<< retReset << " 通道 " << i;

        // 设置终端电阻
        sprintf(path, "%d/initenal_resistance", i);
        UINT retRes = ZCAN_SetValue(deviceKey, path, "1");
        if (retRes != STATUS_OK)
        {
            qDebug()<< "使能终端电阻失败 " << i;
        }

        // 设置发送超时
        sprintf_s(path, "%d/tx_timeout", i);
        ZCAN_SetValue(deviceKey, path, "100");

        //        // 软件环回模式（自发自收，无需外部接线）
        //        sprintf(path, "%d/mode", i);
        //        ZCAN_SetValue(deviceKey, path, "1"); // 1 = 环回模式

        //发送失败重试策略
        ZCAN_SetValue(deviceKey, "0/set_tx_retry_policy", "1"); //1 -发送失败不重传 2 -发送失败重传，直到总线关闭


        // 启动 CAN 通道
        if (!ZCAN_StartCAN(channelKey[i]))
        {
            qDebug()<<"启动 CAN 通道失败 "<<i;
            closeDevice_fd_200u();
            break;
        }else{
            qDebug()<<"启动 CAN 通道成功 "<<i;
        }


        // 启动接收线程
        QThread *t = QThread::create([=]() {
            thread_task_fd_200u(channelKey[i]);
        });
        thd_handle.append(t);
        t->start();

    }
    ZCAN_ClearBuffer(deviceKey);
    g_thd_run_fd_200u = 1;
    return true;
}

//==========================================================================================
//关闭连接
bool USBCAN_FD_200U::closeDevice_fd_200u()
{
    closeAllSend();

    g_thd_run_fd_200u = 0;

    //关闭线程
    for (auto *t : thd_handle)
    {
        t->quit();
        t->wait();
        delete t;
    }
    thd_handle.clear();

    UINT retCloseDev = ZCAN_CloseDevice(deviceKey);
    qDebug() << "关闭设备返回:" << retCloseDev;
    if (retCloseDev)
    {
        qDebug() << "关闭设备成功";
        return true;
    }else{
        qDebug() << "关闭设备失败";
        return false;
    }
}

//===========================================================================================

//构造SYNC报文
void USBCAN_FD_200U::buildSyncFrame(ZCAN_Transmit_Data &can)
{
    memset(&can,0,sizeof (can));
    can.frame.can_id = MAKE_CAN_ID(0x080,0,0,0);    // CANFD ID + STD/EXT + DATA/RMT
    can.frame.can_dlc = 1;          //数据长度
    can.transmit_type = 0;      //正常发送模式
    can.frame.data[0] = 0;      //值
}

//构造TimerStamp报文
void USBCAN_FD_200U::buildTimeStampFrame(ZCAN_Transmit_Data &can)
{
    memset(&can,0,sizeof (can));
    can.frame.can_id = MAKE_CAN_ID(0x0FF,0,0,0);
    can.frame.can_dlc = 4;
    can.transmit_type = 0;
    can.frame.data[0] = 0;
}

//构造TractionHB报文
void USBCAN_FD_200U::buildTractionHBFrame(ZCAN_Transmit_Data &can)
{
    memset(&can,0,sizeof (can));
    can.frame.can_id = MAKE_CAN_ID(0x0701,0,0,0);
    can.frame.can_dlc = 1;
    can.transmit_type = 0;
    can.frame.data[0] = 5;
}

//构造LiftHB报文
void USBCAN_FD_200U::buildLiftHBFrame(ZCAN_Transmit_Data &can)
{
    memset(&can,0,sizeof (can));
    can.frame.can_id = MAKE_CAN_ID(0x0702,0,0,0);
    can.frame.can_dlc = 1;
    can.transmit_type = 0;
    can.frame.data[0] = 0x05;
}

//构造PowerTracLHB报文
void USBCAN_FD_200U::buildPowerTracLHBFrame(ZCAN_Transmit_Data &can)
{
    memset(&can,0,sizeof (can));
    can.frame.can_id = MAKE_CAN_ID(0x070A,0,0,0);
    can.frame.can_dlc = 1;
    can.transmit_type = 0;
    can.frame.data [0] = 0;
}

//构造ModuleCtrl报文
void USBCAN_FD_200U::buildModuleCtrlFrame(ZCAN_Transmit_Data &can)
{
    memset(&can,0,sizeof(can));
    can.frame.can_id = MAKE_CAN_ID(0x0000,0,0,0);
    can.frame.can_dlc = 2;
    can.transmit_type = 0;
    can.frame.data [0] = 1;
    can.frame.data [1] = 0;
}

//构造TractionPDO4报文
void USBCAN_FD_200U::buildTractionPDO4Frame(ZCAN_Transmit_Data &can)
{
    memset(&can,0,sizeof (can));
    can.frame.can_id = MAKE_CAN_ID(0x0481,0,0,0);
    can.frame.can_dlc = 4;
    can.transmit_type = 0;
    can.frame.data [0] = 0;
}

//构造LiftPDO1Can1报文(信号控制)
void USBCAN_FD_200U::buildLiftPDO1Can1Frame(ZCAN_Transmit_Data &can,int messCount)
{
    memset(&can,0,sizeof (can));
    can.frame.can_id = MAKE_CAN_ID(0x0182,0,0,0);
    can.frame.can_dlc = 8;
    can.transmit_type = 0;

    unsigned char L_MessCount1  = (messCount) % 16;  // 0~15 循环，等差+1

    can.frame.data[0] = 0;
    can.frame.data[1] = 0;
    can.frame.data[2] = 0xff & L_speedSet1;
    can.frame.data[3] = (L_speedSet1 >> 8) & 0xff;
    can.frame.data[4] = 0;
    can.frame.data[5] = 0x28 & 0xff;
    can.frame.data[6] = (0x02 & 0x03) | ((0x01 & 0x01) << 2) | (L_PWMenable1 & 0x01) << 3;
    can.frame.data[7] = (L_MessCount1 & 0x0f) << 4;
}

//构造TractionPDOF报文(信号控制)
void USBCAN_FD_200U::buildTractionPDOFFrame(ZCAN_Transmit_Data &can,int messCountF)
{
    memset(&can,0,sizeof (can));
    can.frame.can_id = MAKE_CAN_ID(0x0081,0,0,0);
    can.frame.can_dlc = 8;
    can.transmit_type = 0;

    unsigned char T_MessCountF  = (messCountF)%16;  // 0~15 循环，等差+1

    can.frame.data[0] = 0;
    can.frame.data[1] = 0;
    can.frame.data[2] = 0;
    can.frame.data[3] = 0;
    can.frame.data[4] = 0;
    can.frame.data[5] = 0;
    can.frame.data[6] = (T_MessCountF) << 4;
    can.frame.data[7] = 0;
}

//定时发送CAN报文
bool USBCAN_FD_200U::timerSend_can()
{
    if(!timer_send_fd_200u)
    {
        ZCAN_CHANNEL_ERR_INFO err_info;
        ZCAN_ReadChannelErrInfo(channelKey[0],&err_info);
        //qDebug() << err_info.error_code;

        QString path = QString("%1/auto_send").arg(m_txChannel);

        timer_send_fd_200u = 1;

        //定时发送 CAN 报文
        //SYNC报文
        ZCAN_AUTO_TRANSMIT_OBJ transmitObj;
        memset(&transmitObj,0,sizeof (transmitObj));
        transmitObj.index = 0;                      //定时列表索引
        transmitObj.enable = 1;                     //使能此索引
        transmitObj.interval = 10;                  //定时发送间隔
        buildSyncFrame(transmitObj.obj);               //构造SYNC报文
        ZCAN_SetValue(deviceKey,path.toStdString().c_str(),(const char*)&transmitObj); //设置定时发送

        //TimeStamp报文
        memset(&transmitObj,0,sizeof (transmitObj));
        transmitObj.index = 1;
        transmitObj.enable = 1;
        transmitObj.interval = 1000;
        buildTimeStampFrame(transmitObj.obj);
        ZCAN_SetValue(deviceKey,path.toStdString().c_str(),(const char*)&transmitObj);

        //Traction_Heartbeat报文
        memset(&transmitObj,0,sizeof (transmitObj));
        transmitObj.index = 2;
        transmitObj.enable = 1;
        transmitObj.interval = 40;
        buildTractionHBFrame(transmitObj.obj);
        ZCAN_SetValue(deviceKey,path.toStdString().c_str(),(const char*)&transmitObj);

        //Lift_Heartbeat报文
        memset(&transmitObj,0,sizeof(transmitObj));
        transmitObj.index = 3;
        transmitObj.enable = 1;
        transmitObj.interval = 40;
        buildLiftHBFrame(transmitObj.obj);
        ZCAN_SetValue(deviceKey,path.toStdString().c_str(),(const char*)&transmitObj);

        //        //Power1_TracL_Heartbeat报文
        //        memset(&transmitObj,0,sizeof (transmitObj));
        //        transmitObj.index = 4;
        //        transmitObj.enable = 1;
        //        transmitObj.interval = 40;
        //        buildPowerTracLHBFrame(transmitObj.obj);
        //        ZCAN_SetValue(deviceKey,"0/auto_send",(const char*)&transmitObj);

        //ModuleControl报文
        memset(&transmitObj,0,sizeof(transmitObj));
        transmitObj.index = 5;
        transmitObj.enable = 1;
        transmitObj.interval = 100;
        buildModuleCtrlFrame(transmitObj.obj);
        ZCAN_SetValue(deviceKey,path.toStdString().c_str(),(const char*)&transmitObj);

        //Traction_PDO4报文
        memset(&transmitObj,0,sizeof (transmitObj));
        transmitObj.index = 6;
        transmitObj.enable = 1;
        transmitObj.interval = 1000;
        buildTractionPDO4Frame(transmitObj.obj);
        ZCAN_SetValue(deviceKey,path.toStdString().c_str(),(const char*)&transmitObj);

        //开启两个定时器
        m_timerLiftPDO->start();
        m_timerTractionPDO->start();
        m_timerStatus->start();


        QString pathapply = QString("%1/apply_auto_send").arg(m_txChannel);
        //使能定时发送
        ZCAN_SetValue(deviceKey,pathapply.toStdString().c_str(), "0");
        qDebug() << "定时发送手动开启";
    }
    else
    {
        closeAllSend();
         qDebug() << "定时发送手动停止";
    }
    return timer_send_fd_200u;
}


//手动发送
bool USBCAN_FD_200U::Send_fd_200u(int length, QStringList data, uint32_t canId)
{
    //发送测试帧
    ZCAN_Transmit_Data frame;
    memset(&frame, 0, sizeof(frame));

    frame.frame.can_id = MAKE_CAN_ID(canId, type, 0, 0); // SYNC ID
    frame.frame.can_dlc = length;
    frame.transmit_type = 0;    //发送模式 ：正常发送

    // 按DLC长度填充数据（多余的截断，不足的补0）
    for(int i=0;i<8;i++)
    {
        if(i<length && i<data.size())
        {
            bool ok;
            uint8_t byte = data[i].toUInt(&ok,16);
            if(ok)
            {
                frame.frame.data[i] = byte;
            }
            else
            {
                frame.frame.data[i] = 0x00; // 解析失败补 0
            }
        }
        else
        {
            frame.frame.data[i] = 0x00;     // 超出DLC的部分补 0
        }
    }

    int retCount = ZCAN_Transmit(channelKey[0], &frame, 1);       //1帧
    if(!retCount)
    {
        qDebug()<<"发送失败！";
        return false;
    }

//    qDebug() << "手动发送:" << retCount << "帧"
//             << " ID: 0x" << QString::number(GET_ID(frame.frame.can_id), 16)
//             << " 数据:" << QString::number(frame.frame.data[0], 16);
    return true;
}

//CAN接收线程
void USBCAN_FD_200U::thread_task_fd_200u(CHANNEL_HANDLE handle)
{
    qDebug()<< "接收线程启动 handle:"<< handle << " g_thd_run=" << g_thd_run_fd_200u;
    ZCAN_Receive_Data data[100] = {};

    while (g_thd_run_fd_200u)
    {
        // 获取 CANFD 帧数量（type=1 / TYPE_CAN 表示 CANFD）
        int count = ZCAN_GetReceiveNum(handle, TYPE_CAN);

        if (count <= 0) {
            QThread::msleep(50);
            continue;
        }

        // 使用 ZCAN_Receive（通道句柄）
        int rcount = ZCAN_Receive(handle,data,100,10);

        for (int i = 0; i < rcount; ++i)
        {
            int channel = m_txChannel;
//            QByteArray hex;
//            for (int j = 0; j < data[i].frame.can_dlc; j++)
//            {
//                hex.append(QString("%1 ").arg(data[i].frame.data[j], 2, 16, QChar('0')));
//            }

//            qDebug() << "==================================================";
//            qDebug() << "通道:" << channel << " 接收报文";
//            qDebug() << "ID: 0x" << QString::number(data[i].frame.can_id, 16);
//            qDebug() << "长度:" << (int)data[i].frame.can_dlc;
//            qDebug() << "数据:" << hex;
//            qDebug() << "共接收:" << thcount << "次";
//            qDebug()<<"当前时间："<<QDateTime::currentDateTime();
//            emit signalsSendNum(++thcount);

            //记录内容
            int canId = GET_ID(data[i].frame.can_id);
            int dlc = data[i].frame.can_dlc;
            // 组装数据为 QByteArray
            QByteArray hexData;
            //格式转换到16进制
            for (int j = 0; j < dlc; j++)
            {
                hexData.append(QString("%1 ").arg(data[i].frame.data[j], 2, 16, QChar('0')).toUpper());
            }
            // 发射信号给 UI（所有帧都发，让 UI 过滤）
            emit signalsReceivedFrame(channel,canId, dlc, hexData);
            emit signalsSendNum(++idcount);
        }
    }
    qDebug()<< "按下关闭按钮，接收线程退出";
}

//===================================================================================
void USBCAN_FD_200U::thread_task_can(CHANNEL_HANDLE handle)
{
    //    int nChnl = (unsigned int)handle &0x000000FF;

    //    qDebug()<< "chnl: " << nChnl << "线程启动, handle:0x" << handle;

    //    ZCAN_Receive_Data data[100] = {};
    //    while (g_thd_run_fd_200u)
    //    {
    //        int count = ZCAN_GetReceiveNum(handle,0);        //获取CAN报文数量
    //        while(g_thd_run_fd_200u && count > 0)
    //        {
    //            int count = ZCAN_Receive(handle,data,100,10);
    //            for(int i=0;i<count;i++)
    //            {
    //                qDebug()<<"CHNL:"<<nChnl<<"返回 can ID:0x";
    //                qDebug()<<data[i].frame.can_id;
    //            }
    //            count -= count;
    //        }

    //        QThread::sleep(100);
    //    }
    //    qDebug()<<"chnl: "<<nChnl<<" thread 退出";
}

//关闭发送
void USBCAN_FD_200U::closeAllSend()
{
    timer_send_fd_200u = 0;

    //关闭定时发送
    ZCAN_SetValue(deviceKey, "0/clear_auto_send", "0"); //清空 0通道
    ZCAN_SetValue(deviceKey, "1/clear_auto_send", "0"); //清空 1通道

    // 停止 PDO 软件定时器
    if(m_timerLiftPDO)
    {
        m_timerLiftPDO->stop();
    }
    if(m_timerTractionPDO)
    {
        m_timerTractionPDO->stop();
    }

    // 计数器归零
    m_messCountL = 0;
    m_messCountT = 0;
}

//初始化所有定时器
void USBCAN_FD_200U::initAllTimer()
{
    //初始化两个同步定时器
    m_timerLiftPDO = new QTimer(this);
    connect(m_timerLiftPDO, &QTimer::timeout, this, &USBCAN_FD_200U::onTimerLiftPDO);
    m_timerLiftPDO->setInterval(10); // 10ms

    m_timerTractionPDO = new QTimer(this);
    connect(m_timerTractionPDO, &QTimer::timeout, this, &USBCAN_FD_200U::onTimerTractionPDO);
    m_timerTractionPDO->setInterval(2); // 2ms

    // 断线检测相关
    // 启动状态检测定时器
    m_timerStatus = new QTimer(this);
    connect(m_timerStatus, &QTimer::timeout, this, &USBCAN_FD_200U::onTimerStatus);
    m_timerStatus->start(1000); // 1000ms 检测一次
}

void USBCAN_FD_200U::slotsSetLSpeedSet1(double num)
{
    L_speedSet1 = num;
}

void USBCAN_FD_200U::slotsSetLPWMenable1(int num)
{
    L_PWMenable1 = num;
}

//LiftPDO1Can1报文(信号控制)定时器
void USBCAN_FD_200U::onTimerLiftPDO()
{
    ZCAN_Transmit_Data frame;
    buildLiftPDO1Can1Frame(frame, m_messCountL);

    ZCAN_Transmit(channelKey[m_txChannel], &frame, 1);

    m_messCountL = (m_messCountL + 1) % 16; // 0~15 循环，等差+1
}

//TractionPDOF报文(信号控制)定时器
void USBCAN_FD_200U::onTimerTractionPDO()
{
    ZCAN_Transmit_Data frame;
    buildTractionPDOFFrame(frame, m_messCountT);

    ZCAN_Transmit(channelKey[m_txChannel], &frame, 1);

    m_messCountT = (m_messCountT + 1) % 16; // 0~15 循环，等差+1
}


//定时器发送/接收状态
void USBCAN_FD_200U::onTimerStatus()
{
    // 1：检查设备在线状态
    UINT online = ZCAN_IsDeviceOnLine(deviceKey);
    if (online == STATUS_OFFLINE)
    {
        qDebug() << "usb设备连接已断开！";
        handleDisconnect();
        ZCAN_ClearBuffer(deviceKey);
        emit signalsExceptionStatus();
        return;
    }

    // 2：检查 CAN 控制器错误状态
    ZCAN_CHANNEL_ERR_INFO errInfo;
    if (ZCAN_ReadChannelErrInfo(channelKey[m_txChannel], &errInfo) == STATUS_OK)
    {
        // BusOff 检测
        if (errInfo.error_code == ZCAN_ERROR_CAN_BUSOFF)
        {
            qDebug() << "CAN 控制器总线关闭";
            handleDisconnect();
            ZCAN_ClearBuffer(deviceKey);
            emit signalsExceptionStatus();
            return;
        }
        // Error Passive
        if (errInfo.error_code == ZCAN_ERROR_CAN_PASSIVE)
        {
            qDebug() << "CAN 控制器消极错误";
            handleDisconnect();
            ZCAN_ClearBuffer(deviceKey);
            emit signalsExceptionStatus();
            return;
        }
        // Error Warning
        if (errInfo.error_code == ZCAN_ERROR_CAN_ERRALARM)
        {
            qDebug() << "CAN 控制器错误报警";
            handleDisconnect();
            ZCAN_ClearBuffer(deviceKey);
            emit signalsExceptionStatus();
            return;
        }
    }
    // 3：检查通道状态
    ZCAN_CHANNEL_STATUS canStatus;
    if (ZCAN_ReadChannelStatus(channelKey[m_txChannel], &canStatus) == STATUS_OK)
    {
        // regStatus & 0x20 = BusOff
        if (canStatus.regStatus & 0x20)
        {
            qDebug() << "CAN 控制器处于 BusOff 状态";
            handleDisconnect();
            ZCAN_ClearBuffer(deviceKey);
            emit signalsExceptionStatus();
            return;
        }
    }
    //每循环一次清除一次状态
    ZCAN_ClearBuffer(deviceKey);
}

// 处理断开连接
void USBCAN_FD_200U::handleDisconnect()
{
    // 停止所有发送
    closeAllSend();

    // 停止定时器
    m_timerLiftPDO->stop();
    m_timerTractionPDO->stop();
    m_timerStatus->stop();

    qDebug() << "任务已暂停!";

    // 尝试重新打开设备
    // openDevice_fd_200u();
}

