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
    QByteArrayData data[22];
    char stringdata0[289];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "signalsSetNum"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "uint8"
QT_MOC_LITERAL(4, 32, 11), // "speedSetNum"
QT_MOC_LITERAL(5, 44, 12), // "PWMenableNum"
QT_MOC_LITERAL(6, 57, 14), // "slotsUpdateNum"
QT_MOC_LITERAL(7, 72, 3), // "num"
QT_MOC_LITERAL(8, 76, 22), // "on_btn_openDev_clicked"
QT_MOC_LITERAL(9, 99, 19), // "on_btn_send_clicked"
QT_MOC_LITERAL(10, 119, 23), // "on_btn_closeDev_clicked"
QT_MOC_LITERAL(11, 143, 16), // "btnSetEnableTrue"
QT_MOC_LITERAL(12, 160, 17), // "btnSetEnableFalse"
QT_MOC_LITERAL(13, 178, 21), // "on_btn_send_2_clicked"
QT_MOC_LITERAL(14, 200, 18), // "on_btn_set_clicked"
QT_MOC_LITERAL(15, 219, 22), // "slotsUpdateTableWidget"
QT_MOC_LITERAL(16, 242, 8), // "uint32_t"
QT_MOC_LITERAL(17, 251, 5), // "canId"
QT_MOC_LITERAL(18, 257, 7), // "uint8_t"
QT_MOC_LITERAL(19, 265, 3), // "dlc"
QT_MOC_LITERAL(20, 269, 4), // "data"
QT_MOC_LITERAL(21, 274, 14) // "initTableForID"

    },
    "MainWindow\0signalsSetNum\0\0uint8\0"
    "speedSetNum\0PWMenableNum\0slotsUpdateNum\0"
    "num\0on_btn_openDev_clicked\0"
    "on_btn_send_clicked\0on_btn_closeDev_clicked\0"
    "btnSetEnableTrue\0btnSetEnableFalse\0"
    "on_btn_send_2_clicked\0on_btn_set_clicked\0"
    "slotsUpdateTableWidget\0uint32_t\0canId\0"
    "uint8_t\0dlc\0data\0initTableForID"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   74,    2, 0x08 /* Private */,
       8,    0,   77,    2, 0x08 /* Private */,
       9,    0,   78,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,
      15,    3,   84,    2, 0x08 /* Private */,
      21,    0,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 18, QMetaType::QByteArray,   17,   19,   20,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalsSetNum((*reinterpret_cast< uint8(*)>(_a[1])),(*reinterpret_cast< uint8(*)>(_a[2]))); break;
        case 1: _t->slotsUpdateNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_btn_openDev_clicked(); break;
        case 3: _t->on_btn_send_clicked(); break;
        case 4: _t->on_btn_closeDev_clicked(); break;
        case 5: _t->btnSetEnableTrue(); break;
        case 6: _t->btnSetEnableFalse(); break;
        case 7: _t->on_btn_send_2_clicked(); break;
        case 8: _t->on_btn_set_clicked(); break;
        case 9: _t->slotsUpdateTableWidget((*reinterpret_cast< uint32_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 10: _t->initTableForID(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(uint8 , uint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalsSetNum)) {
                *result = 0;
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::signalsSetNum(uint8 _t1, uint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
