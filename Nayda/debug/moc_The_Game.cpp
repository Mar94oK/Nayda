/****************************************************************************
** Meta object code from reading C++ file 'The_Game.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Application/The_Game/The_Game.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'The_Game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_The_Game_t {
    QByteArrayData data[11];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_The_Game_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_The_Game_t qt_meta_stringdata_The_Game = {
    {
QT_MOC_LITERAL(0, 0, 8), // "The_Game"
QT_MOC_LITERAL(1, 9, 15), // "dbg_to_be_shown"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 29), // "dbg_return_to_before_the_game"
QT_MOC_LITERAL(4, 56, 27), // "dbg_was_pushed_to_game_mode"
QT_MOC_LITERAL(5, 84, 29), // "dbg_return_to_the_main_window"
QT_MOC_LITERAL(6, 114, 19), // "showTheCardInCentre"
QT_MOC_LITERAL(7, 134, 14), // "PositionedCard"
QT_MOC_LITERAL(8, 149, 4), // "card"
QT_MOC_LITERAL(9, 154, 19), // "hideTheCardInCentre"
QT_MOC_LITERAL(10, 174, 49) // "_adjustSizeOfTheGamerWidgetTo..."

    },
    "The_Game\0dbg_to_be_shown\0\0"
    "dbg_return_to_before_the_game\0"
    "dbg_was_pushed_to_game_mode\0"
    "dbg_return_to_the_main_window\0"
    "showTheCardInCentre\0PositionedCard\0"
    "card\0hideTheCardInCentre\0"
    "_adjustSizeOfTheGamerWidgetToMakeCardsToBeInPlace"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_The_Game[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   55,    2, 0x0a /* Public */,
       5,    0,   56,    2, 0x0a /* Public */,
       6,    1,   57,    2, 0x0a /* Public */,
       9,    1,   60,    2, 0x0a /* Public */,
      10,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

       0        // eod
};

void The_Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        The_Game *_t = static_cast<The_Game *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dbg_to_be_shown((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->dbg_return_to_before_the_game((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->dbg_was_pushed_to_game_mode(); break;
        case 3: _t->dbg_return_to_the_main_window(); break;
        case 4: _t->showTheCardInCentre((*reinterpret_cast< PositionedCard(*)>(_a[1]))); break;
        case 5: _t->hideTheCardInCentre((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->_adjustSizeOfTheGamerWidgetToMakeCardsToBeInPlace(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (The_Game::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&The_Game::dbg_to_be_shown)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (The_Game::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&The_Game::dbg_return_to_before_the_game)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject The_Game::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_The_Game.data,
      qt_meta_data_The_Game,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *The_Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *The_Game::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_The_Game.stringdata0))
        return static_cast<void*>(const_cast< The_Game*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int The_Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void The_Game::dbg_to_be_shown(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void The_Game::dbg_return_to_before_the_game(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
