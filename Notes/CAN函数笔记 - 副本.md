[TOC]

## 3.2节 CAN函数接口定义

### 函数速查表

| 分类     | 函数                    | 用途                               |
| :------- | :---------------------- | :--------------------------------- |
| 设备管理 | ZCAN_OpenDevice         | 打开设备                           |
|          | ZCAN_CloseDevice        | 关闭设备                           |
|          | ZCAN_GetDeviceInf       | 获取设备信息                       |
|          | ZCAN_IsDeviceOnLine     | 检测设备是否在线                   |
| CAN通道  | ZCAN_InitCAN            | 初始化CAN                          |
|          | ZCAN_StartCAN           | 启动CAN通道                        |
|          | ZCAN_ResetCAN           | 复位CAN通道                        |
|          | ZCAN_ClearBuffer        | 清除接收缓冲区                     |
|          | ZCAN_ReadChannelErrInfo | 读取通道错误信息                   |
|          | ZCAN_ReadChannelStatus  | 读取通道状态（不支持）             |
| 发送     | ZCAN_Transmit           | 发送CAN报文                        |
|          | ZCAN_TransmitFD         | 发送CANFD报文                      |
|          | ZCAN_TransmitData       | 发送CAN/CANFD报文（合并接收设备）  |
| 接收     | ZCAN_GetReceiveNum      | 获取缓冲区报文数目                 |
|          | ZCAN_Receive            | 接收CAN报文                        |
|          | ZCAN_ReceiveFD          | 接收CANFD报文                      |
|          | ZCAN_ReceiveData        | 合并接收（CAN/CANFD/LIN/GPS/错误） |
| 属性操作 | ZCAN_SetValue           | 设置设备属性                       |
|          | ZCAN_GetValue           | 获取设备属性                       |
|          | GetIProperty            | 获取属性配置接口                   |
|          | ReleaseIProperty        | 释放属性接口                       |
| 云服务   | ZCLOUD_SetServerInfo    | 设置云服务器连接信息               |
|          | ZCLOUD_ConnectServer    | 连接云服务器                       |
|          | ZCLOUD_IsConnected      | 判断是否已连接云服务器             |
|          | ZCLOUD_DisconnectServer | 断开云服务器连接                   |
|          | ZCLOUD_GetUserData      | 获取用户数据                       |
|          | ZCLOUD_ReceiveGPS       | 接收云设备GPS数据                  |
| LIN      | ZCAN_InitLIN            | 初始化LIN                          |
|          | ZCAN_StartLIN           | 启动LIN通道                        |
|          | ZCAN_ResetLIN           | 复位LIN通道                        |
|          | ZCAN_TransmitLIN        | 发送LIN消息                        |
|          | ZCAN_GetLINReceiveNum   | 获取LIN消息数量                    |
|          | ZCAN_ReceiveLIN         | 接收LIN消息                        |
|          | ZCAN_SetLINSlaveMsg     | 设置从站响应（已弃用）             |
|          | ZCAN_ClearLINSlaveMsg   | 清除从站响应（已弃用）             |
|          | ZCAN_SetLINSubscribe    | 设置LIN订阅                        |
|          | ZCAN_SetLINPublish      | 设置LIN发布                        |
| UDS      | ZCAN_UDS_Request        | 发送UDS请求                        |
|          | ZCAN_UDS_Control        | UDS诊断控制                        |
|          | ZCAN_UDS_RequestEX      | UDS诊断请求扩展                    |
|          | ZCAN_UDS_ControlEX      | UDS诊断控制扩展                    |

### 设备相关操作

#### ZCAN_OpenDevice — 打开设备

该函数用于打开设备。一个设备只能被打开一次。

```c++
DEVICE_HANDLE ZCAN_OpenDevice(UINT device_type, UINT device_index, UINT reserved);
```

参数

```c++
device_type
设备类型，详见头文件 zlgcan.h 中的宏定义。
    
device_index
设备索引号，比如当只有一个 USBCANFD-200U 时，索引号为 0，这时再插入一个USBCANFD-200U，那么后面插入的这个设备索引号就是 1，以此类推。
    
reserved
仅作保留。
```

返回值

```c++
为 INVALID_DEVICE_HANDLE 表示操作失败，否则表示操作成功，返回设备句柄值，请保存该句柄值，往后的操作需要使用。
```

#### ZCAN_CloseDevice — 关闭设备

该函数用于关闭设备，关闭设备和打开设备一一对应。

```c++
UINT ZCAN_CloseDevice(DEVICE_HANDLE device_handle);
```

参数

```c++
device_handle
需要关闭的设备的句柄值，即 ZCAN_OpenDevice 成功返回的值。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

#### ZCAN_GetDeviceInf — 获取设备信息

该函数用于获取设备信息。

```c++
UINT ZCAN_GetDeviceInf(DEVICE_HANDLE device_handle, ZCAN_DEVICE_INFO* pInfo);
```

参数

```c++
device_handle
设备句柄值。

pInfo
设备信息结构体，详见 ZCAN_DEVICE_INFO 结构说明。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

#### ZCAN_IsDeviceOnLine — 检测设备是否在线

该函数用于检测设备是否在线，仅支持 USB 系列设备。

```c++
UINT ZCAN_IsDeviceOnLine(DEVICE_HANDLE device_handle);
```

参数

```c++
device_handle
设备句柄值
```

返回值

```c++
设备在线=STATUS_ONLINE，不在线=STATUS_OFFLINE。
```

### CAN通道相关操作

#### ZCAN_InitCAN — 初始化 CAN

该函数用于初始化 CAN。

```c++
CHANNEL_HANDLE ZCAN_InitCAN(DEVICE_HANDLE device_handle, UINT can_index,ZCAN_CHANNEL_INIT_CONFIG* pInitConfig);
```

参数

```c++
device_handle
设备句柄值。
can_index
通道索引号，通道 0 的索引号为 0，通道 1 的索引号为 1，以此类推。
pInitConfig
初始化结构，详见 ZCAN_CHANNEL_INIT_CONFIG 结构说明。
```

返回值

```c++
为 INVALID_CHANNEL_HANDLE 表示操作失败，否则表示操作成功，返回通道句柄值，请保存该句柄值，往后的操作需要使用。
```

#### ZCAN_StartCAN — 启动 CAN 通道

该函数用于启动 CAN 通道。

```c++
UINT ZCAN_StartCAN(CHANNEL_HANDLE channel_handle);
```

参数

```c++
channel_handle
通道句柄值。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

#### ZCAN_ResetCAN — 复位 CAN 通道

该函数用于复位 CAN 通道，可通过 ZCAN_StartCAN 恢复。

```c++
UINT ZCAN_ResetCAN(CHANNEL_HANDLE channel_handle);
```

参数

```c++
channel_handle
通道句柄值。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

#### ZCAN_ClearBuffer — 清除库接收缓冲区

该函数用于清除库接收缓冲区。

```c++
UINT ZCAN_ClearBuffer(CHANNEL_HANDLE channel_handle)
```

参数

```c++
channel_handle
通道句柄值。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

#### ZCAN_ReadChannelErrInfo — 读取通道的错误信息

该函数用于读取通道的错误信息。

```c++
UINT ZCAN_ReadChannelErrInfo(CHANNEL_HANDLE channel_handle, ZCAN_CHANNEL_ERROR_INFO *pErrInfo);
```

参数

```c++
channel_handle
通道句柄值。
pErrInfo
错误信息结构，详见 ZCAN_CHANNEL_ERROR_INFO 结构说明。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

#### ZCAN_ReadChannelStatus — 读取通道的状态信息

该函数用于读取通道的状态信息。目前暂时没有设备支持使用此接口获取通道的状态信息，后续接口可能会被废弃。

```c++
UINT ZCAN_ReadChannelStatus(CHANNEL_HANDLE channel_handle, ZCAN_CHANNEL_STATUS *pCANStatus);
```

参数

