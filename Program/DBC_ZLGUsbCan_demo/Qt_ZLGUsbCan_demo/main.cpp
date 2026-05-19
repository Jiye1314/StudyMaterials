#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("CAN通讯demo");
    w.setWindowIcon(QIcon(":/icon/icon.png"));
    return a.exec();
}
