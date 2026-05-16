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
	注：当设备类型为 PCI-5010-U、PCI-5020-U、USBCAN-E-U、 USBCAN-2E-U、USBCAN-4E-U、CANDTU 时，帧过滤（acc_code 和 acc_mask 忽略）采用 GetIProperty 设置，详见 GetIProperty。
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

















