```c++
channel_handle
通道句柄值。
pCANStatus
状态信息结构，详见 ZCAN_CHANNEL_STATUS 结构说明。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

#### ZCAN_Transmit — 发送 CAN 报文

该函数用于发送 CAN 报文。

```c++
UINT ZCAN_Transmit(CHANNEL_HANDLE channel_handle,ZCAN_Transmit_Data* pTransmit, UINT len);
```

参数

```c++
channel_handle
通道句柄值。
pTransmit
结构体 ZCAN_Transmit_Data 数组的首指针。
len
报文数目
```

返回值

```c++
返回实际发送成功的报文数目
```

#### ZCAN_TransmitFD — 发送 CANFD 报文

该函数用于发送 CANFD 报文。

```c++
UINT ZCAN_TransmitFD(CHANNEL_HANDLE channel_handle, ZCAN_TransmitFD_Data* pTransmit, UINT len);
```

参数

```c++
channel_handle
通道句柄值。
pTransmit
结构体 ZCAN_TransmitFD_Data 数组的首指针。
len
报文数目
```

返回值

```c++
返回实际发送成功的报文数目。
```

#### ZCAN_TransmitData — 发送 CAN/CANFD 报文

该函数用于发送 CAN/CANFD 报文。

```c++
UINT ZCAN_TransmitData(DEVICE_HANDLE device_handle, ZCANDataObj* pTransmit, UINT len);
```

参数

```c++
device_handle
设备句柄值。
pTransmit
结构体 ZCANDataObj 数组的首指针。
len
报文数目
```

返回值

```c++
返回实际发送成功的报文数目。
```

注：只有支持合并接收的设备才可以使用此接口发送数据，支持合并接收功能的设备调用发送接口发送数据时，并不要求设备开启合并接收功能。支持合并接收的设备列表如表 4.2 所示。

#### ZCAN_GetReceiveNum — 获取缓冲区报文数目

获取缓冲区中 CAN，CANFD 或者合并接收报文数目。

```c++
UINT ZCAN_GetReceiveNum(CHANNEL_HANDLE channel_handle, BYTE type);
```

参数

```c++
channel_handle
通道句柄值。
type
获取 CAN，CANFD 或者合并接收报文，0=CAN，1=CANFD，2=合并接收。
```

详细说明：
- 未开启合并接收时，channel_handle 使用要获取数据的通道句柄，type 表示要获取的数据类型(CAN 或 CANFD)
- 支持合并接收的设备开启合并接收时，channel_handle 可使用任意通道的句柄，type 使用值 2 表示获取合并接收帧数量
- 合并接收的数据可以通过调用接口 ZCAN_ReceiveData 获取
- 支持合并接收的设备列表如表 4.2 所示

返回值

```c++
返回报文数目。
```

#### ZCAN_Receive — 接收 CAN 报文

该函数用于接收 CAN 报文，建议使用 ZCAN_GetReceiveNum 确保缓冲区有数据再使用。

```c++
UINT ZCAN_Receive(CHANNEL_HANDLE channel_handle, ZCAN_Receive_Data* pReceive, UINT len, INT wait_time = -1);
```

参数

```c++
channel_handle
通道句柄值。
pReceive
结构体 ZCAN_Receive_Data 数组的首指针。
len
数组长度（本次接收的最大报文数目，实际返回值小于等于这个值）。
wait_time
缓冲区无数据，函数阻塞等待时间，单位毫秒。若为-1 则表示无超时，一直等待，默认值为-1。
```

返回值

```c++
返回实际接收的报文数目。
```

注：PCIECANFD-100U、PCIECANFD-400U、MiniPCIeCANFD、M.2CANFD 等设备不支持使用 ZCAN_Receive 接口接收 CAN 数据，只能使用 ZCAN_ReceiveData 接口接收数据。

#### ZCAN_ReceiveFD — 接收 CANFD 报文

该函数用于接收 CANFD 数据，建议使用 ZCAN_GetReceiveNum 确保缓冲区有数据再使用。

```c++
UINT ZCAN_ReceiveFD(CHANNEL_HANDLE channel_handle, ZCAN_ReceiveFD_Data* pReceive, UINT len, INT wait_time = -1);
```

参数

```c++
channel_handle
通道句柄值。
pReceive
结构体 ZCAN_ReceiveFD_Data 数组的首指针。
len
数组长度（本次接收的最大报文数目，实际返回值小于等于这个值）。
wait_time
缓冲区无数据，函数阻塞等待时间，单位毫秒。若为-1 则表示无超时，一直等待，默认值为-1。
```

返回值

```c++
返回实际接收的报文数目。
```

注：PCIECANFD-100U、PCIECANFD-400U、MiniPCIeCANFD、M.2CANFD 等设备不支持使用 ZCAN_ReceiveFD 接口接收 CANFD 数据，只能使用 ZCAN_ReceiveData 接口接收数据。

#### ZCAN_ReceiveData — 合并接收

该函数用于接收 CAN、CANFD、LIN、GPS、错误数据等各种类型的数据，即合并接收功能。建议使用 ZCAN_GetReceiveNum 接口使用合并接收参数获取缓冲区合并接收帧数量后确保缓冲区有数据再调用接口获取数据。

```c++
UINT ZCAN_ReceiveData(DEVICE_HANDLE device_handle, ZCANDataObj* pReceive, UINT len, INT wait_time = -1);
```

参数

```c++
device_handle
设备句柄值。
pReceive
结构体 ZCANDataObj 数组的首指针。
len
数组长度（本次接收的最大报文数目，实际返回值小于等于这个值）。
wait_time
缓冲区无数据，函数阻塞等待时间，单位毫秒。若为-1 则表示无超时，一直等待，默认值为-1。
```

返回值

```c++
返回实际接收的报文数目。
```

注：ZCAN_ReceiveData 接口只有在设备支持合并接收功能并开启合并接收功能后才可以正常的接收到各种数据，设备不支持合并接收功能或者设备支持合并接收但是未开启合并接收时，请使用 ZCAN_Receive/ZCAN_ReceiveFD 等接口获取设备数据。支持合并接收的设备列表如表 4.2 所示。

---

### 设备属性操作

#### ZCAN_SetValue — 设置设备属性

该函数设置设备属性。使用方法可以参考 IProperty 属性的 SetValue 函数，详见手册3.3小节。

```c++
UINT ZCAN_SetValue(DEVICE_HANDLE device_handle, const char* path, const void* value);
```

参数

```c++
device_handle
设备句柄值。
path
设备属性路径。
value
要设置的属性值。
```

返回值

```c++
STATUS_OK 表示设置成功，STATUS_ERR 表示设置失败。
```

| 配置功能               | path 写法                    | value 示例    | 说明                                                    |
| ---------------------- | --------------------------- | ------------- | ------------------------------------------------------- |
| 设置 CAN n 波特率      | `n/baud_rate`               | `"250000"`     | 通道 n 的波特率                                         |
| 自定义波特率           | `n/baud_rate_custom`        | `"125000"`     | 通道 n 的自定义波特率                                   |
| 终端电阻               | `n/internal_resistance`      | `"0"`          | 0 = 关闭，1 = 开启                                      |
| 环回模式（自测用）     | `n/mode`                    | `"1"`          | 1 = 环回模式，自发自收                                   |
| 过滤模式               | `n/filter_mode`             | `"0"`          | 0 = 接收所有，1 = 只接收过滤 ID 匹配的帧                  |
| 设置滤波 ID（标准帧）  | `n/filter_std_id`            | `"0x123"`      | 只接收 ID=0x123 的标准帧                                |
| 滤波掩码（标准帧）     | `n/filter_std_mask`          | `"0x7FF"`      | 掩码中为1的位必须匹配，0表示不关心；0x7FF=11位全匹配     |
| 设置滤波 ID（扩展帧）  | `n/filter_ext_id`            | `"0x123"`      | 只接收 ID=0x123 的扩展帧                                |
| 滤波掩码（扩展帧）     | `n/filter_ext_mask`          | `"0x1FFFFFFF"` | 掩码中为1的位必须匹配，0表示不关心；0x1FFFFFFF=29位全匹配 |
| 定时发送（CAN报文） | `n/auto_send` | `"(const char*)&transmitObj"` | (const char*)&报文 |
| 定时发送（CANFD报文） | `n/auto_send_canfd` | `"(const char*)&transmitObj"` | (const char*)&报文 |
| 使能定时发送 | `n/apply_auto_send` | "0" | 0 = 开启，1 = 关闭 |
| 暂停定时发送 | `n/clear_auto_send` | "0" | 0 = 清空定时发送 |
| 自动重发（错误帧重发） | `n/auto_retry`              | `"1"`          | 1 = 开启，0 = 关闭                                      |
| 发送超时时间           | `n/send_timeout`            | `"1000"`       | 单位 ms，超时重发                                       |
| 接收缓存大小           | `n/rx_buf_size`             | `"1024"`       | 接收队列长度                                            |
| 发送缓存大小           | `n/tx_buf_size`             | `"1024"`       | 发送队列长度                                            |
| **CANFD 仲裁段波特率** | `n/canfd_abit_baud_rate`    | `"2000000"`    | CANFD 设备的仲裁段波特率（bps）                          |
| **CANFD 数据段波特率** | `n/canfd_dbit_baud_rate`    | `"5000000"`    | CANFD 设备的数据段波特率（bps）                          |
| **CANFD 采样点**       | `n/canfd_sample_point`       | `"80"`         | 采样点百分比（0~100），默认80                           |
| **CANFD TDC**         | `n/tdc`                     | `"1"`          | 收发器延迟补偿：0=关闭，1=开启                           |

注：ZCAN_SetValue 函数可以通过设备句柄，直接设置设备属性。旧接口要达到同样的目的，要先通过 GetIProperty 接口获取设备属性 IProperty，后通过 IProperty 的成员 SetValue 函数设置设备属性，属性设置完毕后还需要使用 ReleaseIProperty 释放对应的 IProperty。ZCAN_SetValue 可以简化属性设置的步骤，方便用户使用。

#### ZCAN_GetValue — 获取设备属性

该函数获取设备属性。使用方法可以参考 IProperty 属性的 GetValue 函数，详见手册3.3小节。

```c++
const void* ZCAN_GetValue(DEVICE_HANDLE device_handle, const char* path);
```

参数

```c++
device_handle
设备句柄值。
path
设备属性路径。
```

返回值

```c++
返回的指针值非空表示操作成功，为空(NULL)则表示操作失败。
```

注：ZCAN_GetValue 函数可以通过设备句柄，直接获取设备属性。旧接口要达到同样的目的，要先通过 GetIProperty 接口获取设备属性 IProperty，后通过 IProperty 的成员 GetValue 函数获取设备属性，属性获取完毕后还需要使用 ReleaseIProperty 释放对应的 IProperty。ZCAN_GetValue 可以简化属性获取的步骤，方便用户使用。

#### GetIProperty — 获取属性配置接口

```c++
IProperty* GetIProperty(DEVICE_HANDLE device_handle);
```

参数

```c++
device_handle
设备句柄值。
```

返回值

```c++
返回属性配置接口指针，详见 IProperty 结构说明，空则表示操作失败。
```

#### ReleaseIProperty — 释放属性接口

释放属性接口，与 GetIProperty 结对使用。

```c++
UINT ReleaseIProperty(IProperty * pIProperty);
```

参数

```c++
pIProperty
GetIProperty 的返回值。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

