/****************************************************************************
** Meta object code from reading C++ file 'devbattery.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "devbattery.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'devbattery.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DevBattery[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,
      46,   41,   11,   11, 0x05,
      75,   11,   11,   11, 0x05,
     102,   41,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DevBattery[] = {
    "DevBattery\0\0pct\0signalBatteryUpdate(int)\0"
    "stat\0signalChargerConnected(bool)\0"
    "signalLowBatteryShutdown()\0"
    "signalLowBatteryDetected(bool)\0"
};

void DevBattery::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DevBattery *_t = static_cast<DevBattery *>(_o);
        switch (_id) {
        case 0: _t->signalBatteryUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalChargerConnected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->signalLowBatteryShutdown(); break;
        case 3: _t->signalLowBatteryDetected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DevBattery::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DevBattery::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DevBattery,
      qt_meta_data_DevBattery, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DevBattery::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DevBattery::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DevBattery::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DevBattery))
        return static_cast<void*>(const_cast< DevBattery*>(this));
    return QThread::qt_metacast(_clname);
}

int DevBattery::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DevBattery::signalBatteryUpdate(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DevBattery::signalChargerConnected(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DevBattery::signalLowBatteryShutdown()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void DevBattery::signalLowBatteryDetected(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
