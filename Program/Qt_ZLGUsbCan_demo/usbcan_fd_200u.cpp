#include "usbcan_fd_200u.h"

bool g_thd_run = 1;
bool thread_value = 0;
bool open_timer = 0;

USBCAN_FD_200U::USBCAN_FD_200U(QObject *parent) : QObject(parent)
{

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

//    //读取信息
//    ZCAN_DEVICE_INFO zc_DevInfo;
//    UINT retGetDevInf = ZCAN_GetDeviceInf(deviceKey,&zc_DevInfo);

//    if(retGetDevInf == STATUS_ERR)
//    {
//        qDebug()<<"读取设备信息失败";
//        return false;
//    }else{
//        qDebug()<<"读取设备信息成功";
//    }
//    qDebug()<<"硬件版本："<<zc_DevInfo.hw_Version;
//    qDebug()<<"固件版本："<<zc_DevInfo.fw_Version;


    for (int i=0;i<2;i++)
    {
        // 设置 CANFD 标准为 ISO
        sprintf_s(path, "%d/canfd_standard", i);
        if (0 == ZCAN_SetValue(deviceKey, path, "0")) {
            qDebug()<< "set canfd standard ok";
        }

        // 设置仲裁域波特率（CANFD 必需）
        sprintf(path, "%d/canfd_abit_baud_rate", i);
        if (!ZCAN_SetValue(deviceKey, path, "500000")) {
            qDebug() << "设置仲裁域波特率失败 " << i;
            closeDevice_fd_200u();
            break;
        } else {
            qDebug() << "设置仲裁域波特率成功 " << i;
        }

        // 设置数据域波特率（CANFD 必需）
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

        channelConfig.can_type = TYPE_CANFD;  // CANFD模式 TYPE_CANFD 或 1
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
            thread_taskFD_fd_200u(channelKey[i]);
        });
        thd_handle.append(t);
        t->start();
    }
    return true;
}

bool USBCAN_FD_200U::closeDevice_fd_200u()
{
    g_thd_run = 0;

    thread_value = 0;
    for (const auto &canThread: thd_handle)
    {
        canThread->quit();
        canThread->wait();
        delete canThread;
    }
    thd_handle.clear();

    UINT retCloseDev = ZCAN_CloseDevice(deviceKey);
    qDebug() << "关闭设备返回:" << retCloseDev;
    if (retCloseDev)
    {
        qDebug() << "关闭设备成功";
    }else{
        qDebug() << "关闭设备失败";
        return false;
    }
    return true;
}

bool USBCAN_FD_200U::timerSend_fd_200u()
{
    if(!open_timer)
    {
        open_timer = 1;
        //ui->bt_send->setText("关闭");

        //定时发送 CANFD
        ZCANFD_AUTO_TRANSMIT_OBJ auto_canfd;
        memset(&auto_canfd, 0, sizeof(auto_canfd));
        auto_canfd.index = 0;
        auto_canfd.enable = 1;
        auto_canfd.interval = 1000;
        get_canfd_frame_fd_200u(auto_canfd.obj, 0);
        ZCAN_SetValue(deviceKey, "0/auto_send_canfd", (const char*)&auto_canfd);

        memset(&auto_canfd, 0, sizeof(auto_canfd));
        auto_canfd.index = 1;
        auto_canfd.enable = 1;
        auto_canfd.interval = 2000;
        get_canfd_frame_fd_200u(auto_canfd.obj, 1);
        ZCAN_SetValue(deviceKey, "0/auto_send_canfd", (const char*)&auto_canfd);

        ZCAN_SetValue(deviceKey, "0/apply_auto_send", "0");
        qDebug() << "定时发送已开启";
    }
    else
    {
        open_timer = 0;
        //ui->bt_send->setText("开启定时发送");
        //关闭定时发送
        ZCAN_SetValue(deviceKey, "0/clear_auto_send", "0");

    }
    return open_timer;
}

//手动发送
void USBCAN_FD_200U::Send_fd_200u()
{
    //发送测试帧
    static int count = 1;
    ZCAN_TransmitFD_Data trans_datafd[10] = {};
    for (int i = 0; i < 10; ++i)
    {
        get_canfd_frame_fd_200u(trans_datafd[i], i);
    }
    int send_count = ZCAN_TransmitFD(channelKey[0], trans_datafd, 10);

    qDebug()<< "发送CANFD帧数: " << send_count;
    qDebug()<<"共发送："<<count++;
    qDebug()<<"当前时间："<<QDateTime::currentDateTime();

//    // 构造 10 帧 CAN 报文(0 通道发送)以及 10 帧 CANFD 报文（1 通道发送）
//    ZCANDataObj trans_data[20] = {};
//    for (int i = 0; i < 20; ++i)
//    {
//        int ch = i < 10 ? 0 : 1;
//        bool is_fd = i < 10 ? false : true;
//        get_can_canfd_frame(trans_data[i], ch, i + 0x100, is_fd);
//    }
//    int send_count = ZCAN_TransmitData(deviceKey, trans_data, 20);
//    qDebug()<< "send frame: "<< send_count;
}

// 构造CANFD示例报文
void USBCAN_FD_200U::get_canfd_frame_fd_200u(ZCAN_TransmitFD_Data &canfd_data, canid_t id)
{
    memset(&canfd_data, 0, sizeof(canfd_data));
    canfd_data.frame.can_id = MAKE_CAN_ID(id, 0, 0, 0);
    canfd_data.frame.len = 64;
    canfd_data.transmit_type = 0;
    canfd_data.frame.flags |= TX_ECHO_FLAG;
    for (int i = 0; i < 64; ++i) {
        canfd_data.frame.data[i] = i;
    }
}

//接收线程
void USBCAN_FD_200U::thread_taskFD_fd_200u(CHANNEL_HANDLE handle)
{
    qDebug()<< "接收线程启动 handle:"<< handle;
    ZCAN_ReceiveFD_Data fd_data[100] = {};
    static int thcount = 1;

    while (g_thd_run) {
        // 获取 CANFD 帧数量（type=1 表示 CANFD）
        int count = ZCAN_GetReceiveNum(handle, 1);

        if (count <= 0) {
            QThread::msleep(50);
            continue;
        }

        // 使用 ZCAN_ReceiveFD（通道句柄）
        int rcount = ZCAN_ReceiveFD(handle, fd_data, 100, 10);

        for (int i = 0; i < rcount; ++i)
        {
            qDebug() << "==================================================";
            qDebug() << "通道:" << ((unsigned int)handle & 0x000000FF);

            if (fd_data[i].frame.flags & 0x01)
            {
                qDebug() << "[自发自收]";
            } else {
                qDebug() << "[外部接收]";
            }

            qDebug() << "ID: 0x" << QString::number(fd_data[i].frame.can_id, 16);
            qDebug() << "长度:" << (int)fd_data[i].frame.len;

            QByteArray hex;
            for (int j = 0; j < fd_data[i].frame.len; j++)
            {
                hex.append(QString("%1 ").arg(fd_data[i].frame.data[j], 2, 16, QChar('0')));
            }
            qDebug() << "数据:" << hex;
            qDebug() << "共接收:" << thcount++ << "次";
            qDebug()<<"当前时间："<<QDateTime::currentDateTime();
            QThread::msleep(100);
        }
        QThread::msleep(100);
    }
    qDebug()<< "接收线程退出";
}

void USBCAN_FD_200U::sleepMs_fd_200u(int msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, &QEventLoop::quit);
    loop.exec();
}