---

### 云服务相关函数

#### ZCLOUD_SetServerInfo — 设置云服务器连接信息

```c++
void ZCLOUD_SetServerInfo(const char* httpSvr, unsigned short httpPort, const char* mqttSvr, unsigned short mqttPort);
```

参数

```c++
httpSvr
用户认证服务器地址，IP 地址或域名。
httpPort
用户认证服务器端口号。
mqttSvr
数据服务器地址，IP 地址或域名，一般与认证服务器相同。
mqttPort
数据服务器端口号。
```

#### ZCLOUD_ConnectServer — 连接云服务器

该函数用于连接云服务器，会先登录认证服务器，然后连接到数据服务器。

```c++
UINT ZCLOUD_ConnectServer(const char* username, const char* password);
```

参数

```c++
username
用户名。
password
密码。
```

返回值

```c++
0：成功，1：失败，2：认证服务器连接错误，3：用户信息验证错误，4：数据服务器连接错误。
```

#### ZCLOUD_IsConnected — 判断是否已连接云服务器

```c++
bool ZCLOUD_IsConnected();
```

返回值

```c++
true：已连接，false：未连接。
```

#### ZCLOUD_DisconnectServer — 断开云服务器连接

```c++
UINT ZCLOUD_DisconnectServer()
```

返回值

```c++
0：成功，1：失败。
```

#### ZCLOUD_GetUserData — 获取用户数据

获取用户数据，包括用户基本信息和所拥有设备信息。

```c++
const ZCLOUD_USER_DATA* ZCLOUD_GetUserData();
```

返回值

```c++
用户数据结构指针。
```

#### ZCLOUD_ReceiveGPS — 接收云设备 GPS 数据

```c++
UINT ZCLOUD_ReceiveGPS(DEVICE_HANDLE device_handle, ZCLOUD_GPS_FRAME* pReceive, UINT len, int wait_time = -1);
```

参数

```c++
device_handle
设备句柄值。
pReceive
结构体 ZCLOUD_GPS_FRAME 数组的首指针。
len
数组长度（本次接收的最大报文数目，实际返回值小于等于这个值）。
wait_time
缓冲区无数据，函数阻塞等待时间，单位毫秒，若为-1 则表示无超时，一直等待，默认值为-1。
```

返回值

```c++
返回实际接收的报文数目。
```

---

### LIN 相关函数

#### ZCAN_InitLIN — 初始化 LIN

该函数用于对 LIN 进行初始化，指定设备工作模式，采用经典校验方式还是增强校验等参数，如果是主站模式，需要指定 LIN 工作的波特率。

```c++
CHANNEL_HANDLE ZCAN_InitLIN(DEVICE_HANDLE device_handle, UINT can_index, PZCAN_LIN_INIT_CONFIG pLINInitConfig);
```

参数

```c++
device_handle
设备句柄值。
can_index
通道索引号，通道 0 的索引号为 0，通道 1 的索引号为 1，以此类推。
pLINInitConfig
初始化结构，详见 ZCAN_LIN_INIT_CONFIG 结构说明。
```

返回值

```c++
为 INVALID_CHANNEL_HANDLE 表示操作失败，否则表示操作成功，返回通道句柄值，请保存该句柄值，往后的操作需要使用。
```

#### ZCAN_StartLIN — 启动 LIN 通道

```c++
UINT ZCAN_StartLIN(CHANNEL_HANDLE channel_handle);
```

参数

```c++
channel_handle
通道句柄值。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

#### ZCAN_ResetLIN — 复位 LIN 通道

该函数用于复位对应的 LIN 通道，即停止此通道的数据发送和接收。复位之后如果需要继续接收或者发送数据，需要重新调用 ZCAN_StartLIN 来启动 LIN 通道。

```c++
UINT ZCAN_ResetLIN(CHANNEL_HANDLE channel_handle);
```

参数

```c++
channel_handle
通道句柄值。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

#### ZCAN_TransmitLIN — 发送 LIN 消息

该函数用来控制 LIN 发送 LIN 消息，只有 LIN 处于主站模式下才可以使用此函数进行数据发送。

```c++
ULONG ZCAN_TransmitLIN(CHANNEL_HANDLE channel_handle, PZCAN_LIN_MSG pSend, ULONG Len);
```

参数

```c++
channel_handle
通道句柄值。
pSend
结构体 ZCAN_LIN_MSG 数组的首指针。
Len
报文数目
```

返回值

```c++
返回实际发送成功的报文数目。
```

#### ZCAN_GetLINReceiveNum — 获取 LIN 消息数量

该函数用于获取指定通道已经接收到的 LIN 消息数量。

```c++
ULONG ZCAN_GetLINReceiveNum(CHANNEL_HANDLE channel_handle);
```

参数

```c++
channel_handle
通道句柄值。
```

返回值

```c++
返回报文数目。
```

#### ZCAN_ReceiveLIN — 接收 LIN 消息

该函数用来接收 LIN 消息，不论 LIN 处于主站还是从站模式，都可以使用该函数获取总线上的数据信息。

