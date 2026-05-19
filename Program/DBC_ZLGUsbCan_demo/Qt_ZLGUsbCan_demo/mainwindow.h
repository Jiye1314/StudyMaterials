#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "zlgDeviceType/usbcan_2e_u.h"
#include "zlgDeviceType/usbcan_fd_200u.h"
#include <QMainWindow>
#include <QDebug>
#include "zlgcan.h"
#include <QEventLoop>
#include <QTimer>
#include <QThread>
#include <QDateTime>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_openDev_clicked();

    void on_btn_send_clicked();

    void on_btn_closeDev_clicked();

    void btnSetEnableTrue();
    void btnSetEnableFalse();

    void on_btn_send_2_clicked();

private:


private:
    Ui::MainWindow *ui;
    USBCAN_2E_U *usbC_2e_u;
    USBCAN_FD_200U *usbC_fd_200u;
};
#endif // MAINWINDOW_H
