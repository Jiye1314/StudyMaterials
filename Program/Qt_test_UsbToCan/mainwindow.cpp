#include "mainwindow.h"
#include "ui_mainwindow.h"

bool g_thd_run = 1;
bool thread_value = 0;
bool open_timer = 0;

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
    qDebug() << "Start CAN1 state:" << retCloseDev;
    if (retCloseDev)
    {
        qDebug() << "关闭设备成功";
    }else{
        qDebug() << "关闭设备失败";
        return;
    }
}

//打开设备并读取设备信息
void MainWindow::OpenDevice()
{
    char path[20] = {0};

    //打开设备
    DEVICE_HANDLE retOpenDev = ZCAN_OpenDevice(ZCAN_USBCAN_2E_U, 0, 0);
    //保存设备句柄
    deviceKey = retOpenDev;

    qDebug() << "Start CAN1 state:" << retOpenDev;
    if (retOpenDev == INVALID_DEVICE_HANDLE) {
        qDebug() << "打开设备失败";
        return;
    }else{
        qDebug() << "打开设备成功";
        ui->bt_closeDev->setEnabled(true);
        ui->bt_send->setEnabled(true);
    }

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
    qDebug()<<"设备："<<retGetDevInf;
    qDebug()<<"硬件版本："<<zc_DevInfo.hw_Version;
    qDebug()<<"固件版本："<<zc_DevInfo.fw_Version;
    qDebug()<<"驱动程序版本："<<zc_DevInfo.dr_Version;
    qDebug()<<"接口库版本："<<zc_DevInfo.in_Version;
    qDebug()<<"板卡的序列号："<<zc_DevInfo.str_Serial_Num;
    qDebug()<<"硬件类型："<<zc_DevInfo.str_hw_Type;


    for (int i=0;i<2;i++)
    {
        //设置波特率
        sprintf(path,"%d/baud_rate",i);
        if(!ZCAN_SetValue(deviceKey,path,"1000000"))
        {
            qDebug()<<"设置波特率失败 "<<i;
            on_bt_closeDev_clicked();
            break;
        }else{
            qDebug()<<"设置波特率成功 "<<i;
        }


        //初始化CAN通道 0/1
        ZCAN_CHANNEL_INIT_CONFIG channelConfig;
        memset(&channelConfig, 0, sizeof(channelConfig));

        channelConfig.can_type = 0; // 0 - CAN，1 - CANFD
        channelConfig.can.mode = 0; // 0 - 正常模式，1 - 只听模式


        CHANNEL_HANDLE retChannelHandle[2];
        retChannelHandle[i] = ZCAN_InitCAN(deviceKey,i, &channelConfig);

        if (retChannelHandle[i] == INVALID_CHANNEL_HANDLE)
        {
            qDebug()<< "初始化通道失败 "<<i;
            on_bt_closeDev_clicked();
            return;;
        }else{
            qDebug()<< "初始化通道成功 "<<i;
        }
        //保存句柄
        channelKey[i] = retChannelHandle[i];


        // 使能通道终端电阻
        sprintf_s(path, "%d/initenal_resistance", i);
        if (!ZCAN_SetValue(deviceKey, path, "1"))
        {
            qDebug()<< "set 通道终端电阻 failed "<<i;
            on_bt_closeDev_clicked();
            break;
        }

        // 设置通道发送超时时间为 100ms
        sprintf_s(path, "%d/tx_timeout", i);
        if (!ZCAN_SetValue(deviceKey, path, "100"))
        {
            qDebug()<< "set 发送超时时间 failed "<<i;
            on_bt_closeDev_clicked();
            break;
        }

        // 仅对 0 通道设置滤波
        if (i == 0)
        {
            // 设置第一组滤波，只接收 ID 范围在 0x100-0x200 之间的标准帧
            ZCAN_SetValue(deviceKey, "0/filter_mode", "0"); // 标准帧
            ZCAN_SetValue(deviceKey, "0/filter_start", "0x100"); // 起始 ID
            ZCAN_SetValue(deviceKey, "0/filter_end", "0x200"); // 结束 ID
            // 设置第二组滤波，只接收 ID 范围在 0x1FFFF-0x2FFFF 之间的扩展帧
            ZCAN_SetValue(deviceKey, "0/filter_mode", "1"); // 扩展帧
            ZCAN_SetValue(deviceKey, "0/filter_start", "0x1FFFF"); // 起始 ID
            ZCAN_SetValue(deviceKey, "0/filter_end", "0x2FFFF"); // 结束 ID
            // 使能滤波
            ZCAN_SetValue(deviceKey, "0/filter_ack", "0");

            // 清除滤波,此处仅举例，何时调用用户自由决定
            // ZCAN_SetValue(device, "0/filter_clear", "0");
        }

        // 设置合并接收标志，启用合并发送，接收接口（只需设置 1 次）
        if (i == 0)
        {
            ZCAN_SetValue(deviceKey, "0/set_device_recv_merge", "1");
        }

        // 启动 CAN 通道
        if (!ZCAN_StartCAN(channelKey[i]))
        {
            qDebug()<<"启动 CAN 通道 failed "<<i;
            on_bt_closeDev_clicked();
            break;
        }else{
            qDebug()<<"启动 CAN 通道 successed "<<i;
        }

        // 启动 CAN 通道的接收线程
        // 启动线程
        canThread = QThread::create([=]() {
            thread_task(channelKey[i]);
        });

        thread_value = 1;

        thd_handle.append(canThread);
        canThread->start();

        // 转发，将 1，2 通道转发到 0 通道
        int ret = 1;
        ret &= ZCAN_SetValue(deviceKey, "1/redirect", "0 1");
        ret &= ZCAN_SetValue(deviceKey, "2/redirect", "0 1");
        if (0 == ret) {
            qDebug()<< "set 转发 failed!";
            on_bt_closeDev_clicked();
            break;
        }
    }
}

