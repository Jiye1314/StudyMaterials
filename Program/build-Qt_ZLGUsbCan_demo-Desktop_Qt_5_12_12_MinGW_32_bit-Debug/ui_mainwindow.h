/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btn_openDev;
    QPushButton *btn_send;
    QPushButton *btn_closeDev;
    QPushButton *btn_send_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(535, 469);
        QFont font;
        font.setPointSize(12);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btn_openDev = new QPushButton(centralwidget);
        btn_openDev->setObjectName(QString::fromUtf8("btn_openDev"));
        btn_openDev->setGeometry(QRect(190, 20, 141, 61));
        btn_send = new QPushButton(centralwidget);
        btn_send->setObjectName(QString::fromUtf8("btn_send"));
        btn_send->setGeometry(QRect(190, 110, 141, 61));
        btn_closeDev = new QPushButton(centralwidget);
        btn_closeDev->setObjectName(QString::fromUtf8("btn_closeDev"));
        btn_closeDev->setGeometry(QRect(190, 290, 141, 61));
        btn_send_2 = new QPushButton(centralwidget);
        btn_send_2->setObjectName(QString::fromUtf8("btn_send_2"));
        btn_send_2->setGeometry(QRect(190, 200, 141, 61));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 535, 33));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_openDev->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        btn_send->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
        btn_closeDev->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\350\256\276\345\244\207", nullptr));
        btn_send_2->setText(QApplication::translate("MainWindow", "\346\211\213\345\212\250\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
