#ifndef UNITSREPOSITORY_H
#define UNITSREPOSITORY_H

#include <QString>
#include <QList>
#include <QObject>
#include "Types.h"


typedef enum {
    UNITS_TYPE_NULL = 0,
    UNITS_TYPE_V,
    UNITS_TYPE_A,
    UNITS_TYPE_Watt,
    UNITS_TYPE_Hz,
    UNITS_TYPE_Pa,
    UNITS_TYPE_Psi,
    UNITS_TYPE_Cels,
    UNITS_TYPE_Percent,
    UNITS_TYPE_sec,
} TYPEUNITS;

typedef enum {
    UNITS_DEG_n = 0,
    UNITS_DEG_u,
    UNITS_DEG_m,
    UNITS_DEG_NULL,
    UNITS_DEG_k,
    UNITS_DEG_M,
} TYPEDEGUNITS;

class UnitsRepository
{
public:
    UnitsRepository();

    // Получить лист единиц измерений
    void GetUnitsList(QList<QString> &list);

    // Получить лист единиц измерений одной Unit
    void GetUnitsList(QList<QString> &list, USHORT Type);

    // Получить множитель номера степени
    void GetDegree(double *Degree, UNITS_TYPE unit);

    // Преобразовать из общего листа единиц, в тип и множитель
    void ConvertUnit(UNITS_TYPE *unit, ULONG numUnits);

    // Преобразовать из типа и множителя в позицию общего листа единиц
    void ConvertUnit(ULONG *numUnits, UNITS_TYPE unit);

    // Сложить порядковые номера множителя (после умножения величин)
    bool AddUnit(ULONG *numDegSumm, ULONG numDeg1, ULONG numDeg2);

    // Получить лист типов единиц измерений
    void GetTypeUnitsList(QList<QString> &list);

    // Получить лист степени числа
    void GetDegreeUnitsList(QList<QString> &list);

    // Получить количество единиц измерений
    void GetUnitsCount(ULONG *size);

    // Получить единицу измерения
    void GetUnitsName(QString  &name, UNITS_TYPE unit);

    // Получить единицу измерения, без приставки едениц
    void GetBaseUnitsName(QString  &name, UNITS_TYPE unit);

private:
    QList<QString> m_Units;
    QList<QString> m_DegUnits;
};

#endif // UNITSREPOSITORY_H
