/****************************************************************************
** Meta object code from reading C++ file 'devusbserialmonitor.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "devusbserialmonitor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'devusbserialmonitor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DevUsbSerialMonitor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   21,   20,   20, 0x05,
      59,   21,   20,   20, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DevUsbSerialMonitor[] = {
    "DevUsbSerialMonitor\0\0devName\0"
    "signalDeviceAttached(QString)\0"
    "signalDeviceDisconnected(QString)\0"
};

void DevUsbSerialMonitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DevUsbSerialMonitor *_t = static_cast<DevUsbSerialMonitor *>(_o);
        switch (_id) {
        case 0: _t->signalDeviceAttached((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->signalDeviceDisconnected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DevUsbSerialMonitor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DevUsbSerialMonitor::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DevUsbSerialMonitor,
      qt_meta_data_DevUsbSerialMonitor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DevUsbSerialMonitor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DevUsbSerialMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DevUsbSerialMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DevUsbSerialMonitor))
        return static_cast<void*>(const_cast< DevUsbSerialMonitor*>(this));
    return QThread::qt_metacast(_clname);
}

int DevUsbSerialMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DevUsbSerialMonitor::signalDeviceAttached(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DevUsbSerialMonitor::signalDeviceDisconnected(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
