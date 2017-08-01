/****************************************************************************
** Meta object code from reading C++ file 'trackingthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dsResult/trackingthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trackingthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_trackingThread_t {
    QByteArrayData data[8];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_trackingThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_trackingThread_t qt_meta_stringdata_trackingThread = {
    {
QT_MOC_LITERAL(0, 0, 14), // "trackingThread"
QT_MOC_LITERAL(1, 15, 9), // "signalDoa"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 3), // "doa"
QT_MOC_LITERAL(4, 30, 17), // "signalParticlePos"
QT_MOC_LITERAL(5, 48, 12), // "particlePos*"
QT_MOC_LITERAL(6, 61, 8), // "posGroup"
QT_MOC_LITERAL(7, 70, 15) // "signalTerminate"

    },
    "trackingThread\0signalDoa\0\0doa\0"
    "signalParticlePos\0particlePos*\0posGroup\0"
    "signalTerminate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_trackingThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,
       7,    0,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Short,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void trackingThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        trackingThread *_t = static_cast<trackingThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalDoa((*reinterpret_cast< short(*)>(_a[1]))); break;
        case 1: _t->signalParticlePos((*reinterpret_cast< particlePos*(*)>(_a[1]))); break;
        case 2: _t->signalTerminate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (trackingThread::*_t)(short );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&trackingThread::signalDoa)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (trackingThread::*_t)(particlePos * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&trackingThread::signalParticlePos)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (trackingThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&trackingThread::signalTerminate)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject trackingThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_trackingThread.data,
      qt_meta_data_trackingThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *trackingThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *trackingThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_trackingThread.stringdata0))
        return static_cast<void*>(const_cast< trackingThread*>(this));
    return QThread::qt_metacast(_clname);
}

int trackingThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void trackingThread::signalDoa(short _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void trackingThread::signalParticlePos(particlePos * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void trackingThread::signalTerminate()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
