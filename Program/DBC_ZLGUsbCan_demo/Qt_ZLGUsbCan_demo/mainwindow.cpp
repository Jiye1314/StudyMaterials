#include "mainwindow.h"
#include "ui_mainwindow.h"

#define USBCAN_FD_200U_def

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //隐藏手动发送按钮
    //ui->btn_send_2->hide();

    btnSetEnableFalse();

    usbC_fd_200u = new USBCAN_FD_200U;

    qDebug()<<"当前时间："<<QDateTime::currentDateTime();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_openDev_clicked()
{

    if(usbC_fd_200u->openDevice_fd_200u())
    {
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

