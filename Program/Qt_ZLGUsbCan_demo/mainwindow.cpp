#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    btnSetEnableFalse();
    usbC_fd_200u = new USBCAN_FD_200U;
    usbC_2e_u = new USBCAN_2E_U;
    //connect(usbC_fd_200u,&USBCAN_FD_200U::signalChangebtn_fd_200u,this,&MainWindow::btnSetEnableTrue);
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
    }
}


void MainWindow::on_btn_send_clicked()
{
    if(usbC_fd_200u->timerSend_fd_200u())
    {
        ui->btn_send->setText("关闭");
    }else
    {
        ui->btn_send->setText("开启");
    }
}


void MainWindow::on_btn_closeDev_clicked()
{
    if(usbC_fd_200u->closeDevice_fd_200u())
    {
        btnSetEnableFalse();
    }

}

void MainWindow::btnSetEnableTrue()
{
    ui->btn_closeDev->setEnabled(true);
    ui->btn_send->setEnabled(true);
    ui->btn_send_2->setEnabled(true);
}

void MainWindow::btnSetEnableFalse()
{
    ui->btn_closeDev->setEnabled(false);
    ui->btn_send->setEnabled(false);
    ui->btn_send_2->setEnabled(false);
}


void MainWindow::on_btn_send_2_clicked()
{
    usbC_fd_200u->Send_fd_200u();
}

