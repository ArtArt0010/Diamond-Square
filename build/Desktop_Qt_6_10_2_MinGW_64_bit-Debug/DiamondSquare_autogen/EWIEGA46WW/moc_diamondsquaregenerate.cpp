/****************************************************************************
** Meta object code from reading C++ file 'diamondsquaregenerate.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../diamondsquaregenerate.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'diamondsquaregenerate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN21DiamondSquareGenerateE_t {};
} // unnamed namespace

template <> constexpr inline auto DiamondSquareGenerate::qt_create_metaobjectdata<qt_meta_tag_ZN21DiamondSquareGenerateE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DiamondSquareGenerate",
        "QML.Element",
        "auto",
        "DiamondSquare",
        "offsetChanged",
        "",
        "roughnessChanged",
        "seedChanged",
        "waterLevelChanged",
        "camChanged",
        "waterLevel",
        "roughness",
        "seed",
        "camX",
        "camY",
        "camScale"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'offsetChanged'
        QtMocHelpers::SignalData<void()>(4, 5, QMC::AccessPublic, QMetaType::Void),
        // Signal 'roughnessChanged'
        QtMocHelpers::SignalData<void()>(6, 5, QMC::AccessPublic, QMetaType::Void),
        // Signal 'seedChanged'
        QtMocHelpers::SignalData<void()>(7, 5, QMC::AccessPublic, QMetaType::Void),
        // Signal 'waterLevelChanged'
        QtMocHelpers::SignalData<void()>(8, 5, QMC::AccessPublic, QMetaType::Void),
        // Signal 'camChanged'
        QtMocHelpers::SignalData<void()>(9, 5, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'waterLevel'
        QtMocHelpers::PropertyData<double>(10, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'roughness'
        QtMocHelpers::PropertyData<double>(11, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'seed'
        QtMocHelpers::PropertyData<quint32>(12, QMetaType::UInt, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'camX'
        QtMocHelpers::PropertyData<double>(13, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'camY'
        QtMocHelpers::PropertyData<double>(14, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'camScale'
        QtMocHelpers::PropertyData<double>(15, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    1,    3 },
    });
    return QtMocHelpers::metaObjectData<DiamondSquareGenerate, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject DiamondSquareGenerate::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickPaintedItem::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21DiamondSquareGenerateE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21DiamondSquareGenerateE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN21DiamondSquareGenerateE_t>.metaTypes,
    nullptr
} };

void DiamondSquareGenerate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DiamondSquareGenerate *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->offsetChanged(); break;
        case 1: _t->roughnessChanged(); break;
        case 2: _t->seedChanged(); break;
        case 3: _t->waterLevelChanged(); break;
        case 4: _t->camChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DiamondSquareGenerate::*)()>(_a, &DiamondSquareGenerate::offsetChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DiamondSquareGenerate::*)()>(_a, &DiamondSquareGenerate::roughnessChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (DiamondSquareGenerate::*)()>(_a, &DiamondSquareGenerate::seedChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (DiamondSquareGenerate::*)()>(_a, &DiamondSquareGenerate::waterLevelChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (DiamondSquareGenerate::*)()>(_a, &DiamondSquareGenerate::camChanged, 4))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<double*>(_v) = _t->waterLevel(); break;
        case 1: *reinterpret_cast<double*>(_v) = _t->roughness(); break;
        case 2: *reinterpret_cast<quint32*>(_v) = _t->seed(); break;
        case 3: *reinterpret_cast<double*>(_v) = _t->camX(); break;
        case 4: *reinterpret_cast<double*>(_v) = _t->camY(); break;
        case 5: *reinterpret_cast<double*>(_v) = _t->camScale(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWaterLevel(*reinterpret_cast<double*>(_v)); break;
        case 1: _t->setRoughness(*reinterpret_cast<double*>(_v)); break;
        case 2: _t->setSeed(*reinterpret_cast<quint32*>(_v)); break;
        case 3: _t->setCamX(*reinterpret_cast<double*>(_v)); break;
        case 4: _t->setCamY(*reinterpret_cast<double*>(_v)); break;
        case 5: _t->setCamScale(*reinterpret_cast<double*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DiamondSquareGenerate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DiamondSquareGenerate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21DiamondSquareGenerateE_t>.strings))
        return static_cast<void*>(this);
    return QQuickPaintedItem::qt_metacast(_clname);
}

int DiamondSquareGenerate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickPaintedItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void DiamondSquareGenerate::offsetChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DiamondSquareGenerate::roughnessChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DiamondSquareGenerate::seedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DiamondSquareGenerate::waterLevelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void DiamondSquareGenerate::camChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
