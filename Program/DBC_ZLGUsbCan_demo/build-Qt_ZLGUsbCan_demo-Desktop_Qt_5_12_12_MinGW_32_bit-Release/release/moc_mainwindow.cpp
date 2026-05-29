/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt_ZLGUsbCan_demo/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[27];
    char stringdata0[419];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "signalLSpeedSetNum"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 11), // "speedSetNum"
QT_MOC_LITERAL(4, 43, 19), // "signalLPWMenableNum"
QT_MOC_LITERAL(5, 63, 12), // "PWMenableNum"
QT_MOC_LITERAL(6, 76, 14), // "slotsUpdateNum"
QT_MOC_LITERAL(7, 91, 3), // "num"
QT_MOC_LITERAL(8, 95, 17), // "slotsUpdateRpmNum"
QT_MOC_LITERAL(9, 113, 22), // "on_btn_openDev_clicked"
QT_MOC_LITERAL(10, 136, 19), // "on_btn_send_clicked"
QT_MOC_LITERAL(11, 156, 23), // "on_btn_closeDev_clicked"
QT_MOC_LITERAL(12, 180, 16), // "btnSetEnableTrue"
QT_MOC_LITERAL(13, 197, 17), // "btnSetEnableFalse"
QT_MOC_LITERAL(14, 215, 21), // "on_btn_send_2_clicked"
QT_MOC_LITERAL(15, 237, 22), // "slotsUpdateTableWidget"
QT_MOC_LITERAL(16, 260, 7), // "channel"
QT_MOC_LITERAL(17, 268, 5), // "canId"
QT_MOC_LITERAL(18, 274, 3), // "dlc"
QT_MOC_LITERAL(19, 278, 4), // "data"
QT_MOC_LITERAL(20, 283, 14), // "initTableForID"
QT_MOC_LITERAL(21, 298, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(22, 330, 5), // "index"
QT_MOC_LITERAL(23, 336, 28), // "on_btn_setL_speedSet_clicked"
QT_MOC_LITERAL(24, 365, 27), // "on_lineEdit_data_textEdited"
QT_MOC_LITERAL(25, 393, 4), // "arg1"
QT_MOC_LITERAL(26, 398, 20) // "slotsExceptionStatus"

    },
    "MainWindow\0signalLSpeedSetNum\0\0"
    "speedSetNum\0signalLPWMenableNum\0"
    "PWMenableNum\0slotsUpdateNum\0num\0"
    "slotsUpdateRpmNum\0on_btn_openDev_clicked\0"
    "on_btn_send_clicked\0on_btn_closeDev_clicked\0"
    "btnSetEnableTrue\0btnSetEnableFalse\0"
    "on_btn_send_2_clicked\0slotsUpdateTableWidget\0"
    "channel\0canId\0dlc\0data\0initTableForID\0"
    "on_comboBox_currentIndexChanged\0index\0"
    "on_btn_setL_speedSet_clicked\0"
    "on_lineEdit_data_textEdited\0arg1\0"
    "slotsExceptionStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,  100,    2, 0x08 /* Private */,
       8,    1,  103,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    4,  112,    2, 0x08 /* Private */,
      20,    0,  121,    2, 0x08 /* Private */,
      21,    1,  122,    2, 0x08 /* Private */,
      23,    0,  125,    2, 0x08 /* Private */,
      24,    1,  126,    2, 0x08 /* Private */,
      26,    0,  129,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QByteArray,   16,   17,   18,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalLSpeedSetNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalLPWMenableNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slotsUpdateNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotsUpdateRpmNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_btn_openDev_clicked(); break;
        case 5: _t->on_btn_send_clicked(); break;
        case 6: _t->on_btn_closeDev_clicked(); break;
        case 7: _t->btnSetEnableTrue(); break;
        case 8: _t->btnSetEnableFalse(); break;
        case 9: _t->on_btn_send_2_clicked(); break;
        case 10: _t->slotsUpdateTableWidget((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QByteArray(*)>(_a[4]))); break;
        case 11: _t->initTableForID(); break;
        case 12: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_btn_setL_speedSet_clicked(); break;
        case 14: _t->on_lineEdit_data_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->slotsExceptionStatus(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalLSpeedSetNum)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalLPWMenableNum)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::signalLSpeedSetNum(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::signalLPWMenableNum(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
