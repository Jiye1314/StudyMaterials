/****************************************************************************
** Meta object code from reading C++ file 'usbcan_fd_200u.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt_ZLGUsbCan_demo/zlgDeviceType/usbcan_fd_200u.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usbcan_fd_200u.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_USBCAN_FD_200U_t {
    QByteArrayData data[14];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_USBCAN_FD_200U_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_USBCAN_FD_200U_t qt_meta_stringdata_USBCAN_FD_200U = {
    {
QT_MOC_LITERAL(0, 0, 14), // "USBCAN_FD_200U"
QT_MOC_LITERAL(1, 15, 14), // "signalsSendNum"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 3), // "num"
QT_MOC_LITERAL(4, 35, 20), // "signalsReceivedFrame"
QT_MOC_LITERAL(5, 56, 7), // "channel"
QT_MOC_LITERAL(6, 64, 5), // "canId"
QT_MOC_LITERAL(7, 70, 3), // "dlc"
QT_MOC_LITERAL(8, 74, 4), // "data"
QT_MOC_LITERAL(9, 79, 18), // "slotsSetLSpeedSet1"
QT_MOC_LITERAL(10, 98, 19), // "slotsSetLPWMenable1"
QT_MOC_LITERAL(11, 118, 14), // "onTimerLiftPDO"
QT_MOC_LITERAL(12, 133, 18), // "onTimerTractionPDO"
QT_MOC_LITERAL(13, 152, 13) // "onTimerStatus"

    },
    "USBCAN_FD_200U\0signalsSendNum\0\0num\0"
    "signalsReceivedFrame\0channel\0canId\0"
    "dlc\0data\0slotsSetLSpeedSet1\0"
    "slotsSetLPWMenable1\0onTimerLiftPDO\0"
    "onTimerTractionPDO\0onTimerStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_USBCAN_FD_200U[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    4,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   61,    2, 0x0a /* Public */,
      10,    1,   64,    2, 0x0a /* Public */,
      11,    0,   67,    2, 0x0a /* Public */,
      12,    0,   68,    2, 0x0a /* Public */,
      13,    0,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QByteArray,    5,    6,    7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void USBCAN_FD_200U::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<USBCAN_FD_200U *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalsSendNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalsReceivedFrame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QByteArray(*)>(_a[4]))); break;
        case 2: _t->slotsSetLSpeedSet1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->slotsSetLPWMenable1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onTimerLiftPDO(); break;
        case 5: _t->onTimerTractionPDO(); break;
        case 6: _t->onTimerStatus(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (USBCAN_FD_200U::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&USBCAN_FD_200U::signalsSendNum)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (USBCAN_FD_200U::*)(int , int , int , const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&USBCAN_FD_200U::signalsReceivedFrame)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject USBCAN_FD_200U::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_USBCAN_FD_200U.data,
    qt_meta_data_USBCAN_FD_200U,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *USBCAN_FD_200U::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *USBCAN_FD_200U::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_USBCAN_FD_200U.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int USBCAN_FD_200U::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void USBCAN_FD_200U::signalsSendNum(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void USBCAN_FD_200U::signalsReceivedFrame(int _t1, int _t2, int _t3, const QByteArray & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
