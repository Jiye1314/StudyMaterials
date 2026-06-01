#include "mainwindow.h"
#include "ui_mainwindow.h"

#define USBCAN_FD_200U_def

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    btnSetEnableFalse();
    usbC_fd_200u = new USBCAN_FD_200U(this);

    connect(usbC_fd_200u,&USBCAN_FD_200U::signalsSendNum,this,&MainWindow::slotsUpdateNum, Qt::QueuedConnection);
    //连接转数和 PWM（表格）
    connect(this,&MainWindow::signalLSpeedSetNum,usbC_fd_200u,&USBCAN_FD_200U::slotsSetLSpeedSet1);
    connect(this,&MainWindow::signalLPWMenableNum,usbC_fd_200u,&USBCAN_FD_200U::slotsSetLPWMenable1);
    //连接转数 rpm
    connect(this,&MainWindow::signalLSpeedSetNum,this,&MainWindow::slotsUpdateRpmNum);
    //连接中断提醒信号
    connect(usbC_fd_200u,&USBCAN_FD_200U::signalsExceptionStatus,this,&MainWindow::slotsExceptionStatus);

    qDebug()<<"当前时间："<<QDateTime::currentDateTime();

    // CAN 帧 → 表格刷新
    connect(usbC_fd_200u, &USBCAN_FD_200U::signalsReceivedFrame,this, &MainWindow::slotsUpdateTableWidget, Qt::QueuedConnection);
    initTableForID();
}

MainWindow::~MainWindow()
{
    usbC_fd_200u->closeAllSend();
    delete ui;

}


void MainWindow::on_btn_openDev_clicked()
{

    if(usbC_fd_200u->openDevice_fd_200u())
    {
        // 初始化表格
        initTableForID();
        btnSetEnableTrue();
        ui->comboBox_dataFrame->setCurrentIndex(0);
    }
    else
    {
        btnSetEnableFalse();
    }

}


void MainWindow::on_btn_send_clicked()
{    
    if(usbC_fd_200u->timerSend_can())
    {
        ui->btn_send->setText("关闭定时发送");
    }else
    {
        ui->btn_send->setText("开启定时发送");
    }
}


void MainWindow::on_btn_closeDev_clicked()
{
    //将速度和使能至 0
    ui->spinBox->setValue(0);
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_num->setText(QString::number(0));
    //触发设置速度将速度改 0
    on_btn_setL_speedSet_clicked();
    if(usbC_fd_200u->closeDevice_fd_200u())
    {
        btnSetEnableFalse();
        ui->tableWidget->clear();
    }
    ui->btn_send->setText("开启定时发送");
    ui->btn_openDev->setEnabled(true);
}

void MainWindow::btnSetEnableTrue()
{
    ui->btn_openDev->setEnabled(false);
    ui->btn_closeDev->setEnabled(true);
    ui->btn_send->setEnabled(true);
    ui->btn_send_2->setEnabled(true);
    ui->comboBox->setEnabled(true);
    ui->spinBox->setEnabled(true);
    ui->btn_setL_speedSet->setEnabled(true);
    ui->comboBox_channel->setEnabled(true);
    ui->comboBox_dataFrame->setEnabled(true);
    ui->comboBox_dataLength->setEnabled(true);
    ui->comboBox_typeFrame->setEnabled(true);
    ui->lineEdit_data->setEnabled(true);
    ui->lineEdit_frameID->setEnabled(true);
    // 限制 帧ID 输入框：只能输入 0-9 a-f A-F
    ui->lineEdit_frameID->setValidator(new QRegExpValidator(QRegExp("[0-9a-fA-F]+"), this));
    // 限制 数据 输入框：只能输入 0-9 a-f A-F 和 空格（方便输入 11 22 33）
    ui->lineEdit_data->setValidator(new QRegExpValidator(QRegExp("[0-9a-fA-F\\s]+"), this));
}

void MainWindow::btnSetEnableFalse()
{
    ui->btn_openDev->setEnabled(true);
    ui->btn_closeDev->setEnabled(false);
    ui->btn_send->setEnabled(false);
    ui->btn_send_2->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->spinBox->setEnabled(false);
    ui->btn_setL_speedSet->setEnabled(false);
    ui->comboBox_channel->setEnabled(false);
    ui->comboBox_dataFrame->setEnabled(false);
    ui->comboBox_dataLength->setEnabled(false);
    ui->comboBox_typeFrame->setEnabled(false);
    ui->lineEdit_data->setEnabled(false);
    ui->lineEdit_frameID->setEnabled(false);
}

//手动发送
void MainWindow::on_btn_send_2_clicked()
{
    //从Ui读取并解析数据长度 直接用显示文字转成 int
    int length = ui->comboBox_dataLength->currentIndex() + 1;

    //从UI读取并解析帧ID
    QString idStr = ui->lineEdit_frameID->text().trimmed();
    // 按16进制解析
    uint32_t canId = idStr.toUInt(nullptr, 16);

    //从UI读取并解析数据
    //输入内容是"00 11 22"这样的空格分隔16进制字符串
    QString dataStr = ui->lineEdit_data->text().trimmed();
    QStringList data = dataStr.split(" ", QString::SkipEmptyParts);

    //从ui读取帧类型
    unsigned char type = ui->comboBox_dataFrame->currentIndex();
    if(type == 1)
        usbC_fd_200u->type = 1;

    if(usbC_fd_200u->Send_fd_200u(length,data,canId))
    {
        ui->statusBar->showMessage("发送数据成功！",1000);
    }
    else
    {
        ui->statusBar->showMessage("发送数据失败！",1000);
    }

    usbC_fd_200u->type = 0;
}