// 此函数仅用于构造示例 CAN 报文（官方文档）
void MainWindow::get_can_frame(ZCAN_Transmit_Data &can_data, canid_t id)
{
    memset(&can_data, 0, sizeof(can_data));
    can_data.frame.can_id = MAKE_CAN_ID(id, 0, 0, 0); // CAN ID + STD/EXT + DATA/RMT
    can_data.frame.can_dlc = 8; // CAN 数据长度 8
    can_data.transmit_type = 0; // 正常发送
    can_data.frame.__pad |= TX_ECHO_FLAG; // 发送回显
    for (int i = 0; i < 8; ++i)
    { // 填充 CAN 报文 DATA
        can_data.frame.data[i] = i;
    }
}

// 接收数据线程（官方文档）
void MainWindow::thread_task(CHANNEL_HANDLE channelKey)
{
    int nChnl = (unsigned int)channelKey & 0x000000FF;
    qDebug()<< "chnl: "<< nChnl << " thread run, handle:0x"<< channelKey;
    ZCAN_Receive_Data data[100] = {};
    while (g_thd_run)
    {
        int count = ZCAN_GetReceiveNum(channelKey, 0); // 获取 CAN 报文（参数 2：0 - CAN，1 - CANFD）数量
        while (g_thd_run && count > 0)
        {
            int rcount = ZCAN_Receive(channelKey, data, 100, 10);
            for (int i = 0; i < rcount; ++i)
            {
                {
                    qDebug()<< "CHNL: "<< nChnl << " recv can ID: 0x";
                    qDebug()<< data[i].frame.can_id;
                }
                count -= rcount;
            }
            QThread::msleep(100);
        }
        qDebug()<< "chnl: "<< nChnl << " thread exit";
    }
}

void MainWindow::sleepMs(int msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, &QEventLoop::quit);
    loop.exec();
}


void MainWindow::on_bt_send_clicked()
{

    if(!open_timer)
    {

        open_timer = 1;
        ui->bt_send->setText("关闭");

        ZCAN_AUTO_TRANSMIT_OBJ auto_can;
        memset(&auto_can, 0, sizeof(auto_can));
        auto_can.enable = 1; // 使能此索引，每条可单独设置
        auto_can.interval = 500; // 定时发送间隔 500ms
        auto_can.index = 0; // 定时列表索引 0
        get_can_frame(auto_can.obj, 0); // 构造 CAN 报文
        ZCAN_SetValue(deviceKey, "0/auto_send", (const char*)&auto_can); // 设置定时发送
        memset(&auto_can, 0, sizeof(auto_can));
        auto_can.enable = 1; // 使能此索引，每条可单独设置
        auto_can.interval = 1000; // 定时发送间隔 2000ms
        auto_can.index = 1; // 定时列表索引 1
        get_can_frame(auto_can.obj, 1); // 构造 CAN 报文
        ZCAN_SetValue(deviceKey, "0/auto_send", (const char*)&auto_can); // 设置定时发送

    }else{

        open_timer = 0;
        ui->bt_send->setText("开启定时发送");

        ZCAN_SetValue(deviceKey, "0/clear_auto_send", "0");
        // 通道 0 发送 10 帧报文
        ZCAN_Transmit_Data trans_data[10] = {};
        for (int i = 0; i < 10; ++i){
            get_can_frame(trans_data[i], i);
        }
        int send_count = ZCAN_Transmit(channelKey[0], trans_data, 10);
        qDebug()<< "send frame: "<< send_count;
    }

}

