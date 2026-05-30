#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    //ui上的数值
    void signalLSpeedSetNum(int speedSetNum);
    void signalLPWMenableNum(int PWMenableNum);
private slots:
    //更新计数
    void slotsUpdateNum(int num);
    //更新转数显示
    void slotsUpdateRpmNum(int num);

    void on_btn_openDev_clicked();

    void on_btn_send_clicked();

    void on_btn_closeDev_clicked();

    void btnSetEnableTrue();
    void btnSetEnableFalse();

    void on_btn_send_2_clicked();

    // 更新表格显示
    void slotsUpdateTableWidget(int channel,int canId, int dlc, const QByteArray &data);
    //初始化表格
    void initTableForID();


    //ui->comboBox
    void on_comboBox_currentIndexChanged(int index);

    void on_btn_setL_speedSet_clicked();

    void on_lineEdit_data_textEdited(const QString &arg1);

    //连接中断提醒
    void slotsExceptionStatus(int i);

    void on_comboBox_dataFrame_currentIndexChanged(int index);

private:


private:
    Ui::MainWindow *ui;
    USBCAN_FD_200U *usbC_fd_200u;

    // QMap: CAN ID → 接收次数
    QMap<int, int> m_frameCountMap;
};
#endif // MAINWINDOW_H
