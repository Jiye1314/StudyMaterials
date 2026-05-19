#include "usbcan_2e_u.h"

bool g_thd_run = 1;
bool timer_send = false;

USBCAN_2E_U::USBCAN_2E_U(QObject *parent) : QObject(parent)
{

}

bool USBCAN_2E_U::openDevice()
{
    char path[20] = {0};


    DEVICE_HANDLE retOpenDev = ZCAN_OpenDevice(ZCAN_USBCAN_2E_U,0,0);
    if(retOpenDev == INVALID_DEVICE_HANDLE)
    {
        qDebug()<<"打开失败";
        closeDevice();
        return false;

    }else
    {
        qDebug()<<"设备打开成功";
        deviceKey = retOpenDev;
    }


    for(int i=0;i<2;i++)
    {
        sprintf(path,"%d/baud_rate",i);
        if(ZCAN_SetValue(deviceKey,path,"1000000"))
        {
            qDebug()<<"设置波特率成功";
        }else
        {
            qDebug()<<"波特率失败";
            closeDevice();
            break;
        }

        ZCAN_CHANNEL_INIT_CONFIG config;
        memset(&config,0,sizeof (config));
        config.can_type = 0;
        config.can.mode = 0;

        channelKey[i] = ZCAN_InitCAN(deviceKey,i,&config);

        if(channelKey[i] == INVALID_CHANNEL_HANDLE)
        {
            qDebug()<<"初始化通道失败";
            closeDevice();
            break;
        }

        if(!ZCAN_StartCAN(channelKey[i]))
        {
            qDebug()<<"启动can通道失败";
            closeDevice();
            break;
        }

        //启动接收线程
        QThread *t = QThread::create([=]() {
            thread_task(channelKey[i]);
        });
        thd_handle.append(t);
        t->start();
    }
    return true;
}

bool USBCAN_2E_U::closeDevice()
{
    for(int i=0;i<2;i++)
    {
        thd_handle[i]->quit();
        thd_handle[i]->wait();
        delete thd_handle[i];
    }
    thd_handle.clear();

    if(!ZCAN_CloseDevice(deviceKey))
    {
        qDebug()<<"关闭失败";
    }
    qDebug()<<"关闭成功";
    return true;
}

bool USBCAN_2E_U::timerSend()
{
    if(!timer_send)
    {
        timer_send = true;
        // 通道 0 定时发送 2 条 CAN 报文，ID 0 间隔 10ms，ID 1 间隔 100ms
        ZCAN_AUTO_TRANSMIT_OBJ auto_can;
        memset(&auto_can, 0, sizeof(auto_can));
        auto_can.enable = 1;             // 使能此索引，每条可单独设置
        auto_can.interval = 1000;       // 定时发送间隔 1s
        auto_can.index = 0;             // 定时列表索引 0
        get_can_frame(auto_can.obj, 0); // 构造 CAN 报文
        ZCAN_SetValue(deviceKey, "0/auto_send", (const char*)&auto_can); // 设置定时发送
        memset(&auto_can, 0, sizeof(auto_can));
        auto_can.enable = 1;             // 使能此索引，每条可单独设置
        auto_can.interval = 1500;        // 定时发送间隔 1.5s
        auto_can.index = 1;              // 定时列表索引 1
        get_can_frame(auto_can.obj, 1); // 构造 CAN 报文
        ZCAN_SetValue(deviceKey, "0/auto_send", (const char*)&auto_can); // 设置定时发送
    }
    else
    {
        timer_send = false;
        ZCAN_SetValue(deviceKey,"0/clear_auto_send","0");
    }

    return timer_send;

    //    // 5 秒后停止定时发送
    //    Sleep(1000);
    //    ZCAN_SetValue(device, "0/clear_auto_send", "0");
}

bool USBCAN_2E_U::send()
{
    // 通道 0 发送 10 帧报文
    ZCAN_Transmit_Data trans_data[10] = {};
    for (int i = 0; i < 10; ++i)
    {
        get_can_frame(trans_data[i], i);
    }
    int send_count = ZCAN_Transmit(channelKey[0], trans_data, 10);
    qDebug()<<"send 报文: "<< send_count;
    return true;
}

void USBCAN_2E_U::get_can_frame(ZCAN_Transmit_Data &can_data, canid_t id)
{
    memset(&can_data,0,sizeof (can_data));
    can_data.frame.can_id = id;     //CAN ID
    can_data.frame.can_dlc = 8;     //CAN数据长度 8
    can_data.transmit_type = 0;     //正常发送
    for(int i = 0;i<8;++i)          //填充CAN报文到 DATA
    {
        can_data.frame.data[i]=i;
    }
}

void USBCAN_2E_U::thread_task(CHANNEL_HANDLE handle)
{
    int nChnl = (unsigned int)handle & 0x000000FF;

    qDebug()<< "chnl: " << nChnl << " thread run, handle:0x" << handle;

    ZCAN_Receive_Data data[100] = {};
    while (g_thd_run)
    {
        int count = ZCAN_GetReceiveNum(deviceKey,0);        //获取CAN报文数量
        while(g_thd_run && count > 0)
        {
            int rcount = ZCAN_Receive(deviceKey,data,100,10);
            for(int i=0;i<rcount;i++)
            {
                qDebug()<<"CHNL:"<<nChnl<<"recv can ID:0x";
                qDebug()<<data[i].frame.can_id;
            }
            count -= count;
        }

        QThread::sleep(100);
    }
    qDebug()<<"chnl: "<<nChnl<<" thread exit";
}

