/****************************************************************************
** Meta object code from reading C++ file 'devbeep.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "devbeep.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'devbeep.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DevBeep[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,    9,    8,    8, 0x0a,
      66,   54,    8,    8, 0x2a,
      95,   89,    8,    8, 0x2a,
     114,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DevBeep[] = {
    "DevBeep\0\0count,lmsec,rmsec\0"
    "slotBeepStart(int,int,int)\0count,lmsec\0"
    "slotBeepStart(int,int)\0count\0"
    "slotBeepStart(int)\0slotBeepStop()\0"
};

void DevBeep::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DevBeep *_t = static_cast<DevBeep *>(_o);
        switch (_id) {
        case 0: _t->slotBeepStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->slotBeepStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slotBeepStart((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotBeepStop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DevBeep::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DevBeep::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DevBeep,
      qt_meta_data_DevBeep, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DevBeep::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DevBeep::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DevBeep::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DevBeep))
        return static_cast<void*>(const_cast< DevBeep*>(this));
    return QThread::qt_metacast(_clname);
}

int DevBeep::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
