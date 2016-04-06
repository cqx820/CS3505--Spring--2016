/****************************************************************************
** Meta object code from reading C++ file 'toolbox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../A7/include/toolbox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'toolbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ToolBox_t {
    QByteArrayData data[9];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ToolBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ToolBox_t qt_meta_stringdata_ToolBox = {
    {
QT_MOC_LITERAL(0, 0, 7), // "ToolBox"
QT_MOC_LITERAL(1, 8, 25), // "switchColorsButtonClicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 7), // "setTool"
QT_MOC_LITERAL(4, 43, 5), // "Tool*"
QT_MOC_LITERAL(5, 49, 14), // "penSizeChanged"
QT_MOC_LITERAL(6, 64, 5), // "value"
QT_MOC_LITERAL(7, 70, 19), // "primaryColorChanged"
QT_MOC_LITERAL(8, 90, 12) // "toolSelected"

    },
    "ToolBox\0switchColorsButtonClicked\0\0"
    "setTool\0Tool*\0penSizeChanged\0value\0"
    "primaryColorChanged\0toolSelected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ToolBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,
       5,    1,   43,    2, 0x06 /* Public */,
       7,    1,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QColor,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ToolBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ToolBox *_t = static_cast<ToolBox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->switchColorsButtonClicked(); break;
        case 1: _t->setTool((*reinterpret_cast< Tool*(*)>(_a[1]))); break;
        case 2: _t->penSizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->primaryColorChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 4: _t->toolSelected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Tool* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ToolBox::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ToolBox::switchColorsButtonClicked)) {
                *result = 0;
            }
        }
        {
            typedef void (ToolBox::*_t)(Tool * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ToolBox::setTool)) {
                *result = 1;
            }
        }
        {
            typedef void (ToolBox::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ToolBox::penSizeChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (ToolBox::*_t)(QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ToolBox::primaryColorChanged)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject ToolBox::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_ToolBox.data,
      qt_meta_data_ToolBox,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ToolBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ToolBox::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ToolBox.stringdata0))
        return static_cast<void*>(const_cast< ToolBox*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int ToolBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ToolBox::switchColorsButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ToolBox::setTool(Tool * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ToolBox::penSizeChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ToolBox::primaryColorChanged(QColor _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
