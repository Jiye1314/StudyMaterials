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
    QPushButton *bt_getDeviceInf;
    QPushButton *bt_closeDev;
    QPushButton *bt_send;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(499, 403);
        QFont font;
        font.setPointSize(12);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        bt_getDeviceInf = new QPushButton(centralwidget);
        bt_getDeviceInf->setObjectName(QString::fromUtf8("bt_getDeviceInf"));
        bt_getDeviceInf->setGeometry(QRect(160, 60, 141, 51));
        bt_closeDev = new QPushButton(centralwidget);
        bt_closeDev->setObjectName(QString::fromUtf8("bt_closeDev"));
        bt_closeDev->setGeometry(QRect(170, 220, 131, 51));
        bt_send = new QPushButton(centralwidget);
        bt_send->setObjectName(QString::fromUtf8("bt_send"));
        bt_send->setGeometry(QRect(170, 140, 131, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 499, 33));
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
        bt_getDeviceInf->setText(QApplication::translate("MainWindow", "\350\257\273\345\217\226\350\256\276\345\244\207\344\277\241\346\201\257", nullptr));
        bt_closeDev->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\350\256\276\345\244\207", nullptr));
        bt_send->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
