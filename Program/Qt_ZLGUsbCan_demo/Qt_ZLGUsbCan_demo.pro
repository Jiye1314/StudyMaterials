QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    usbcan_2e_u.cpp \
    usbcan_fd_200u.cpp

HEADERS += \
    mainwindow.h \
    usbcan_2e_u.h \
    usbcan_fd_200u.h \
    zlgcan_x86/canframe.h \
    zlgcan_x86/config.h \
    zlgcan_x86/typedef.h \
    zlgcan_x86/zlgcan.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/zlgcan_x86/ -lzlgcan

INCLUDEPATH += $$PWD/zlgcan_x86
DEPENDPATH += $$PWD/zlgcan_x86

RESOURCES += \
    images.qrc