```c++
ULONG ZCAN_ReceiveLIN(CHANNEL_HANDLE channel_handle, PZCAN_LIN_MSG pReceive, ULONG Len, int WaitTime);
```

参数

```c++
channel_handle
通道句柄值。
pReceive
结构体 ZCAN_LIN_MSG 数组的首指针。
Len
数组长度（本次接收的最大报文数目，实际返回值小于等于这个值）。
WaitTime
缓冲区无数据，函数阻塞等待时间，单位毫秒。若为-1 则表示无超时，一直等待，默认值为-1。
```

返回值

```c++
返回实际接收的报文数目。
```

#### ZCAN_SetLINSlaveMsg — 设置 LIN 从站响应（已弃用）

该函数用来设置 LIN 作为从站时候的响应信息，设置响应信息后，从站收到对应 ID 的请求时候会将预定义的数据发送出去作为响应。

```c++
UINT ZCAN_SetLINSlaveMsg(CHANNEL_HANDLE channel_handle, PZCAN_LIN_MSG pSend, UINT nMsgCount);
```

参数

```c++
channel_handle
通道句柄值。
pSend
结构体 ZCAN_LIN_MSG 数组的首指针。
nMsgCount
数组长度。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

#### ZCAN_ClearLINSlaveMsg — 清除 LIN 从站响应（已弃用）

该函数用来清除 LIN 作为从站时候的响应信息，设置响应信息后，从站收到对应 ID 的请求时候会将预定义的数据发送出去作为响应，如果需要控制从站不再响应对应的 ID，需要调用此函数清除对特定 ID 的响应信息，清除后，从站不会在对此 ID 进行响应。

```c++
UINT ZCAN_ClearLINSlaveMsg(CHANNEL_HANDLE channel_handle, BYTE* pLINID, UINT nIDCount);
```

参数

```c++
channel_handle
通道句柄值。
pLINID
LIN ID 数组的首指针。
nIDCount
数组长度。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

#### ZCAN_SetLINSubscribe — 设置 LIN 订阅数据

该函数用来设置 LIN 订阅数据，设置订阅后，此时根据设置 ID 的报文长度 Length 接收数据。（注：主站跟从站可进行数据订阅）

```c++
UINT ZCAN_SetLINSubscribe(CHANNEL_HANDLE channel_handle, PZCAN_LIN_SUBSCIBE_CFG pSend, UINT nSubscribeCount);
```

参数

```c++
channel_handle
通道句柄值。
pSend
结构体 ZCAN_LIN_SUBSCIBE_CFG 数组的首指针。
nSubscribeCount
数组长度。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

#### ZCAN_SetLINPublish — 设置 LIN 发布数据

该函数用来设置 LIN 作为从机任务时候的发布数据，设置发布数据后，从机任务收到对应 ID 的请求时候会将预定义的数据发送出去作为响应。（注：主站跟从站都有从机任务）

```c++
UINT ZCAN_SetLINPublish(CHANNEL_HANDLE channel_handle, PZCAN_LIN_PUBLISH_CFG pSend, UINT nPublishCount);
```

参数

```c++
channel_handle
通道句柄值。
pSend
结构体 ZCAN_LIN_PUBLISH_CFG 数组的首指针。
nPublishCount
数组长度。
```

返回值

```c++
STATUS_OK 表示操作成功，STATUS_ERR 表示操作失败。
```

---

### UDS 诊断相关函数

#### ZCAN_UDS_Request — 发送 UDS 请求并接收响应

该函数用来发送 UDS 请求并接收 UDS 响应。

```c++
ZCAN_RET_STATUS ZCAN_UDS_Request(DEVICE_HANDLE device_handle, const ZCAN_UDS_REQUEST* req, ZCAN_UDS_RESPONSE* resp, BYTE* dataBuf, UINT dataBufSize);
```

参数

```c++
device_handle
设备句柄值。
req
请求信息
resp
响应信息，可为 nullptr，表示不关心响应数据
dataBuf
响应数据缓存区，存放积极响应的诊断数据(不包含 SID)，实际长度为 resp.positive.data_len
dataBufSize
响应数据缓存区总大小，如果小于响应诊断数据长度，返回 STATUS_BUFFER_TOO_SMALL
```

返回值

```c++
执行结果状态。
```

#### ZCAN_UDS_Control — UDS 诊断控制

该函数用来进行 UDS 诊断控制，如停止正在执行的 UDS 请求。

```c++
ZCAN_RET_STATUS ZCAN_UDS_Control(DEVICE_HANDLE device_handle, const ZCAN_UDS_CTRL_REQ *ctrl, ZCAN_UDS_CTRL_RESP* resp);
```

参数

```c++
device_handle
设备句柄值。
ctrl
控制请求信息
resp
响应信息，可为 nullptr，表示不关心响应数据
```

返回值

```c++
执行结果状态。
```

#### ZCAN_UDS_RequestEX — UDS 诊断请求扩展

该函数用来进行 UDS 诊断请求并接收 UDS 响应。

```c++
ZCAN_RET_STATUS ZCAN_UDS_RequestEX(DEVICE_HANDLE device_handle, const ZCANUdsRequestDataObj* requestData, ZCAN_UDS_RESPONSE* resp, BYTE* dataBuf, UINT dataBufSize);
```

参数

```c++
device_handle
设备句柄值。
requestData
请求信息
resp
响应信息，可为 nullptr，表示不关心响应数据
dataBuf
响应数据缓存区，存放积极响应的诊断数据(不包含 SID)，实际长度为 resp.positive.data_len
dataBufSize
响应数据缓存区总大小，如果小于响应诊断数据长度，返回 STATUS_BUFFER_TOO_SMALL
```

#### ZCAN_UDS_ControlEX — UDS 诊断控制扩展

该函数用来进行 UDS 诊断控制，如停止正在执行的 UDS 请求。

```c++
ZCAN_RET_STATUS ZCAN_UDS_ControlEX(DEVICE_HANDLE device_handle, ZCAN_UDS_DATA_DEF dataType, const ZCAN_UDS_CTRL_REQ *ctrl, ZCAN_UDS_CTRL_RESP* resp);
```

参数

```c++
device_handle
设备句柄值。
dataType
数据类型（1=CAN/CANFD UDS, 2=LIN UDS, 3=DOIP UDS）
ctrl
控制请求信息
resp
响应信息，可为 nullptr，表示不关心响应数据
```

返回值

```c++
执行结果状态。
```

---



## 3.1节 数据结构定义

### 设备配置相关结构体

#### ZCAN_DEVICE_INFO

​	结构体详情见程序清单 3.1，包含设备的一些基本信息，在函数 ZCAN_GetDeviceInf 中被填充。

程序清单 3.1 ZCAN_DEVICE_INFO 结构体成员

```c++
typedef struct tagZCAN_DEVICE_INFO {
     USHORT hw_Version;
     USHORT fw_Version;
     USHORT dr_Version;
     USHORT in_Version;
     USHORT irq_Num;
     BYTE can_Num;
     UCHAR str_Serial_Num[20];
     UCHAR str_hw_Type[40];
     USHORT reserved[4];
}ZCAN_DEVICE_INFO;
```

成员

```c++
hw_Version
硬件版本号，16 进制，比如 0x0100 表示 V1.00。
fw_Version
固件版本号，16 进制。
dr_Version
驱动程序版本号，16 进制。
in_Version
接口库版本号，16 进制。
irq_Num
板卡所使用的中断号。
can_Num
表示有几路通道。
str_Serial_Num
此板卡的序列号
str_hw_Type
硬件类型，比如” USBCAN V1.00”（注意：包括字符串结束符’\0’）。
reserved
仅作保留，不设置。
```

#### ZCAN_CHANNEL_INIT_CONFIG

​	结构体详情见程序清单 3.2，定义了初始化配置的参数，调用 ZCAN_InitCAN 之前，要先初始化该结构体。

程序清单 3.2 ZCAN_CHANNEL_INIT_CONFIG 结构体成员

```c++
ef struct tagZCAN_CHANNEL_INIT_CONFIG {
     UINT can_type; // 0:can 1:canfd
     union
     {
         struct
         {
             UINT acc_code;
             UINT acc_mask;
             UINT reserved;
             BYTE filter;
             BYTE timing0;
             BYTE timing1;
             BYTE mode;
         }can;
         struct
         {
             UINT acc_code;
             UINT acc_mask;
             UINT abit_timing;
             UINT dbit_timing;
             UINT brp;
             BYTE filter;
             BYTE mode;
             USHORT pad;
             UINT reserved;
         }canfd;
     };
}ZCAN_CHANNEL_INIT_CONFIG;
```

成员

```c++
can_type
设备类型， 0 表示 CAN 设备，1 表示 CANFD 设备。
1、CAN 设备
    acc_code
    SJA1000 的帧过滤验收码，对经过屏蔽码过滤为“有关位”进行匹配，全部匹配成功后，此报文可以被接收，否则不接收。推荐设置为 0。
    acc_mask
    SJA1000 的帧过滤屏蔽码，对接收的 CAN 帧 ID 进行过滤，位为 0 的是“有关位”，位为 1 的是“无关位”。推荐设置为 0xFFFFFFFF，即全部接收。
    reserved
    仅作保留，不设置。
    filter
    滤波方式，=1 表示单滤波，=0 表示双滤波。
    timing0
    忽略，不设置。
    timing1
    忽略，不设置。
    mode
    工作模式，=0 表示正常模式（相当于正常节点），=1 表示只听模式（只接收，不影响总线）。
	注：当设备类型为 PCI-5010-U、PCI-5020-U、USBCAN-E-U、 USBCAN-2E-U、USBCAN-4E-U、CANDTU 时，帧过滤（acc_code 和 acc_mask 忽略）采用 GetIProperty 设置，详GetIProperty。
