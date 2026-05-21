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
    connect(this,&MainWindow::signalsSetNum,usbC_fd_200u,&USBCAN_FD_200U::slotsSetSpeedSet1PWMenable1);
    qDebug()<<"当前时间："<<QDateTime::currentDateTime();

    // CAN 帧 → 表格刷新
    connect(usbC_fd_200u, &USBCAN_FD_200U::signalsReceivedFrame,this, &MainWindow::slotsUpdateTableWidget, Qt::QueuedConnection);
    connect(this, &MainWindow::signalsSetNum,usbC_fd_200u, &USBCAN_FD_200U::slotsSetSpeedSet1PWMenable1);
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


    ui->btn_openDev->setEnabled(false);
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
}

void MainWindow::btnSetEnableFalse()
{
    ui->btn_openDev->setEnabled(true);
    ui->btn_closeDev->setEnabled(false);
    ui->btn_send->setEnabled(false);
    ui->btn_send_2->setEnabled(false);
}


void MainWindow::on_btn_send_2_clicked()
{

    usbC_fd_200u->Send_fd_200u();

}

//设置按钮
void MainWindow::on_btn_set_clicked()
{
    emit signalsSetNum(ui->spinBox->value(),ui->comboBox->currentText().toUInt());
}

// 收到帧时更新表格（只处理 0x0182）
void MainWindow::slotsUpdateTableWidget(uint32_t canId, uint8_t dlc, const QByteArray &data)
{
    // 只显示 0x0182 的帧
    if (canId != 0x0182 && canId != 0x0081) return;

    m_frameCountMap[canId]++;

    int row;
    if (canId == 0x0182) row = 0;
    else if (canId == 0x0081) row = 1;
    else return;

    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(dlc)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString(data)));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(m_frameCountMap[canId])));
}


void MainWindow::initTableForID()
{
    ui->tableWidget->setRowCount(2); // 2 行
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

    // 预填固定信息
    // 第 0 行：LiftPDO1 (0x0182)
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("1"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("0x0182"));
    m_frameCountMap[0x0182] = 0;

    // 第 1 行：TractionPDOF (0x0081)
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("1"));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem("0x0081"));
    m_frameCountMap[0x0081] = 0;
}

//更新计数
void MainWindow::slotsUpdateNum(int num)
{
    ui->lineEdit_num->setText(QString::number(num));
}

