#include "mainwindow.h"
#include "ui_mainwindow.h"

bool g_thd_run = 1;
bool thread_value = 0;
bool open_timer = 0;

#define type ZCAN_USBCANFD_200U

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->bt_closeDev->setEnabled(false);
    ui->bt_send->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//打开设备/读取设备信息/设置波特率/初始化
void MainWindow::on_bt_getDeviceInf_clicked()
{
    OpenDevice();
}

//关闭设备
void MainWindow::on_bt_closeDev_clicked()
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
        return;
    }
    ui->bt_closeDev->setEnabled(false);
    ui->bt_send->setEnabled(false);
}

//打开设备并读取设备信息
void MainWindow::OpenDevice()
{
    char path[20] = {0};

    //打开设备
    DEVICE_HANDLE retOpenDev = ZCAN_OpenDevice(type, 0, 0);

    qDebug() << "打开设备返回:" << retOpenDev;
    if (retOpenDev == INVALID_DEVICE_HANDLE) {
        qDebug() << "打开设备失败";
        return;
    }else{
        qDebug() << "打开设备成功";
    }

    //保存设备句柄
    deviceKey = retOpenDev;

    //读取信息
    ZCAN_DEVICE_INFO zc_DevInfo;
    UINT retGetDevInf = ZCAN_GetDeviceInf(deviceKey,&zc_DevInfo);

    if(retGetDevInf == STATUS_ERR)
    {
        qDebug()<<"读取设备信息失败";
        return;
    }else{
        qDebug()<<"读取设备信息成功";
    }
    qDebug()<<"硬件版本："<<zc_DevInfo.hw_Version;
    qDebug()<<"固件版本："<<zc_DevInfo.fw_Version;


    for (int i=0;i<2;i++)
    {
        // 设置 CANFD 标准为 ISO
        sprintf_s(path, "%d/canfd_standard", i);
        if (0 == ZCAN_SetValue(deviceKey, path, "0")) {
            qDebug()<< "set canfd standard ok";
        }

        // 设置仲裁域波特率（CANFD 必需）
        sprintf(path, "%d/canfd_abit_baud_rate", i);
        if (ZCAN_SetValue(deviceKey, path, "500000") == STATUS_ERR) {
            qDebug() << "设置仲裁域波特率失败 " << i;
            on_bt_closeDev_clicked();
            break;
        } else {
            qDebug() << "设置仲裁域波特率成功 " << i;
        }

        // 设置数据域波特率（CANFD 必需）
        sprintf(path, "%d/canfd_dbit_baud_rate", i);
        if (ZCAN_SetValue(deviceKey, path, "500000") == STATUS_ERR) {
            qDebug() << "设置数据域波特率失败 " << i;
            on_bt_closeDev_clicked();
            break;
        } else {
            qDebug() << "设置数据域波特率成功 " << i;
        }

        sprintf(path, "%d/initenal_resistance", i);
        UINT retRes = ZCAN_SetValue(deviceKey, path, "1");
        if (retRes != STATUS_OK)
        {
            qDebug()<< "使能终端电阻失败 " << i << " （部分设备不支持软件控制，可忽略）";
        }

        //初始化CAN通道
        ZCAN_CHANNEL_INIT_CONFIG channelConfig;
        memset(&channelConfig, 0, sizeof(channelConfig));

        channelConfig.can_type = TYPE_CANFD;  // 正确的CANFD模式
        channelConfig.can.mode = 0;

        CHANNEL_HANDLE ch = ZCAN_InitCAN(deviceKey,i, &channelConfig);

        if (ch == INVALID_CHANNEL_HANDLE)
        {
            qDebug()<< "初始化通道失败 "<<i;
            on_bt_closeDev_clicked();
            return;
        }else{
            qDebug()<< "初始化通道成功 "<<i;
        }

        channelKey[i] = ch;

        // 设置发送超时
        sprintf_s(path, "%d/tx_timeout", i);
        ZCAN_SetValue(deviceKey, path, "100");

//        // 软件环回模式（自发自收，无需外部接线）
//        sprintf(path, "%d/mode", i);
//        ZCAN_SetValue(deviceKey, path, "1"); // 1 = 环回模式

        // 启动 CAN 通道
        if (!ZCAN_StartCAN(ch))
        {
            qDebug()<<"启动 CAN 通道失败 "<<i;
            on_bt_closeDev_clicked();
            break;
        }else{
            qDebug()<<"启动 CAN 通道成功 "<<i;
        }

        // 启动接收线程
        QThread *t = QThread::create([=]() {
            thread_taskFD(ch);
        });
        thd_handle.append(t);
        t->start();
    }

    ui->bt_closeDev->setEnabled(true);
    ui->bt_send->setEnabled(true);
}

