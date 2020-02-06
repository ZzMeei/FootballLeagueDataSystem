/****************************************************************************
** Meta object code from reading C++ file 'adminverifywindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FootballLeagueDataSystem/adminverifywindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adminverifywindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_adminverifywindow_t {
    QByteArrayData data[4];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_adminverifywindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_adminverifywindow_t qt_meta_stringdata_adminverifywindow = {
    {
QT_MOC_LITERAL(0, 0, 17), // "adminverifywindow"
QT_MOC_LITERAL(1, 18, 20), // "adminVerifWindowBack"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 17) // "adminVerifSucceed"

    },
    "adminverifywindow\0adminVerifWindowBack\0"
    "\0adminVerifSucceed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_adminverifywindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void adminverifywindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        adminverifywindow *_t = static_cast<adminverifywindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->adminVerifWindowBack(); break;
        case 1: _t->adminVerifSucceed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (adminverifywindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&adminverifywindow::adminVerifWindowBack)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (adminverifywindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&adminverifywindow::adminVerifSucceed)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject adminverifywindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_adminverifywindow.data,
      qt_meta_data_adminverifywindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *adminverifywindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *adminverifywindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_adminverifywindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int adminverifywindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void adminverifywindow::adminVerifWindowBack()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void adminverifywindow::adminVerifSucceed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