2、CANFD 设备
    acc_code
    验收码，同 CAN 设备。
    acc_mask
    屏蔽码，同 CAN 设备。
    abit_timing
    忽略，不设置。
    dbit_timing
    忽略，不设置。
    brp
    波特率预分频因子，设置为 0。
    filter
    滤波方式，同 CAN 设备。
    mode
    模式，同 CAN 设备。
    pad
    数据对齐，不设置。
    reserved
    仅作保留，不设置。
	注：当设备类型为 USBCANFD-100U、USBCANFD-200U、USBCANFD-MINI 时，帧过滤(acc_code和 acc_mask 忽略)采用 GetIProperty 设置，详见 GetIProperty。
	注：当设备类型为 PCIECANFD-100U、PCIECANFD-400U、MiniPCIeCANFD、M.2CANFD 时，模式mode 在正常模式(0)和只听模式(1)基础上，支持自发自收模式(2)和单次发送模式(3)。单次发送模式：CAN处于正常模式，但是发送失败时不会进行重发，此时发送超时无效。
```

### 错误与状态类结构体

#### ZCAN_CHANNEL_ERROR_INFO

结构体详情见程序清单 3.3，包含总线错误信息，在函数 ZCAN_ReadChannelErrInfo 中被填充。

程序清单 3.3 ZCAN_CHANNEL_ERROR_INFO 结构体成员

```c++
typedef struct tagZCAN_CHANNEL_ERROR_INFO {
    UINT error_code;
    BYTE passive_ErrData[3];
    BYTE arLost_ErrData;
} ZCAN_CHANNEL_ERROR_INFO;
```

成员

```c++
error_code
错误码，详见附录 3 - 错误码定义。
passive_ErrData
当产生的错误中有消极错误时表示为消极错误的错误标识数据。
arLost_ErrData
当产生的错误中有仲裁丢失错误时表示为仲裁丢失错误的错误标识数据。
```

#### ZCAN_CHANNEL_STATUS

结构体详情见程序清单 3.4，包含控制器状态信息，在函数 ZCAN_ReadChannelStatus 中被填充。

程序清单 3.4 ZCAN_CHANNEL_STATUS 结构体成员

```c++
typedef struct tagZCAN_CHANNEL_STATUS {
    BYTE errInterrupt;
    BYTE regMode;
    BYTE regStatus;
    BYTE regALCapture;
    BYTE regECCapture;
    BYTE regEWLimit;
    BYTE regRECounter;
    BYTE regTECounter;
    UINT Reserved;
} ZCAN_CHANNEL_STATUS;
```

成员

```c++
errInterrupt
中断记录，读操作会清除中断。
regMode
CAN 控制器模式寄存器值。
regStatus
CAN 控制器状态寄存器值。
regALCapture
CAN 控制器仲裁丢失寄存器值。
regECCapture
CAN 控制器错误寄存器值。
regEWLimit
CAN 控制器错误警告限制寄存器值。默认为 96。
regRECounter
CAN 控制器接收错误寄存器值。为 0-127 时，为错误主动状态；为 128-254 时，为错误被动状态；为 255 时，为总线关闭状态。
regTECounter
CAN 控制器发送错误寄存器值。为 0-127 时，为错误主动状态；为 128-254 时，为错误被动状态；为 255 时，为总线关闭状态。
Reserved
仅作保留，不设置。
```


### CAN / CANFD 帧结构

#### can_frame

结构体详情见程序清单 3.5，包含了 CAN 报文信息。

程序清单 3.5 can_frame 结构体成员

```c++
struct can_frame {
    canid_t can_id;   /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    __u8    can_dlc;  /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    __u8    __pad;    /* padding */
    __u8    __res0;   /* reserved / padding */
    __u8    __res1;   /* reserved / padding */
    __u8    data[CAN_MAX_DLEN];
};
```

成员

```c++
can_id
帧 ID，32 位，高 3 位属于标志位，标志位含义如下：
第 31 位(最高位)代表扩展帧标志，=0 表示标准帧，=1 代表扩展帧，宏 IS_EFF 可获取该标志；
第 30 位代表远程帧标志，=0 表示数据帧，=1 表示远程帧，宏 IS_RTR 可获取该标志；
第 29 位代表错误帧标志，=0 表示 CAN 帧，=1 表示错误帧，目前只能设置为 0；
其余位代表实际帧 ID 值，使用宏 MAKE_CAN_ID 构造 ID，使用宏 GET_ID 获取 ID。
can_dlc
数据长度（字节数）。
__pad
对齐填充，忽略。
__res0
仅作保留，不设置。
__res1
仅作保留，不设置。
data
报文数据，有效长度为 can_dlc。
```

#### canfd_frame

结构体详情见程序清单 3.6，包含了 CANFD 报文信息。

程序清单 3.6 canfd_frame 结构体成员

```c++
struct canfd_frame {
    canid_t can_id;   /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    __u8    len;      /* frame payload length in byte */
    __u8    flags;    /* additional flags for CAN FD, i.e error code */
    __u8    __res0;   /* reserved / padding */
    __u8    __res1;   /* reserved / padding */
    __u8    data[CANFD_MAX_DLEN];
};
```

成员

```c++
can_id
帧 ID，同 can_frame 结构的 can_id 成员。
len
数据长度（字节数）。
flags
额外标志，例如使用 CANFD 加速（BRS），则设置为宏 CANFD_BRS。
__res0
仅作保留，不设置。
__res1
仅作保留，不设置。
data
报文数据，有效长度为 len。
```


### 发送数据结构

#### ZCAN_Transmit_Data

结构体详情见程序清单 3.7，包含发送的 CAN 报文信息，在函数 ZCAN_Transmit 中使用。

程序清单 3.7 ZCAN_Transmit_Data 结构体成员

```c++
typedef struct tagZCAN_Transmit_Data {
    can_frame frame;
    UINT     transmit_type;
} ZCAN_Transmit_Data;
```

成员

```c++
frame
报文数据信息，详见 can_frame 结构说明。
transmit_type
发送方式，0=正常发送，1=单次发送，2=自发自收，3=单次自发自收。
发送方式说明：
- 正常发送：在 ID 仲裁丢失或发送出现错误时，CAN 控制器会自动重发，直到发送成功、发送超时或总线关闭。
- 单次发送：仲裁丢失或发送错误时，CAN 控制器不会重发报文。适用于允许部分数据丢失、不能出现传输延迟的应用。
- 自发自收：产生一次带自接收特性的正常发送，发送完成后可以从接收缓冲区中读到已发送的报文。
- 单次自发自收：产生一次带自接收特性的单次发送，发送出错或仲裁丢失不会执行重发。
```

#### ZCAN_TransmitFD_Data

结构体详情见程序清单 3.8，包含发送的 CANFD 报文信息，在函数 ZCAN_TransmitFD 中使用。

程序清单 3.8 ZCAN_TransmitFD_Data 结构体成员

```c++
typedef struct tagZCAN_TransmitFD_Data {
    canfd_frame frame;
    UINT        transmit_type;
} ZCAN_TransmitFD_Data;
```

成员

```c++
frame
报文数据信息，详见 canfd_frame 结构说明。
transmit_type
发送方式，同 ZCAN_Transmit_Data 结构的 transmit_type 成员。
```


### 接收数据结构

#### ZCAN_Receive_Data

结构体详情见程序清单 3.9，包含接收的 CAN 报文信息，在函数 ZCAN_Receive 中使用。

程序清单 3.9 ZCAN_Receive_Data 结构体成员

```c++
typedef struct tagZCAN_Receive_Data {
    can_frame frame;
    UINT64    timestamp;
} ZCAN_Receive_Data;
```

成员

```c++
frame
报文数据信息，详见 can_frame 结构说明。
timestamp
时间戳，单位微秒。对于本地设备，基于设备启动时间；对于云设备，基于 1970 年 1 月 1 日 0 时 0 分 0 秒。
```

#### ZCAN_ReceiveFD_Data

结构体详情见程序清单 3.10，包含接收的 CANFD 报文信息，在函数 ZCAN_ReceiveFD 中使用。

程序清单 3.10 ZCAN_ReceiveFD_Data 结构体成员

```c++
typedef struct tagZCAN_ReceiveFD_Data {
    canfd_frame frame;
    UINT64      timestamp;
} ZCAN_ReceiveFD_Data;
```

成员

```c++
frame
报文数据信息，详见 canfd_frame 结构说明。
timestamp
时间戳，单位微秒。
```


### 定时发送结构体

#### ZCAN_AUTO_TRANSMIT_OBJ

结构体详情见程序清单 3.11，包含定时发送 CAN 参数信息。

程序清单 3.11 ZCAN_AUTO_TRANSMIT_OBJ 结构体成员

```c++
typedef struct tagZCAN_AUTO_TRANSMIT_OBJ {
    USHORT enable;
    USHORT index;
    UINT    interval;  /* 定时发送时间，单位毫秒 */
    ZCAN_Transmit_Data obj;
} ZCAN_AUTO_TRANSMIT_OBJ, *PZCAN_AUTO_TRANSMIT_OBJ;
```

成员

```c++
enable
使能本条报文，0=禁能，1=使能。
index
报文编号，从 0 开始，编号相同则使用最新的一条信息。
interval
发送周期，单位毫秒。
obj
发送的报文，详见 ZCAN_Transmit_Data 结构说明。
```

#### ZCANFD_AUTO_TRANSMIT_OBJ

结构体详情见程序清单 3.12，包含定时发送 CANFD 参数信息。

程序清单 3.12 ZCANFD_AUTO_TRANSMIT_OBJ 结构体成员

```c++
typedef struct tagZCANFD_AUTO_TRANSMIT_OBJ {
    USHORT enable;
    USHORT index;
    UINT    interval;
    ZCAN_TransmitFD_Data obj;
} ZCANFD_AUTO_TRANSMIT_OBJ, *PZCANFD_AUTO_TRANSMIT_OBJ;
```

成员

```c++
enable
使能本条报文，0=禁能，1=使能。
index
报文编号，从 0 开始，编号相同则使用最新的一条信息。
interval
发送周期，单位毫秒。
obj
发送的报文，详见 ZCAN_TransmitFD_Data 结构说明。
```

#### ZCAN_AUTO_TRANSMIT_OBJ_PARAM

用于设置定时发送额外的参数，目前只支持 USBCANFD-X00U 系列设备。

程序清单 3.13 ZCAN_AUTO_TRANSMIT_OBJ_PARAM 结构体成员

```c++
typedef struct tagZCAN_AUTO_TRANSMIT_OBJ_PARAM {
    USHORT type;   /* 参数类型，目前类型只有 1：表示启动延时 */
    USHORT index;  /* 定时发送帧的索引 */
    UINT    value;  /* 参数数值，单位 ms */
} ZCAN_AUTO_TRANSMIT_OBJ_PARAM, *PZCAN_AUTO_TRANSMIT_OBJ_PARAM;
```


### 云设备相关结构体

#### ZCLOUD_DEVINFO

结构体详情见程序清单 3.14，包含云设备的属性信息，在 ZCLOUD_GetUserData 中被填充。

程序清单 3.14 ZCLOUD_DEVINFO 结构体成员

```c++
typedef struct tagZCLOUD_DEVINFO {
    int    devIndex;
    char   type[64];
    char   id[64];
    char   owner[64];
    char   model[64];
    char   fwVer[16];
    char   hwVer[16];
    char   serial[64];
    int    status;
    BYTE   bCanUploads[16];
    BYTE   bGpsUpload;
} ZCLOUD_DEVINFO;
```

成员

```c++
devIndex
设备索引号，指该设备在该用户关联的所有设备中的索引序号。
type
设备类型字符串。
id
设备唯一识别号，字符串。
owner
设备的拥有者。
model
模块型号字符串。
fwVer
固件版本号字符串，如 V1.01。
hwVer
硬件版本号字符串，如 V1.01。
serial
设备序列号字符串。
status
设备状态，0：设备在线，1：设备离线。
bCanUploads
各通道数据云上送使能，0：不上送，1：上送。
bGpsUpload
设备 GPS 数据云上送使能，0：不上送，1：上送。
```

#### ZCLOUD_USER_DATA

结构体详情见程序清单 3.15，包含用户信息，包含用户基本信息以及用户拥有的设备信息，通过 ZCLOUD_GetUserData 获取。

程序清单 3.15 ZCLOUD_USER_DATA 结构体成员

```c++
typedef struct tagZCLOUD_USER_DATA {
    char                username[64];
    char                mobile[64];
    ZCLOUD_DEVINFO      devices[ZCLOUD_MAX_DEVICES];
    size_t              devCnt;
} ZCLOUD_USER_DATA;
```

成员

```c++
username
用户名字符串。
mobile
用户手机号。
devices
用户拥有的设备组，详见 ZCLOUD_DEVINFO 结构说明。
devCnt
设备个数。
```

#### ZCLOUD_GPS_FRAME

结构体详情见程序清单 3.16，包含设备 GPS 数据，通过 ZCLOUD_ReceiveGPS 获取。

程序清单 3.16 ZCLOUD_GPS_FRAME 结构体成员

```c++
typedef struct tagZCLOUD_GPS_FRAME {
    float latitude;
    float longitude;
    float speed;
    struct __gps_time {
        USHORT year;
        USHORT mon;
        USHORT day;
        USHORT hour;
        USHORT min;
        USHORT sec;
    } tm;
} ZCLOUD_GPS_FRAME;
```

成员

```c++
latitude
纬度。
longitude
经度。
speed
速度。
tm
时间结构。
```


### 属性操作接口

#### IProperty

结构体详情见程序清单 3.17，用于获取/设置设备参数信息。

程序清单 3.17 IProperty 结构体成员

```c++
typedef struct tagIProperty {
    SetValueFunc     SetValue;
    GetValueFunc     GetValue;
    GetPropertysFunc GetPropertys;
} IProperty;
```

成员

```c++
SetValue
设置设备属性值，函数指针，详见 3.3 小节。
GetValue
获取属性值，函数指针。
GetPropertys
用于返回设备包含的所有属性，函数指针。
```


### LIN 相关结构体

#### ZCAN_LIN_MSG

结构体详情见程序清单 3.19，该结构体定义了 LIN 消息的结构，在设置从站响应信息和接收 LIN 数据接口中使用此结构表示单帧 LIN 消息。

程序清单 3.19 ZCAN_LIN_MSG 结构体成员

```c++
typedef struct _VCI_LIN_MSG {
    BYTE chnl;
    BYTE dataType;
    union {
        ZCANLINData      zcanLINData;
        ZCANLINErrData    zcanLINErrData;
        BYTE             raw[46];
    } data;
} ZCAN_LIN_MSG, *PZCAN_LIN_MSG;
```

成员

```c++
chnl
数据通道。
dataType
数据类型，0-LIN 数据，1-LIN 错误数据。
data
实际数据，联合体，有效成员根据 dataType 字段而定。
```

#### ZCAN_LIN_INIT_CONFIG

结构体详情见程序清单 3.20，该结构体表示配置 LIN 的信息，在函数 ZCAN_InitLIN 函数中调用。用于设置设备 LIN 的工作模式、波特率，是否使用增强校验等信息。

程序清单 3.20 ZCAN_LIN_INIT_CONFIG 结构体成员

```c++
typedef struct _VCI_LIN_INIT_CONFIG {
    BYTE   linMode;
    BYTE   chkSumMode;
    USHORT reserved;
    UINT   linBaud;
} ZCAN_LIN_INIT_CONFIG, *PZCAN_LIN_INIT_CONFIG;
```

成员

```c++
linMode
LIN 工作模式，从站为 0，主站为 1。
chkSumMode
校验方式，1-经典校验，2-增强校验，3-自动（即经典校验跟增强校验都会进行轮询）。
reserved
保留位。
linBaud
LIN 波特率，取值 1000~20000。
```

#### ZCANCANFDData

结构体详情见程序清单 3.21，该结构体表示 CAN/CANFD 帧结构，可以表示发送接收 CAN/CANFD 帧，目前仅作为 ZCANDataObj 结构的成员使用。

程序清单 3.21 ZCANCANFDData 结构体成员

```c++
typedef struct tagZCANCANFDData {
    UINT64 timeStamp;
    union {
        struct {
            UINT frameType      : 2;
            UINT txDelay        : 2;
            UINT transmitType   : 4;
            UINT txEchoRequest  : 1;
            UINT txEchoed       : 1;
            UINT reserved       : 22;
        } unionVal;
        UINT rawVal;
    } flag;
    BYTE       extraData[4];
    canfd_frame frame;
} ZCANCANFDData;
```

成员

```c++
timeStamp
时间戳。作为接收帧时，时间戳单位微秒(us)。正常发送时，timeStamp 字段无意义。队列延迟发送数据时，timeStamp 字段存放发送当前帧后设备等待的时间，时间单位取决于 flag.unionVal.txDelay。
flag
flag 字段表示 CAN/CANFD 帧的标记信息，长度 4 字节。
- frameType：帧类型，0=CAN 帧，1=CANFD 帧
- txDelay：队列发送延时，0=不启用延时，1=启用延时（单位 1ms），2=启用延时（单位 0.1ms）
- transmitType：发送类型，0=正常发送，1=单次发送，2=自发自收，3=单次自发自收
- txEchoRequest：发送回显请求，0=不需要设备回显发送帧，1=请求设备回显发送帧
- txEchoed：报文是否是发送回显报文，0=正常总线接收到的报文，1=本设备发送回显报文
extraData
帧附加数据，暂未使用。
frame
CAN/CANFD 帧数据，参考 canfd_frame 结构体。
```

#### ZCANErrorData

结构体详情见程序清单 3.22，该结构体表示错误信息结构，可以表示总线错误、控制器错误、设备端错误等错误信息，目前仅作为 ZCANDataObj 结构的成员使用。

程序清单 3.22 ZCANErrorData 结构体成员

```c++
typedef struct tagZCANErrorData {
    UINT64 timeStamp;
    BYTE   errType;
    BYTE   errSubType;
    BYTE   nodeState;
    BYTE   rxErrCount;
    BYTE   txErrCount;
    BYTE   errData;
    BYTE   reserved[2];
} ZCANErrorData;
```

成员

```c++
timeStamp
时间戳，表示错误产生的时间，单位微秒(us)。
errType
错误类型：0=未知错误，1=总线错误，2=控制器错误，3=终端设备错误。
errSubType
错误子类型，根据 errType 不同表示不同的含义。
nodeState
节点状态，显示当前节点的总线状态（errType=1 时有效）：1=总线积极，2=总线告警，3=总线消极，4=总线关闭。
rxErrCount
接收错误计数（errType=1 时有效）。
txErrCount
发送错误计数（errType=1 时有效）。
errData
错误数据（errType=3 且 errSubType=3 时有效，存放定时发送帧的索引）。
reserved
保留字段，未使用。
```

#### ZCANGPSData

结构体详情见程序清单 3.23，该结构体表示 GPS 数据，目前仅作为 ZCANDataObj 结构的成员使用。

程序清单 3.23 ZCANGPSData 结构体成员

```c++
typedef struct tagZCANGPSData {
    struct {
        USHORT year;
        USHORT mon;
        USHORT day;
        USHORT hour;
        USHORT min;
        USHORT sec;
        USHORT milsec;
    } time;
    union {
        struct {
            USHORT timeValid       : 1;
            USHORT latlongValid    : 1;
            USHORT altitudeValid   : 1;
            USHORT speedValid      : 1;
            USHORT courseAngleValid: 1;
            USHORT reserved        : 11;
        } unionVal;
        USHORT rawVal;
    } flag;
    double latitude;
    double longitude;
    double altitude;
    double speed;
    double courseAngle;
} ZCANGPSData;
```

成员

```c++
time
UTC 时间，表示定位数据的时间。
flag
数据标志位，用于标识定位数据的有效性。
latitude
纬度，正数表示北纬，负数表示南纬。
longitude
经度，正数表示东经，负数表示西经。
altitude
海拔，单位：米。
speed
速度，单位：km/h。
courseAngle
航向角。
```

#### ZCANLINData

结构体详情见程序清单 3.24，该结构体表示 LIN 数据结构，目前仅作为 ZCANDataObj 结构的成员使用。

程序清单 3.24 ZCANLINData 结构体成员

```c++
typedef struct tagZCANLINData {
    union {
        struct {
            BYTE ID      : 6;
            BYTE Parity  : 2;
        } unionVal;
        BYTE rawVal;
    } PID;
    struct {
        UINT64 timeStamp;
        BYTE   dataLen;
        BYTE   dir;
        BYTE   chkSum;
        BYTE   reserved[13];
        BYTE   data[8];
    } RxData;
    BYTE reserved[3];
} ZCANLINData;
```

成员

```c++
PID
受保护的帧 ID。PID 包含帧 ID(PID.unionVal.ID)和帧 ID 校验(PID.unionVal.Parity)两个部分。
RxData
数据部分，仅接收数据时有效。包含时间戳、数据长度、传输方向、校验和、数据等字段。
reserved
保留。
```

#### ZCANLINErrData

结构体详情见程序清单 3.25，该结构体表示 LIN 错误数据结构，目前仅作为 ZCANDataObj 结构的成员使用。

程序清单 3.25 ZCANLINErrData 结构体成员

```c++
typedef struct tagZCANLINErrData {
    UINT64 timeStamp;
    union {
        struct {
            BYTE ID     : 6;
            BYTE Parity : 2;
        } unionVal;
        BYTE rawVal;
    } PID;
    BYTE dataLen;
    BYTE data[8];
    union {
        struct {
            USHORT errStage  : 4;
            USHORT errReason : 4;
            USHORT reserved  : 8;
        } unionVal;
        USHORT unionErrData;
    } errData;
    BYTE dir;
    BYTE chkSum;
    BYTE reserved[10];
} ZCANLINErrData;
```

成员

```c++
timeStamp
时间戳，单位微秒(us)，表示数据帧接收时间。
PID
受保护的帧 ID。
dataLen
数据长度。
data
数据。
errData
错误标志。errStage 表示错误阶段；errReason 表示错误原因。
dir
传输方向。
chkSum
数据校验。
reserved
保留。
```

#### ZCAN_LIN_SUBSCIBE_CFG

结构体详情见程序清单 3.26，该结构体表示 LIN 订阅数据结构。

程序清单 3.26 ZCAN_LIN_SUBSCIBE_CFG 结构体成员

```c++
typedef struct _VCI_LIN_SUBSCIBE_CFG {
    BYTE ID;
    BYTE dataLen;
    BYTE chkSumMode;
    BYTE reserved[5];
} ZCAN_LIN_SUBSCIBE_CFG;
```

成员

```c++
ID
受保护的 ID（ID 取值范围为 0-63）。
dataLen
数据长度，范围为 1-8，当为 255（0xFF）则表示设备自动识别报文长度。
chkSumMode
校验方式，0=默认（启动时配置），1=经典校验，2=增强校验，3=自动。
reserved
保留。
```

#### ZCAN_LIN_PUBLISH_CFG

结构体详情见程序清单 3.27，该结构体表示 LIN 发布数据结构。

程序清单 3.27 ZCAN_LIN_PUBLISH_CFG 结构体成员

```c++
typedef struct _VCI_LIN_PUBLISH_CFG {
    BYTE ID;
    BYTE dataLen;
    BYTE data[8];
    BYTE chkSumMode;
    BYTE reserved[5];
} ZCAN_LIN_PUBLISH_CFG;
```

成员

```c++
ID
受保护的 ID（ID 取值范围为 0-63）。
dataLen
数据长度，范围为 1-8。
data
数据。
chkSumMode
校验方式，0=默认（启动时配置），1=经典校验，2=增强校验。
reserved
保留。
```


### 合并接收数据结构

#### ZCANDataObj

结构体详情见程序清单 3.28，该结构作为合并接收使用的各种数据的载体，支持 CAN、CANFD、LIN、GPS、错误数据等各种不同类型的数据。

程序清单 3.28 ZCANDataObj 结构体成员

```c++
typedef struct tagZCANDataObj {
    BYTE dataType;
    BYTE chnl;
    union {
        struct {
            USHORT reserved : 16;
        } unionVal;
        USHORT rawVal;
    } flag;
    BYTE extraData[4];
    union {
        ZCANCANFDData  zcanCANFDData;
        ZCANErrorData  zcanErrData;
        ZCANGPSData    zcanGPSData;
        ZCANLINData    zcanLINData;
        ZCANLINErrData zcanLINErrData;
        BYTE           raw[92];
    } data;
} ZCANDataObj;
```

成员

```c++
dataType
数据类型：1=CAN/CANFD 数据，2=错误数据，3=GPS 数据，4=LIN 数据，5=总线利用率数据，6=LIN 错误数据。
chnl
数据通道。
flag
数据标志，暂未使用。
extraData
额外数据，暂未使用。
data
实际数据，联合体，根据 dataType 决定有效成员。
```


### 动态配置结构体

#### ZCAN_DYNAMIC_CONFIG_DATA

结构体详情见程序清单 3.29，该结构体表示动态配置结构。

程序清单 3.29 ZCAN_DYNAMIC_CONFIG_DATA 结构体成员

```c++
typedef struct tagZCAN_DYNAMIC_CONFIG_DATA {
    char key[64];
    char value[64];
} ZCAN_DYNAMIC_CONFIG_DATA;
```

成员

```c++
key
动态配置的 key。
value
下发动态配置项的数据。
```


### UDS 相关结构体

#### ZCAN_UDS_REQUEST

结构体详情见程序清单 3.30，该结构体表示 CAN UDS 请求数据。

程序清单 3.30 ZCAN_UDS_REQUEST 结构体成员

```c++
typedef struct _ZCAN_UDS_REQUEST {
    UINT                   req_id;
    BYTE                   channel;
    ZCAN_UDS_FRAME_TYPE    frame_type;
    BYTE                   reserved0[2];
    UINT                   src_addr;
    UINT                   dst_addr;
    BYTE                   suppress_response;
    BYTE                   sid;
    BYTE                   reserved1[6];
    struct {
        UINT                   timeout;
        UINT                   enhanced_timeout;
        BYTE                   check_any_negative_response : 1;
        BYTE                   wait_if_suppress_response    : 1;
        BYTE                   flag                         : 6;
        BYTE                   reserved0[7];
    } session_param;
    struct {
        ZCAN_UDS_TRANS_VER  version;
        BYTE                 max_data_len;
        BYTE                 local_st_min;
        BYTE                 block_size;
        BYTE                 fill_byte;
        BYTE                 ext_frame;
        BYTE                 is_modify_ecu_st_min;
        BYTE                 remote_st_min;
        UINT                 fc_timeout;
        BYTE                 reserved0[4];
    } trans_param;
    BYTE                  *data;
    UINT                   data_len;
    UINT                   reserved2;
} ZCAN_UDS_REQUEST;
```

#### ZLIN_UDS_REQUEST

结构体详情见程序清单 3.31，该结构体表示 LIN UDS 请求数据。

程序清单 3.31 ZLIN_UDS_REQUEST 结构体成员

```c++
typedef struct _ZLIN_UDS_REQUEST {
    UINT  req_id;
    BYTE  channel;
    BYTE  suppress_response;
    BYTE  sid;
    BYTE  Nad;
    BYTE  reserved1[8];
    struct {
        UINT p2_timeout;
        UINT enhanced_timeout;
        BYTE check_any_negative_response : 1;
        BYTE wait_if_suppress_response    : 1;
        BYTE flag                         : 6;
        BYTE reserved0[7];
    } session_param;
    BYTE *data;
    UINT  data_len;
    UINT  reserved2;
} ZLIN_UDS_REQUEST;
```

#### ZCAN_UDS_RESPONSE

结构体详情见程序清单 3.32，该结构体表示 UDS 响应数据。

程序清单 3.32 ZCAN_UDS_RESPONSE 结构体成员

```c++
typedef struct _ZCAN_UDS_RESPONSE {
    union {
        struct {
            BYTE is_positive : 1;
            BYTE reserved    : 7;
        } unionVal;
        BYTE rawVal;
    } flag;
    BYTE  sid;
    BYTE  nrc;
    BYTE  data_len;
    BYTE *data;
} ZCAN_UDS_RESPONSE;
```

#### ZCAN_UDS_CTRL_REQ

结构体详情见程序清单 3.33，该结构体表示 UDS 控制请求。

程序清单 3.33 ZCAN_UDS_CTRL_REQ 结构体成员

```c++
typedef struct _ZCAN_UDS_CTRL_REQ {
    UINT req_id;
    ZCAN_UDS_CTRL_CMD cmd;
} ZCAN_UDS_CTRL_REQ;
```

#### ZCAN_UDS_CTRL_RESP

结构体详情见程序清单 3.34，该结构体表示 UDS 控制响应数据。

程序清单 3.34 ZCAN_UDS_CTRL_RESP 结构体成员

```c++
typedef struct _ZCAN_UDS_CTRL_RESP {
    ZCAN_UDS_CTRL_CMD cmd;
    ZCAN_RET_STATUS    ret;
} ZCAN_UDS_CTRL_RESP;
```

#### ZCANCANFDUdsData

结构体详情见程序清单 3.35，该结构体表示 CAN/CAN FD UDS 数据。

程序清单 3.35 ZCANCANFDUdsData 结构体成员

```c++
typedef struct tagZCANCANFDUdsData {
    ZCANUdsRequestDataObj req;
    ZCAN_UDS_RESPONSE    resp;
} ZCANCANFDUdsData;
```

#### ZCANLINUdsData

结构体详情见程序清单 3.36，该结构体表示 LIN UDS 数据。

程序清单 3.36 ZCANLINUdsData 结构体成员

```c++
typedef struct tagZCANLINUdsData {
    ZCANUdsRequestDataObj req;
    ZCAN_UDS_RESPONSE    resp;
} ZCANLINUdsData;
```

#### ZCANUdsRequestDataObj

结构体详情见程序清单 3.37，该结构体表示 UDS 数据结构，支持 CAN/LIN 等 UDS 不同传输层。

程序清单 3.37 ZCANUdsRequestDataObj 结构体成员

```c++
typedef struct tagZCANUdsRequestDataObj {
    ZCAN_UDS_DATA_DEF dataType;
    union {
        ZCAN_UDS_REQUEST   canUdsReq;
        ZLIN_UDS_REQUEST   linUdsReq;
        ZCAN_UDS_RESPONSE  resp;
    } data;
} ZCANUdsRequestDataObj;
```

---

