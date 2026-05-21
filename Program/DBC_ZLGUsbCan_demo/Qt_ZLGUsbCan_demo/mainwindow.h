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

signals:
    //数值
    void signalsSetNum(uint8 speedSetNum,uint8 PWMenableNum);

private slots:
    //更新计数
    void slotsUpdateNum(int num);

    void on_btn_openDev_clicked();

    void on_btn_send_clicked();

    void on_btn_closeDev_clicked();

    void btnSetEnableTrue();
    void btnSetEnableFalse();

    void on_btn_send_2_clicked();

    void on_btn_set_clicked();

    // 更新表格显示
    void slotsUpdateTableWidget(uint32_t canId, uint8_t dlc, const QByteArray &data);
    void initTableForID();
private:


private:
    Ui::MainWindow *ui;
    USBCAN_2E_U *usbC_2e_u;
    USBCAN_FD_200U *usbC_fd_200u;

    // QMap: CAN ID → 接收次数
    QMap<uint32_t, int> m_frameCountMap;
};
#endif // MAINWINDOW_H
