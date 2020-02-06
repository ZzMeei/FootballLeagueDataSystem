/****************************************************************************
** Meta object code from reading C++ file 'leaguedatawindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FootballLeagueDataSystem/leaguedatawindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'leaguedatawindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Leaguedatawindow_t {
    QByteArrayData data[6];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Leaguedatawindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Leaguedatawindow_t qt_meta_stringdata_Leaguedatawindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Leaguedatawindow"
QT_MOC_LITERAL(1, 17, 20), // "leagueDataWindowBack"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 28), // "teamDataWindowShowAndGetTeam"
QT_MOC_LITERAL(4, 68, 18), // "scheduleWindowShow"
QT_MOC_LITERAL(5, 87, 32) // "playerDataWindowShowAndGetPlayer"

    },
    "Leaguedatawindow\0leagueDataWindowBack\0"
    "\0teamDataWindowShowAndGetTeam\0"
    "scheduleWindowShow\0playerDataWindowShowAndGetPlayer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Leaguedatawindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Leaguedatawindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Leaguedatawindow *_t = static_cast<Leaguedatawindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->leagueDataWindowBack(); break;
        case 1: _t->teamDataWindowShowAndGetTeam(); break;
        case 2: _t->scheduleWindowShow(); break;
        case 3: _t->playerDataWindowShowAndGetPlayer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Leaguedatawindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Leaguedatawindow::leagueDataWindowBack)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Leaguedatawindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Leaguedatawindow::teamDataWindowShowAndGetTeam)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Leaguedatawindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Leaguedatawindow::scheduleWindowShow)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Leaguedatawindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Leaguedatawindow::playerDataWindowShowAndGetPlayer)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Leaguedatawindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Leaguedatawindow.data,
      qt_meta_data_Leaguedatawindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Leaguedatawindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Leaguedatawindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Leaguedatawindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Leaguedatawindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Leaguedatawindow::leagueDataWindowBack()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Leaguedatawindow::teamDataWindowShowAndGetTeam()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Leaguedatawindow::scheduleWindowShow()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Leaguedatawindow::playerDataWindowShowAndGetPlayer()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
