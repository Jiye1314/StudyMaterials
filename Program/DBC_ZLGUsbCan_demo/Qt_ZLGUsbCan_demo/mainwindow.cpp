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

    qDebug()<<"当前时间："<<QDateTime::currentDateTime();

    // CAN 帧 → 表格刷新
    connect(usbC_fd_200u, &USBCAN_FD_200U::signalsReceivedFrame,this, &MainWindow::slotsUpdateTableWidget, Qt::QueuedConnection);
    initTableForID();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_openDev_clicked()
{

    if(usbC_fd_200u->openDevice_fd_200u())
    {
        // 初始化表格
        initTableForID();
        btnSetEnableTrue();
    }else
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

    if(usbC_fd_200u->closeDevice_fd_200u())
    {
        btnSetEnableFalse();
    }
    ui->btn_openDev->setEnabled(true);
}

void MainWindow::btnSetEnableTrue()
{
    ui->btn_openDev->setEnabled(false);
    ui->btn_closeDev->setEnabled(true);
    ui->btn_send->setEnabled(true);
    ui->btn_send_2->setEnabled(true);
    ui->comboBox->setEnabled(true);
    ui->doubleSpinBox->setEnabled(true);
}

void MainWindow::btnSetEnableFalse()
{
    ui->btn_openDev->setEnabled(true);
    ui->btn_closeDev->setEnabled(false);
    ui->btn_send->setEnabled(false);
    ui->btn_send_2->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
}


void MainWindow::on_btn_send_2_clicked()
{

    usbC_fd_200u->Send_fd_200u();

}

// 收到帧时更新表格
void MainWindow::slotsUpdateTableWidget(int channel, int canId, int dlc, const QByteArray &data)
{
    // 只显示 xxx 的帧
    //    if (canId != 0x0182 && canId != 0x0081 && canId != 0x0481)
    //    {
    //        return;
    //    }

    m_frameCountMap[canId]++;

    int row;
    switch (canId)
    {
        case 0x0182:
            row = 0;
            break;
        case 0x0081:
            row = 1;
            break;
        case 0x0080:
            row = 2;
            break;
        case 0x00FF:
            row = 3;
            break;
        case 0x0701:
            row = 4;
            break;
        case 0x0702:
            row = 5;
            break;
        case 0x00:
            row = 6;
            break;
        case 0x0481:
            row = 7;
            break;
        default:
            return;
    }

    // 转为 QString，保留 0x 前缀 + 固定4位十六进制
    QString strID = QString("%1").arg(canId, 4, 16, QChar('0')).toUpper();
    // 手动加上 0x 前缀（最终字符串：0x001A）
    strID = "0x" + strID;

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(channel)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(strID));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(dlc)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString(data)));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(m_frameCountMap[canId])));
}


void MainWindow::initTableForID()
{
    ui->tableWidget->setRowCount(8); // 8 行
    ui->tableWidget->setColumnCount(5); // 通道、ID、DLC、数据、次数

    QStringList headers;
    headers << "通道" << "报文ID" << "报文长度" << "数据" << "次数";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // 设置列宽
    ui->tableWidget->setColumnWidth(0, 50); // 通道
    ui->tableWidget->setColumnWidth(1, 80); // ID
    ui->tableWidget->setColumnWidth(2, 70); // DLC
    ui->tableWidget->setColumnWidth(3, 220); // 数据
    ui->tableWidget->setColumnWidth(4, 60); // 次数

    //清空
    m_frameCountMap.clear();
}

//更新计数
void MainWindow::slotsUpdateNum(int num)
{
    ui->lineEdit_num->setText(QString::number(num));
}

void MainWindow::slotsUpdateRpmNum(double num)
{
    ui->lineEdit_nowrpm->setText(QString::number(num*100));
}

//ui->comboBox取值
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    int num = ui->comboBox->currentText().toUInt();
    emit signalLPWMenableNum(num);
}

//ui->double spinBox取值
void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    double num = arg1;
    emit signalLSpeedSetNum(num);
}

