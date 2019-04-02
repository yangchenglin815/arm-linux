/****************************************************************************
** Meta object code from reading C++ file 'devbacklight.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "devbacklight.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'devbacklight.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DevBacklight[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DevBacklight[] = {
    "DevBacklight\0\0type\0slotKeepTimeUpdate(int)\0"
};

void DevBacklight::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DevBacklight *_t = static_cast<DevBacklight *>(_o);
        switch (_id) {
        case 0: _t->slotKeepTimeUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DevBacklight::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DevBacklight::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DevBacklight,
      qt_meta_data_DevBacklight, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DevBacklight::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DevBacklight::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DevBacklight::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DevBacklight))
        return static_cast<void*>(const_cast< DevBacklight*>(this));
    return QObject::qt_metacast(_clname);
}

int DevBacklight::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