// 构造CANFD示例报文
void MainWindow::get_canfd_frame(ZCAN_TransmitFD_Data &canfd_data, canid_t id)
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


void MainWindow::thread_taskFD(CHANNEL_HANDLE handle)
{
    qDebug()<< "接收线程启动 handle:"<< handle;
    ZCAN_ReceiveFD_Data fd_data[100] = {};

    while (g_thd_run) {
        // 获取 CANFD 帧数量（type=1 表示 CANFD）
        int count = ZCAN_GetReceiveNum(handle, 1);

        if (count <= 0) {
            QThread::msleep(5);
            continue;
        }

        // 使用 ZCAN_ReceiveFD（通道句柄版），正确用法
        int rcount = ZCAN_ReceiveFD(handle, fd_data, 100, 10);

        for (int i = 0; i < rcount; ++i) {
            qDebug() << "==================================================";
            qDebug() << "通道:" << ((unsigned int)handle & 0x000000FF);

            if (fd_data[i].frame.flags & 0x01) {
                qDebug() << "[自发自收]";
            } else {
                qDebug() << "[外部接收]";
            }

            qDebug() << "ID: 0x" << QString::number(fd_data[i].frame.can_id, 16);
            qDebug() << "长度:" << (int)fd_data[i].frame.len;

            QByteArray hex;
            for (int j = 0; j < fd_data[i].frame.len; j++) {
                hex.append(QString("%1 ").arg(fd_data[i].frame.data[j], 2, 16, QChar('0')));
            }
            qDebug() << "数据:" << hex;
        }
    }
    qDebug()<< "接收线程退出";
}

void MainWindow::sleepMs(int msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, &QEventLoop::quit);
    loop.exec();
}

//定时发送
void MainWindow::on_bt_send_clicked()
{
    if(!open_timer)
    {
        open_timer = 1;
        ui->bt_send->setText("关闭");

        //定时发送 CANFD
        ZCANFD_AUTO_TRANSMIT_OBJ auto_canfd;
        memset(&auto_canfd, 0, sizeof(auto_canfd));
        auto_canfd.index = 0;
        auto_canfd.enable = 1;
        auto_canfd.interval = 500;
        get_canfd_frame(auto_canfd.obj, 0);
        ZCAN_SetValue(deviceKey, "0/auto_send_canfd", (const char*)&auto_canfd);

        memset(&auto_canfd, 0, sizeof(auto_canfd));
        auto_canfd.index = 1;
        auto_canfd.enable = 1;
        auto_canfd.interval = 600;
        get_canfd_frame(auto_canfd.obj, 1);
        ZCAN_SetValue(deviceKey, "0/auto_send_canfd", (const char*)&auto_canfd);

        ZCAN_SetValue(deviceKey, "0/apply_auto_send", "0");
        qDebug() << "定时发送已开启";
    }
    else
    {
        open_timer = 0;
        ui->bt_send->setText("开启定时发送");
        ZCAN_SetValue(deviceKey, "0/clear_auto_send", "0");

        //发送测试帧
        ZCAN_TransmitFD_Data trans_datafd[10] = {};
        for (int i = 0; i < 10; ++i){
            get_canfd_frame(trans_datafd[i], i);
        }
        int send_count = ZCAN_TransmitFD(channelKey[0], trans_datafd, 10);
        qDebug()<< "发送CANFD帧数: " << send_count;
    }
}