// 收到帧时更新表格
void MainWindow::slotsUpdateTableWidget(int channel, int canId, int dlc, const QByteArray &data)
{

    m_frameCountMap[canId]++;

    // ===================== 动态 QMap 替换 switch =====================
        int row;
        // 查找ID是否已存在
        if (s_canIdToRow.contains(canId)) {
            row = s_canIdToRow[canId];
        } else {
            // 新ID：分配新行号，并记录到映射表
            row = s_nextRow++;
            s_canIdToRow[canId] = row;
            // 自动插入一行
            ui->tableWidget->insertRow(row);
        }
        // ===============================================================

    unsigned char length = 4;
    if(ui->comboBox_dataFrame->currentIndex() == 1 && row == 8)
        length = 8;
    // 转为 QString，保留 0x 前缀 + 固定4位十六进制  手动加上 0x 前缀（最终字符串：0x001A）
    QString strID = "0x" + QString("%1").arg(canId, length, 16, QChar('0')).toUpper();


    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QTime::currentTime().toString("HH:mm:ss")));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(strID));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(dlc)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString(data)));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(m_frameCountMap[canId])));
}

//初始化表格
void MainWindow::initTableForID()
{
    ui->tableWidget->setRowCount(0); // 0 行
    ui->tableWidget->setColumnCount(5); // 通道、ID、DLC、数据、次数

    QStringList headers;
    headers << "接收时间" << "报文ID" << "报文长度" << "数据" << "接收次数";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // 第0列宽度80
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(1, 100);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(2, 70);
    // 其他列自动拉伸
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    //清空所有映射表和计数器
    m_frameCountMap.clear();

    s_canIdToRow.clear();
    s_nextRow = 0;

}

//更新计数
void MainWindow::slotsUpdateNum(int num)
{
    ui->lineEdit_num->setText(QString::number(num));
}

void MainWindow::slotsUpdateRpmNum(int num)
{
    ui->lineEdit_nowrpm->setText(QString::number(num));
}

//ui->comboBox取值
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    int num = ui->comboBox->currentText().toUInt();
    emit signalLPWMenableNum(num);
}

//点击确定后 ui->spinBox取值
void MainWindow::on_btn_setL_speedSet_clicked()
{
    int num = ui->spinBox->value();
    emit signalLSpeedSetNum(num);
}

//文本框每输入两个字符之后加个空格
void MainWindow::on_lineEdit_data_textEdited(const QString &arg1)
{
        // 1. 先把所有空格去掉
        //QString raw = arg1.remove(QString(" "));

        // 2. 过滤掉非十六进制字符（只保留0-9、A-F、a-f）
        QString hexOnly;
        for (auto c : arg1) {
            if ((c >= '0' && c <= '9') ||
                (c >= 'A' && c <= 'F') ||
                (c >= 'a' && c <= 'f')) {
                hexOnly += c;
            }
        }

        // 3. 每两个字符之间加空格
        QString formatted;
        for (int i = 0; i < hexOnly.size(); i += 2) {
            if (i > 0) formatted += " ";
            formatted += hexOnly.mid(i, 2);
        }

        // 4. 防止setText再次触发信号，先阻塞
        ui->lineEdit_data->blockSignals(true);
        ui->lineEdit_data->setText(formatted);
        ui->lineEdit_data->blockSignals(false);

        // 光标移到末尾，方便继续输入
        ui->lineEdit_data->setCursorPosition(formatted.size());
}

//中断异常提醒
void MainWindow::slotsExceptionStatus(int i,int num = 0)
{
    switch (i)
    {
    case -1:
        ui->statusBar->showMessage(QString("usb设备连接已断开！%1").arg(num),1000);
        QMessageBox::warning(this,"警告","usb设备连接已断开！任务已暂停!");
        ui->btn_send->setEnabled(false);
        break;
    case -2:
        ui->statusBar->showMessage(QString("CAN 控制器总线关闭！%1").arg(num),1000);
        QMessageBox::warning(this,"警告","CAN 控制器总线关闭！任务已暂停!");
        ui->btn_send->setEnabled(false);
        break;
    case -3:
        ui->statusBar->showMessage(QString("CAN 控制器消极错误！信号线连接不稳定。%1").arg(num),1000);
        break;
    case -4:
        ui->statusBar->showMessage(QString("CAN 控制器错误报警！%1").arg(num),1000);
        break;
    case -5:
        ui->statusBar->showMessage(QString("CAN 控制器处于 BusOff 状态！%1").arg(num),1000);
        QMessageBox::warning(this,"警告","CAN 控制器处于 BusOff 状态！任务已暂停!");
        ui->btn_send->setEnabled(false);
        break;
    default:
        return;
    }
}

//选择帧类型时触发
void MainWindow::on_comboBox_dataFrame_currentIndexChanged(int index)
{
    if(index == 0)
        ui->lineEdit_frameID->setMaxLength(3);
    else
        ui->lineEdit_frameID->setMaxLength(8);
}

