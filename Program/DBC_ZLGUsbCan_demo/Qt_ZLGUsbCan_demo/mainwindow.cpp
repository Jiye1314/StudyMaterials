#include "mainwindow.h"
#include "ui_mainwindow.h"

//#define USBCAN_2E_U_def
#define USBCAN_FD_200U_def

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    btnSetEnableFalse();
#ifdef USBCAN_FD_200U_def
    usbC_fd_200u = new USBCAN_FD_200U;
#elif defined USBCAN_2E_U_def
    usbC_2e_u = new USBCAN_2E_U;
#endif
    //connect(usbC_fd_200u,&USBCAN_FD_200U::signalChangebtn_fd_200u,this,&MainWindow::btnSetEnableTrue);
    qDebug()<<"当前时间："<<QDateTime::currentDateTime();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_openDev_clicked()
{
#ifdef USBCAN_FD_200U_def
    if(usbC_fd_200u->openDevice_fd_200u())
    {
        btnSetEnableTrue();
    }

#elif defined USBCAN_2E_U_def
    if(usbC_2e_u->openDevice())
    {
        btnSetEnableTrue();
    }
#endif
    ui->btn_openDev->setEnabled(false);
}


void MainWindow::on_btn_send_clicked()
{
#ifdef USBCAN_FD_200U_def
    if(usbC_fd_200u->timerSend_fd_200u())
    {
        ui->btn_send->setText("关闭定时发送");
    }else
    {
        ui->btn_send->setText("开启定时发送");
    }
#elif defined USBCAN_2E_U_def
    if(usbC_2e_u->timerSend())
    {
        ui->btn_send->setText("关闭定时发送");
    }else
    {
        ui->btn_send->setText("开启定时发送");
    }

#endif
}


void MainWindow::on_btn_closeDev_clicked()
{
#ifdef USBCAN_FD_200U_def
    if(usbC_fd_200u->closeDevice_fd_200u())
    {
        btnSetEnableFalse();
    }

#elif defined USBCAN_2E_U_def
    if(usbC_2e_u->closeDevice())
    {
        btnSetEnableFalse();
    }
#endif
    ui->btn_openDev->setEnabled(true);
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
#ifdef USBCAN_FD_200U_def
    usbC_fd_200u->Send_fd_200u();
#elif defined USBCAN_2E_U_def
    usbC_2e_u->send();
#endif
}

