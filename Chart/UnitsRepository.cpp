#include "UnitsRepository.h"

const int SIZE_TYPEUNITS = 10;
const int SIZE_DEGUNITS = 6;

const int SIZE_ALLUNITS = 44;

UNITS_TYPE ALL_UNITS[] = {
    {UNITS_TYPE_NULL, UNITS_DEG_NULL},
    {UNITS_TYPE_V, UNITS_DEG_n},
    {UNITS_TYPE_V, UNITS_DEG_u},
    {UNITS_TYPE_V, UNITS_DEG_m},
    {UNITS_TYPE_V, UNITS_DEG_NULL},
    {UNITS_TYPE_V, UNITS_DEG_k},
    {UNITS_TYPE_V, UNITS_DEG_M},
    {UNITS_TYPE_A, UNITS_DEG_n},
    {UNITS_TYPE_A, UNITS_DEG_u},
    {UNITS_TYPE_A, UNITS_DEG_m},
    {UNITS_TYPE_A, UNITS_DEG_NULL},
    {UNITS_TYPE_A, UNITS_DEG_k},
    {UNITS_TYPE_A, UNITS_DEG_M},
    {UNITS_TYPE_Watt, UNITS_DEG_n},
    {UNITS_TYPE_Watt, UNITS_DEG_u},
    {UNITS_TYPE_Watt, UNITS_DEG_m},
    {UNITS_TYPE_Watt, UNITS_DEG_NULL},
    {UNITS_TYPE_Watt, UNITS_DEG_k},
    {UNITS_TYPE_Watt, UNITS_DEG_M},
    {UNITS_TYPE_A, UNITS_DEG_n},
    {UNITS_TYPE_A, UNITS_DEG_u},
    {UNITS_TYPE_A, UNITS_DEG_m},
    {UNITS_TYPE_A, UNITS_DEG_NULL},
    {UNITS_TYPE_A, UNITS_DEG_k},
    {UNITS_TYPE_A, UNITS_DEG_M},
    {UNITS_TYPE_Hz, UNITS_DEG_n},
    {UNITS_TYPE_Hz, UNITS_DEG_u},
    {UNITS_TYPE_Hz, UNITS_DEG_m},
    {UNITS_TYPE_Hz, UNITS_DEG_NULL},
    {UNITS_TYPE_Hz, UNITS_DEG_k},
    {UNITS_TYPE_Hz, UNITS_DEG_M},
    {UNITS_TYPE_Pa, UNITS_DEG_n},
    {UNITS_TYPE_Pa, UNITS_DEG_u},
    {UNITS_TYPE_Pa, UNITS_DEG_m},
    {UNITS_TYPE_Pa, UNITS_DEG_NULL},
    {UNITS_TYPE_Pa, UNITS_DEG_k},
    {UNITS_TYPE_Pa, UNITS_DEG_M},
    {UNITS_TYPE_Psi, UNITS_DEG_NULL},
    {UNITS_TYPE_Cels, UNITS_DEG_NULL},
    {UNITS_TYPE_Percent, UNITS_DEG_NULL},
    {UNITS_TYPE_sec, UNITS_DEG_n},
    {UNITS_TYPE_sec, UNITS_DEG_u},
    {UNITS_TYPE_sec, UNITS_DEG_m},
    {UNITS_TYPE_sec, UNITS_DEG_NULL}
};

float DERGEE [] = {
    1e-9,
    1e-6,
    1e-3,
    1e0,
    1e3,
    1e6,
    1e9
};

