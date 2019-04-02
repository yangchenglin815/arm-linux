/****************************************************************************
** Meta object code from reading C++ file 'clistform.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "clistform.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clistform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CListForm[] = {

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
      35,   11,   10,   10, 0x08,
      78,   10,   10,   10, 0x08,
     110,  101,   10,   10, 0x08,
     136,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CListForm[] = {
    "CListForm\0\0taskname,max,avg,allrec\0"
    "slot_info(QString,QString,QString,QString)\0"
    "on_btnReturn_clicked()\0taskname\0"
    "slot_gettaskname(QString)\0"
    "on_btnUpdate_clicked()\0"
};

void CListForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CListForm *_t = static_cast<CListForm *>(_o);
        switch (_id) {
        case 0: _t->slot_info((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: _t->on_btnReturn_clicked(); break;
        case 2: _t->slot_gettaskname((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->on_btnUpdate_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CListForm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CListForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CListForm,
      qt_meta_data_CListForm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CListForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CListForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CListForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CListForm))
        return static_cast<void*>(const_cast< CListForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int CListForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
