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
    QByteArrayData data[16];
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
QT_MOC_LITERAL(5, 56, 8), // "uint32_t"
QT_MOC_LITERAL(6, 65, 5), // "canId"
QT_MOC_LITERAL(7, 71, 7), // "uint8_t"
QT_MOC_LITERAL(8, 79, 3), // "dlc"
QT_MOC_LITERAL(9, 83, 4), // "data"
QT_MOC_LITERAL(10, 88, 27), // "slotsSetSpeedSet1PWMenable1"
QT_MOC_LITERAL(11, 116, 5), // "uint8"
QT_MOC_LITERAL(12, 122, 4), // "num1"
QT_MOC_LITERAL(13, 127, 4), // "num2"
QT_MOC_LITERAL(14, 132, 14), // "onTimerLiftPDO"
QT_MOC_LITERAL(15, 147, 18) // "onTimerTractionPDO"

    },
    "USBCAN_FD_200U\0signalsSendNum\0\0num\0"
    "signalsReceivedFrame\0uint32_t\0canId\0"
    "uint8_t\0dlc\0data\0slotsSetSpeedSet1PWMenable1\0"
    "uint8\0num1\0num2\0onTimerLiftPDO\0"
    "onTimerTractionPDO"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_USBCAN_FD_200U[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    3,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,   49,    2, 0x0a /* Public */,
      14,    0,   54,    2, 0x0a /* Public */,
      15,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7, QMetaType::QByteArray,    6,    8,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 11,   12,   13,
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
        case 1: _t->signalsReceivedFrame((*reinterpret_cast< uint32_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 2: _t->slotsSetSpeedSet1PWMenable1((*reinterpret_cast< uint8(*)>(_a[1])),(*reinterpret_cast< uint8(*)>(_a[2]))); break;
        case 3: _t->onTimerLiftPDO(); break;
        case 4: _t->onTimerTractionPDO(); break;
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
            using _t = void (USBCAN_FD_200U::*)(uint32_t , uint8_t , const QByteArray & );
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
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
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
void USBCAN_FD_200U::signalsReceivedFrame(uint32_t _t1, uint8_t _t2, const QByteArray & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
