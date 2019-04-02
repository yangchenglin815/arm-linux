/****************************************************************************
** Meta object code from reading C++ file 'xtnrddemo.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "xtnrddemo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xtnrddemo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XtNRDDemo[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   11,   10,   10, 0x05,
      70,   58,   10,   10, 0x25,
     101,   95,   10,   10, 0x25,
     122,   10,   10,   10, 0x05,
     163,  139,   10,   10, 0x05,
     212,  207,   10,   10, 0x05,
     247,  238,   10,   10, 0x05,
     275,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     297,   10,   10,   10, 0x08,
     321,  313,   10,   10, 0x08,
     357,  350,   10,   10, 0x08,
     395,  380,   10,   10, 0x08,
     462,  437,   10,   10, 0x08,
     501,  497,   10,   10, 0x08,
     529,  524,   10,   10, 0x08,
     556,   10,   10,   10, 0x08,
     581,  524,   10,   10, 0x08,
     617,  610,   10,   10, 0x08,
     660,  648,   10,   10, 0x08,
     689,   10,   10,   10, 0x08,
     704,   10,   10,   10, 0x08,
     730,   10,   10,   10, 0x08,
     751,   10,   10,   10, 0x08,
     772,   10,   10,   10, 0x08,
     797,   10,   10,   10, 0x08,
     827,  821,   10,   10, 0x08,
     880,  874,   10,   10, 0x08,
     920,   10,   10,   10, 0x08,
     943,   10,   10,   10, 0x08,
     964,   10,   10,   10, 0x08,
     986,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_XtNRDDemo[] = {
    "XtNRDDemo\0\0count,lmsec,rmsec\0"
    "signalBeepStart(int,int,int)\0count,lmsec\0"
    "signalBeepStart(int,int)\0count\0"
    "signalBeepStart(int)\0signalBeepStop()\0"
    "taskname,max,avg,allrec\0"
    "signalInfo(QString,QString,QString,QString)\0"
    "type\0signalKeepTimeUpdate(int)\0taskname\0"
    "signal_gettaskname(QString)\0"
    "signal_showlistform()\0slotOnTimeout()\0"
    "strData\0slotRadiationUpdate(QString)\0"
    "strNbr\0slotNbrUpdate(QString)\0"
    "templ,humidity\0slotTempl_HumidityUpdate(QString,QString)\0"
    "strLongitude,strLatitude\0"
    "slotGpsInfoUpdate(QString,QString)\0"
    "pct\0slotBatteryUpdate(int)\0stat\0"
    "slotChargerConnected(bool)\0"
    "slotLowBatteryShutdown()\0"
    "slotLowBatteryDetected(bool)\0baData\0"
    "slotZigbeeDataRcvd(QByteArray)\0"
    "level,value\0slotRssiLevelUpdate(int,int)\0"
    "slotRssiMiss()\0slotDisplayCTimeRefresh()\0"
    "on_btnTask_clicked()\0slotOnTcpConnected()\0"
    "slotOnTcpSockReadyRead()\0"
    "slotOnTcpDisconnected()\0state\0"
    "slotStateChanged(QAbstractSocket::SocketState)\0"
    "error\0sloterror(QAbstractSocket::SocketError)\0"
    "on_btnExport_clicked()\0on_btnList_clicked()\0"
    "on_resetNet_clicked()\0on_btnInfo_clicked()\0"
};

void XtNRDDemo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        XtNRDDemo *_t = static_cast<XtNRDDemo *>(_o);
        switch (_id) {
        case 0: _t->signalBeepStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->signalBeepStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->signalBeepStart((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signalBeepStop(); break;
        case 4: _t->signalInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 5: _t->signalKeepTimeUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->signal_gettaskname((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->signal_showlistform(); break;
        case 8: _t->slotOnTimeout(); break;
        case 9: _t->slotRadiationUpdate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->slotNbrUpdate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->slotTempl_HumidityUpdate((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 12: _t->slotGpsInfoUpdate((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: _t->slotBatteryUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->slotChargerConnected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->slotLowBatteryShutdown(); break;
        case 16: _t->slotLowBatteryDetected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->slotZigbeeDataRcvd((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 18: _t->slotRssiLevelUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: _t->slotRssiMiss(); break;
        case 20: _t->slotDisplayCTimeRefresh(); break;
        case 21: _t->on_btnTask_clicked(); break;
        case 22: _t->slotOnTcpConnected(); break;
        case 23: _t->slotOnTcpSockReadyRead(); break;
        case 24: _t->slotOnTcpDisconnected(); break;
        case 25: _t->slotStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 26: _t->sloterror((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 27: _t->on_btnExport_clicked(); break;
        case 28: _t->on_btnList_clicked(); break;
        case 29: _t->on_resetNet_clicked(); break;
        case 30: _t->on_btnInfo_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData XtNRDDemo::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject XtNRDDemo::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_XtNRDDemo,
      qt_meta_data_XtNRDDemo, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XtNRDDemo::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XtNRDDemo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XtNRDDemo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XtNRDDemo))
        return static_cast<void*>(const_cast< XtNRDDemo*>(this));
    return QWidget::qt_metacast(_clname);
}

int XtNRDDemo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
    return _id;
}

// SIGNAL 0
void XtNRDDemo::signalBeepStart(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void XtNRDDemo::signalBeepStop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void XtNRDDemo::signalInfo(QString _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void XtNRDDemo::signalKeepTimeUpdate(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void XtNRDDemo::signal_gettaskname(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void XtNRDDemo::signal_showlistform()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}
QT_END_MOC_NAMESPACE
