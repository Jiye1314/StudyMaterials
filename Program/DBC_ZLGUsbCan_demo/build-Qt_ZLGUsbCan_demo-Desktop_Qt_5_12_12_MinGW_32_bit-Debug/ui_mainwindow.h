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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_test;
    QLabel *label_test_2;
    QComboBox *comboBox_channel;
    QLabel *label_test_3;
    QComboBox *comboBox_typeFrame;
    QLabel *label_test_4;
    QComboBox *comboBox_dataFrame;
    QLabel *label_test_5;
    QComboBox *comboBox_dataLength;
    QLabel *label_test_6;
    QLineEdit *lineEdit_data;
    QLabel *label_test_7;
    QLineEdit *lineEdit_frameID;
    QPushButton *btn_send_2;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_num;
    QSpacerItem *horizontalSpacer;
    QLabel *label_L_PWMenable1;
    QLineEdit *lineEdit_nowrpm;
    QComboBox *comboBox;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label;
    QPushButton *btn_closeDev;
    QPushButton *btn_openDev;
    QPushButton *btn_send;
    QLabel *label_2;
    QPushButton *btn_setL_speedSet;
    QSpinBox *spinBox_KGRT_speedReq;
    QPushButton *btn_setKGRT_speedReq;
    QLabel *label_L_speedSet1_2;
    QLabel *label_L_speedSet1;
    QSpinBox *spinBox;
    QMenuBar *menubar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1105, 626);
        QFont font;
        font.setPointSize(12);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem9);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(20, 20, 811, 361));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(840, 10, 251, 561));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_test = new QLabel(layoutWidget);
        label_test->setObjectName(QString::fromUtf8("label_test"));

        verticalLayout->addWidget(label_test);

        label_test_2 = new QLabel(layoutWidget);
        label_test_2->setObjectName(QString::fromUtf8("label_test_2"));

        verticalLayout->addWidget(label_test_2);

        comboBox_channel = new QComboBox(layoutWidget);
        comboBox_channel->addItem(QString());
        comboBox_channel->setObjectName(QString::fromUtf8("comboBox_channel"));

        verticalLayout->addWidget(comboBox_channel);

        label_test_3 = new QLabel(layoutWidget);
        label_test_3->setObjectName(QString::fromUtf8("label_test_3"));

        verticalLayout->addWidget(label_test_3);

        comboBox_typeFrame = new QComboBox(layoutWidget);
        comboBox_typeFrame->addItem(QString());
        comboBox_typeFrame->setObjectName(QString::fromUtf8("comboBox_typeFrame"));

        verticalLayout->addWidget(comboBox_typeFrame);

        label_test_4 = new QLabel(layoutWidget);
        label_test_4->setObjectName(QString::fromUtf8("label_test_4"));

        verticalLayout->addWidget(label_test_4);

        comboBox_dataFrame = new QComboBox(layoutWidget);
        comboBox_dataFrame->addItem(QString());
        comboBox_dataFrame->addItem(QString());
        comboBox_dataFrame->setObjectName(QString::fromUtf8("comboBox_dataFrame"));

        verticalLayout->addWidget(comboBox_dataFrame);

        label_test_5 = new QLabel(layoutWidget);
        label_test_5->setObjectName(QString::fromUtf8("label_test_5"));

        verticalLayout->addWidget(label_test_5);

        comboBox_dataLength = new QComboBox(layoutWidget);
        comboBox_dataLength->addItem(QString());
        comboBox_dataLength->addItem(QString());
        comboBox_dataLength->addItem(QString());
        comboBox_dataLength->addItem(QString());
        comboBox_dataLength->addItem(QString());
        comboBox_dataLength->addItem(QString());
        comboBox_dataLength->addItem(QString());
        comboBox_dataLength->addItem(QString());
        comboBox_dataLength->setObjectName(QString::fromUtf8("comboBox_dataLength"));

        verticalLayout->addWidget(comboBox_dataLength);

        label_test_6 = new QLabel(layoutWidget);
        label_test_6->setObjectName(QString::fromUtf8("label_test_6"));

        verticalLayout->addWidget(label_test_6);

        lineEdit_data = new QLineEdit(layoutWidget);
        lineEdit_data->setObjectName(QString::fromUtf8("lineEdit_data"));
        lineEdit_data->setMaxLength(23);
        lineEdit_data->setCursorPosition(2);

        verticalLayout->addWidget(lineEdit_data);

        label_test_7 = new QLabel(layoutWidget);
        label_test_7->setObjectName(QString::fromUtf8("label_test_7"));

        verticalLayout->addWidget(label_test_7);

        lineEdit_frameID = new QLineEdit(layoutWidget);
        lineEdit_frameID->setObjectName(QString::fromUtf8("lineEdit_frameID"));
        lineEdit_frameID->setMaxLength(3);
        lineEdit_frameID->setCursorPosition(2);

        verticalLayout->addWidget(lineEdit_frameID);

        btn_send_2 = new QPushButton(layoutWidget);
        btn_send_2->setObjectName(QString::fromUtf8("btn_send_2"));

        verticalLayout->addWidget(btn_send_2);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(22, 392, 811, 191));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_num = new QLineEdit(layoutWidget1);
        lineEdit_num->setObjectName(QString::fromUtf8("lineEdit_num"));
        lineEdit_num->setEnabled(false);

        gridLayout->addWidget(lineEdit_num, 0, 9, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 5, 1, 1);

        label_L_PWMenable1 = new QLabel(layoutWidget1);
        label_L_PWMenable1->setObjectName(QString::fromUtf8("label_L_PWMenable1"));

        gridLayout->addWidget(label_L_PWMenable1, 1, 6, 1, 4);

        lineEdit_nowrpm = new QLineEdit(layoutWidget1);
        lineEdit_nowrpm->setObjectName(QString::fromUtf8("lineEdit_nowrpm"));
        lineEdit_nowrpm->setEnabled(false);

        gridLayout->addWidget(lineEdit_nowrpm, 2, 2, 1, 2);

        comboBox = new QComboBox(layoutWidget1);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 1, 10, 1, 2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 2);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 4, 1, 1);

        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 7, 1, 2);

        btn_closeDev = new QPushButton(layoutWidget1);
        btn_closeDev->setObjectName(QString::fromUtf8("btn_closeDev"));

        gridLayout->addWidget(btn_closeDev, 0, 4, 1, 1);

        btn_openDev = new QPushButton(layoutWidget1);
        btn_openDev->setObjectName(QString::fromUtf8("btn_openDev"));

        gridLayout->addWidget(btn_openDev, 0, 0, 1, 1);

        btn_send = new QPushButton(layoutWidget1);
        btn_send->setObjectName(QString::fromUtf8("btn_send"));

        gridLayout->addWidget(btn_send, 0, 1, 1, 3);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 11, 1, 1);

        btn_setL_speedSet = new QPushButton(layoutWidget1);
        btn_setL_speedSet->setObjectName(QString::fromUtf8("btn_setL_speedSet"));

        gridLayout->addWidget(btn_setL_speedSet, 1, 4, 1, 1);

        spinBox_KGRT_speedReq = new QSpinBox(layoutWidget1);
        spinBox_KGRT_speedReq->setObjectName(QString::fromUtf8("spinBox_KGRT_speedReq"));
        spinBox_KGRT_speedReq->setMaximum(10000);
        spinBox_KGRT_speedReq->setSingleStep(50);

        gridLayout->addWidget(spinBox_KGRT_speedReq, 2, 10, 1, 1);

        btn_setKGRT_speedReq = new QPushButton(layoutWidget1);
        btn_setKGRT_speedReq->setObjectName(QString::fromUtf8("btn_setKGRT_speedReq"));

        gridLayout->addWidget(btn_setKGRT_speedReq, 2, 11, 1, 1);

        label_L_speedSet1_2 = new QLabel(layoutWidget1);
        label_L_speedSet1_2->setObjectName(QString::fromUtf8("label_L_speedSet1_2"));

        gridLayout->addWidget(label_L_speedSet1_2, 2, 5, 1, 5);

        label_L_speedSet1 = new QLabel(layoutWidget1);
        label_L_speedSet1->setObjectName(QString::fromUtf8("label_L_speedSet1"));

        gridLayout->addWidget(label_L_speedSet1, 1, 0, 1, 2);

        spinBox = new QSpinBox(layoutWidget1);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximum(10000);
        spinBox->setSingleStep(10);

        gridLayout->addWidget(spinBox, 1, 3, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1105, 33));
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\346\212\245\346\226\207ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\346\212\245\346\226\207\351\225\277\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\346\254\241\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "5", nullptr));
        label_test->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\265\213\350\257\225\346\225\260\346\215\256\357\274\210\344\270\245\347\246\201\344\271\261\345\217\221\357\274\211", nullptr));
        label_test_2->setText(QApplication::translate("MainWindow", "\351\200\232\351\201\223\357\274\232", nullptr));
        comboBox_channel->setItemText(0, QApplication::translate("MainWindow", "0\357\274\210\351\273\230\350\256\244\357\274\211", nullptr));

        label_test_3->setText(QApplication::translate("MainWindow", "\345\270\247\347\261\273\345\236\213\357\274\232", nullptr));
        comboBox_typeFrame->setItemText(0, QApplication::translate("MainWindow", "\346\240\207\345\207\206\345\270\247 CAN\357\274\210\351\273\230\350\256\244\357\274\211", nullptr));

        label_test_4->setText(QApplication::translate("MainWindow", "\345\270\247\346\240\274\345\274\217\357\274\232", nullptr));
        comboBox_dataFrame->setItemText(0, QApplication::translate("MainWindow", "\346\225\260\346\215\256\345\270\247\357\274\210\351\273\230\350\256\244\357\274\211", nullptr));
        comboBox_dataFrame->setItemText(1, QApplication::translate("MainWindow", "\346\211\251\345\261\225\345\270\247", nullptr));

        label_test_5->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\351\225\277\345\272\246:", nullptr));
        comboBox_dataLength->setItemText(0, QApplication::translate("MainWindow", "1\357\274\210\351\273\230\350\256\244\357\274\211", nullptr));
        comboBox_dataLength->setItemText(1, QApplication::translate("MainWindow", "2", nullptr));
        comboBox_dataLength->setItemText(2, QApplication::translate("MainWindow", "3", nullptr));
        comboBox_dataLength->setItemText(3, QApplication::translate("MainWindow", "4", nullptr));
        comboBox_dataLength->setItemText(4, QApplication::translate("MainWindow", "5", nullptr));
        comboBox_dataLength->setItemText(5, QApplication::translate("MainWindow", "6", nullptr));
        comboBox_dataLength->setItemText(6, QApplication::translate("MainWindow", "7", nullptr));
        comboBox_dataLength->setItemText(7, QApplication::translate("MainWindow", "8", nullptr));

        label_test_6->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\357\274\2320x", nullptr));
        lineEdit_data->setText(QApplication::translate("MainWindow", "00", nullptr));
        lineEdit_data->setPlaceholderText(QApplication::translate("MainWindow", "00", nullptr));
        label_test_7->setText(QApplication::translate("MainWindow", "\345\270\247ID\357\274\2320x", nullptr));
        lineEdit_frameID->setText(QApplication::translate("MainWindow", "80", nullptr));
        lineEdit_frameID->setPlaceholderText(QApplication::translate("MainWindow", "80", nullptr));
        btn_send_2->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\265\213\350\257\225\346\225\260\346\215\256", nullptr));
        lineEdit_num->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_L_PWMenable1->setText(QApplication::translate("MainWindow", "L-PWMenable1\357\274\232", nullptr));
        lineEdit_nowrpm->setText(QApplication::translate("MainWindow", "0", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));

        label_3->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\350\256\276\347\275\256\350\275\254\346\225\260\344\270\272\357\274\232", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "rpm", nullptr));
        label->setText(QApplication::translate("MainWindow", "\345\205\261\346\216\245\346\224\266\357\274\232", nullptr));
        btn_closeDev->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\350\256\276\345\244\207", nullptr));
        btn_openDev->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        btn_send->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\346\254\241", nullptr));
        btn_setL_speedSet->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\350\275\254\351\200\237", nullptr));
        btn_setKGRT_speedReq->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\350\275\254\351\200\237", nullptr));
        label_L_speedSet1_2->setText(QApplication::translate("MainWindow", "KGRT-speedReq(\350\275\254\351\200\237)\357\274\232", nullptr));
        label_L_speedSet1->setText(QApplication::translate("MainWindow", "L-speedSet1\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
