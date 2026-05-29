#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("CAN通讯demo");
    w.setWindowIcon(QIcon(":/icon/icon.png"));

    // ====================== 全局按钮样式核心代码 ======================
        QString btnStyle = R"(
            /* 所有QPushButton 通用样式 */
            QPushButton {
                background-color: #409EFF;    /* 背景色 */
                color: white;                 /* 文字颜色 */
                border: none;                 /* 无边框 */
                border-radius: 6px;           /* 圆角 */
                padding: 8px 16px;            /* 内边距 */
                font-size: 16px;              /* 字体大小 */
                font-family: "Microsoft YaHei";
                font-weight: normal;          /* 字体粗细：normal 正常 / bold 加粗 */
            }

            /* 鼠标悬浮 */
            QPushButton:hover {
                background-color: #66B1FF;
            }

            /* 鼠标按下 */
            QPushButton:pressed {
                background-color: #337ECC;
                padding-left: 18px;
                padding-top: 10px;
            }

            /* 不可用状态 */
            QPushButton:disabled {
                background-color: #C0C4CC;
                color: #F5F7FA;
            }
        )";

        // 给整个应用设置样式（全局生效）
        a.setStyleSheet(btnStyle);

    return a.exec();
}