UnitsRepository::UnitsRepository()
{
    m_Units.resize(SIZE_TYPEUNITS);

    m_Units[UNITS_TYPE_NULL] = QObject::tr("код");
    m_Units[UNITS_TYPE_V] = QObject::tr("В");
    m_Units[UNITS_TYPE_A] = QObject::tr("А");
    m_Units[UNITS_TYPE_Watt] = QObject::tr("Вт");
    m_Units[UNITS_TYPE_Hz] = QObject::tr("Гц");
    m_Units[UNITS_TYPE_Pa] = QObject::tr("Па");
    m_Units[UNITS_TYPE_Psi] = QObject::tr("Psi");
    m_Units[UNITS_TYPE_Cels] = QObject::tr("°");
    m_Units[UNITS_TYPE_Percent] = QObject::tr("%");
    m_Units[UNITS_TYPE_sec] = QObject::tr("c");

    m_DegUnits.resize(SIZE_DEGUNITS);

    m_DegUnits[UNITS_DEG_n] = QObject::tr("н");
    m_DegUnits[UNITS_DEG_u] = QObject::tr("мк");
    m_DegUnits[UNITS_DEG_m] = QObject::tr("м");
    m_DegUnits[UNITS_DEG_NULL] = QObject::tr("");
    m_DegUnits[UNITS_DEG_k] = QObject::tr("k");
    m_DegUnits[UNITS_DEG_M] = QObject::tr("M");
}

// Получить лист единиц измерений
void UnitsRepository::GetUnitsList(QList<QString> &list)
{
    for(int i=0; i<SIZE_ALLUNITS; i++) {
        list << m_DegUnits[ALL_UNITS[i].numDegree] + m_Units[ALL_UNITS[i].Type];
    }
}

// Получить лист единиц измерений одной Unit
void UnitsRepository::GetUnitsList(QList<QString> &list, USHORT Type)
{
    for(int i=0; i<SIZE_DEGUNITS; i++) {
        list << m_DegUnits[i] + m_Units[Type];
    }
}

// Получить множитель номера степени
void UnitsRepository::GetDegree(double *Degree, UNITS_TYPE unit)
{
    if(unit.numDegree < SIZE_DEGUNITS)
        *Degree = DERGEE[unit.numDegree];
}

// Преобразовать из общего листа единиц, в тип и множитель
void UnitsRepository::ConvertUnit(UNITS_TYPE *unit, ULONG numUnits)
{
    unit->Type = ALL_UNITS[numUnits].Type;
    unit->numDegree = ALL_UNITS[numUnits].numDegree;
}

// Преобразовать из типа и множителя в позицию общего листа единиц
void UnitsRepository::ConvertUnit(ULONG *numUnits, UNITS_TYPE unit)
{
    for(int i=0; i<SIZE_ALLUNITS; i++) {
        if((ALL_UNITS[i].Type == unit.Type) && (ALL_UNITS[i].numDegree == unit.numDegree)) {
            *numUnits = i;
            return;
        }
    }
}

// Сложить порядковые номера множителя
bool UnitsRepository::AddUnit(ULONG *numDegSumm, ULONG numDeg1, ULONG numDeg2)
{
    switch (numDeg1) {
        case UNITS_DEG_n:
            *numDegSumm = numDeg2-3;
            return *numDegSumm >= 0;

        case UNITS_DEG_u:
            *numDegSumm = numDeg2-2;
            return *numDegSumm >= 0;

        case UNITS_DEG_m:
            *numDegSumm = numDeg2-1;
            return *numDegSumm >= 0;

        case UNITS_DEG_NULL:
            *numDegSumm = numDeg2;
            return true;

        case UNITS_DEG_k:
            *numDegSumm = numDeg2+1;
            return *numDegSumm <= UNITS_DEG_M;

        case UNITS_DEG_M:
            *numDegSumm = numDeg2+2;
            return *numDegSumm <= UNITS_DEG_M;
    }
    return false;
}

// Получить лист типов единиц измерений
void UnitsRepository::GetTypeUnitsList(QList<QString> &list)
{
    list = m_Units;
}

// Получить лист степени числа
void UnitsRepository::GetDegreeUnitsList(QList<QString> &list)
{
    list = m_DegUnits;
}

// Получить количество единиц измерений
void UnitsRepository::GetUnitsCount(ULONG *size)
{
    *size = m_Units.count();
}

// Получить единицу измерения
void UnitsRepository::GetUnitsName(QString  &name, UNITS_TYPE unit)
{
    name = m_DegUnits[unit.numDegree] + m_Units[unit.Type];
}

// Получить единицу измерения, без приставки едениц
void UnitsRepository::GetBaseUnitsName(QString  &name, UNITS_TYPE unit)
{
    name = m_Units[unit.Type];
}
