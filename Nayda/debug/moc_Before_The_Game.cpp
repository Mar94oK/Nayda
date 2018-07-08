/****************************************************************************
** Meta object code from reading C++ file 'Before_The_Game.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Application/Before_The_Game/Before_The_Game.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Before_The_Game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Before_The_Game_t {
    QByteArrayData data[19];
    char stringdata0[459];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Before_The_Game_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Before_The_Game_t qt_meta_stringdata_Before_The_Game = {
    {
QT_MOC_LITERAL(0, 0, 15), // "Before_The_Game"
QT_MOC_LITERAL(1, 16, 23), // "dbg_switch_to_game_mode"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 19), // "dbg_the_game_begins"
QT_MOC_LITERAL(4, 61, 37), // "update_game_options_number_of..."
QT_MOC_LITERAL(5, 99, 17), // "number_of_players"
QT_MOC_LITERAL(6, 117, 20), // "update_game_options_"
QT_MOC_LITERAL(7, 138, 9), // "game_type"
QT_MOC_LITERAL(8, 148, 35), // "update_game_options_card_stac..."
QT_MOC_LITERAL(9, 184, 15), // "card_stack_type"
QT_MOC_LITERAL(10, 200, 32), // "start_game_with_default_settings"
QT_MOC_LITERAL(11, 233, 33), // "sig_userHaveChangedServerSett..."
QT_MOC_LITERAL(12, 267, 14), // "serverSettings"
QT_MOC_LITERAL(13, 282, 25), // "sig_openRoomForConnection"
QT_MOC_LITERAL(14, 308, 38), // "dbg_switch_to_game_mode_butto..."
QT_MOC_LITERAL(15, 347, 40), // "dbg_start_the_game_with_defau..."
QT_MOC_LITERAL(16, 388, 34), // "slot_userHaveChangedServerSet..."
QT_MOC_LITERAL(17, 423, 8), // "settings"
QT_MOC_LITERAL(18, 432, 26) // "slot_openRoomForConnection"

    },
    "Before_The_Game\0dbg_switch_to_game_mode\0"
    "\0dbg_the_game_begins\0"
    "update_game_options_number_of_players\0"
    "number_of_players\0update_game_options_\0"
    "game_type\0update_game_options_card_stack_type\0"
    "card_stack_type\0start_game_with_default_settings\0"
    "sig_userHaveChangedServerSettings\0"
    "serverSettings\0sig_openRoomForConnection\0"
    "dbg_switch_to_game_mode_button_pressed\0"
    "dbg_start_the_game_with_default_settings\0"
    "slot_userHaveChangedServerSettings\0"
    "settings\0slot_openRoomForConnection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Before_The_Game[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       3,    1,   77,    2, 0x06 /* Public */,
       4,    1,   80,    2, 0x06 /* Public */,
       6,    1,   83,    2, 0x06 /* Public */,
       8,    1,   86,    2, 0x06 /* Public */,
      10,    1,   89,    2, 0x06 /* Public */,
      11,    1,   92,    2, 0x06 /* Public */,
      13,    0,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,   96,    2, 0x0a /* Public */,
      15,    0,   97,    2, 0x0a /* Public */,
      16,    1,   98,    2, 0x0a /* Public */,
      18,    0,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   17,
    QMetaType::Void,

       0        // eod
};

void Before_The_Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Before_The_Game *_t = static_cast<Before_The_Game *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dbg_switch_to_game_mode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->dbg_the_game_begins((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->update_game_options_number_of_players((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->update_game_options_((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->update_game_options_card_stack_type((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->start_game_with_default_settings((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->sig_userHaveChangedServerSettings((*reinterpret_cast< serverSettings(*)>(_a[1]))); break;
        case 7: _t->sig_openRoomForConnection(); break;
        case 8: _t->dbg_switch_to_game_mode_button_pressed(); break;
        case 9: _t->dbg_start_the_game_with_default_settings(); break;
        case 10: _t->slot_userHaveChangedServerSettings((*reinterpret_cast< serverSettings(*)>(_a[1]))); break;
        case 11: _t->slot_openRoomForConnection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Before_The_Game::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Before_The_Game::dbg_switch_to_game_mode)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Before_The_Game::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Before_The_Game::dbg_the_game_begins)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Before_The_Game::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Before_The_Game::update_game_options_number_of_players)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Before_The_Game::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Before_The_Game::update_game_options_)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Before_The_Game::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Before_The_Game::update_game_options_card_stack_type)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Before_The_Game::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Before_The_Game::start_game_with_default_settings)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Before_The_Game::*_t)(serverSettings );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Before_The_Game::sig_userHaveChangedServerSettings)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Before_The_Game::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Before_The_Game::sig_openRoomForConnection)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject Before_The_Game::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Before_The_Game.data,
      qt_meta_data_Before_The_Game,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Before_The_Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Before_The_Game::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Before_The_Game.stringdata0))
        return static_cast<void*>(const_cast< Before_The_Game*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Before_The_Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Before_The_Game::dbg_switch_to_game_mode(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Before_The_Game::dbg_the_game_begins(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Before_The_Game::update_game_options_number_of_players(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Before_The_Game::update_game_options_(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Before_The_Game::update_game_options_card_stack_type(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Before_The_Game::start_game_with_default_settings(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Before_The_Game::sig_userHaveChangedServerSettings(serverSettings _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Before_The_Game::sig_openRoomForConnection()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
