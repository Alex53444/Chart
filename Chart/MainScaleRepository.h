#ifndef MAINSCALEREPOSITORY_H
#define MAINSCALEREPOSITORY_H

#include <QString>
#include <QList>
#include <QObject>
#include "Types.h"

typedef enum {
    XMAINSCALE_DEG_nsec = 0,
    XMAINSCALE_DEG_usec,
    XMAINSCALE_DEG_msec,
    XMAINSCALE_DEG_sec,
    XMAINSCALE_DEG_min,
    XMAINSCALE_DEG_hour,
} TYPEDEGXMAINSCALE;

typedef enum {
    XMAINSCALE_TYPE_1nsec = 0,
    XMAINSCALE_TYPE_2nsec,
    XMAINSCALE_TYPE_5nsec,
    XMAINSCALE_TYPE_10nsec,
    XMAINSCALE_TYPE_20nsec,
    XMAINSCALE_TYPE_50nsec,
    XMAINSCALE_TYPE_100nsec,
    XMAINSCALE_TYPE_200nsec,
    XMAINSCALE_TYPE_500nsec,
    XMAINSCALE_TYPE_1usec,
    XMAINSCALE_TYPE_2usec,
    XMAINSCALE_TYPE_5usec,
    XMAINSCALE_TYPE_10usec,
    XMAINSCALE_TYPE_20usec,
    XMAINSCALE_TYPE_50usec,
    XMAINSCALE_TYPE_100usec,
    XMAINSCALE_TYPE_200usec,
    XMAINSCALE_TYPE_500usec,
    XMAINSCALE_TYPE_1msec,
    XMAINSCALE_TYPE_2msec,
    XMAINSCALE_TYPE_5msec,
    XMAINSCALE_TYPE_10msec,
    XMAINSCALE_TYPE_20msec,
    XMAINSCALE_TYPE_50msec,
    XMAINSCALE_TYPE_100msec,
    XMAINSCALE_TYPE_200msec,
    XMAINSCALE_TYPE_500msec,
    XMAINSCALE_TYPE_1sec,
    XMAINSCALE_TYPE_2sec,
    XMAINSCALE_TYPE_5sec,
    XMAINSCALE_TYPE_10sec,
    XMAINSCALE_TYPE_30sec,
    XMAINSCALE_TYPE_1min,
    XMAINSCALE_TYPE_2min,
    XMAINSCALE_TYPE_5min,
    XMAINSCALE_TYPE_10min,
    XMAINSCALE_TYPE_30min,
    XMAINSCALE_TYPE_1hour,
    XMAINSCALE_TYPE_2hour
} TYPEXMAINSCALE;


typedef enum {
    YMAINSCALE_TYPE_1u = 0,
    YMAINSCALE_TYPE_2u,
    YMAINSCALE_TYPE_5u,
    YMAINSCALE_TYPE_10u,
    YMAINSCALE_TYPE_20u,
    YMAINSCALE_TYPE_50u,
    YMAINSCALE_TYPE_100u,
    YMAINSCALE_TYPE_200u,
    YMAINSCALE_TYPE_500u,
    YMAINSCALE_TYPE_1m,
    YMAINSCALE_TYPE_2m,
    YMAINSCALE_TYPE_5m,
    YMAINSCALE_TYPE_10m,
    YMAINSCALE_TYPE_20m,
    YMAINSCALE_TYPE_50m,
    YMAINSCALE_TYPE_100m,
    YMAINSCALE_TYPE_200m,
    YMAINSCALE_TYPE_500m,
    YMAINSCALE_TYPE_1,
    YMAINSCALE_TYPE_2,
    YMAINSCALE_TYPE_5,
    YMAINSCALE_TYPE_10,
    YMAINSCALE_TYPE_20,
    YMAINSCALE_TYPE_50,
    YMAINSCALE_TYPE_100,
    YMAINSCALE_TYPE_200,
    YMAINSCALE_TYPE_500,
    YMAINSCALE_TYPE_1k,
    YMAINSCALE_TYPE_2k,
    YMAINSCALE_TYPE_5k,
    YMAINSCALE_TYPE_10k,
    YMAINSCALE_TYPE_20k,
    YMAINSCALE_TYPE_50k,
    YMAINSCALE_TYPE_100k,
    YMAINSCALE_TYPE_200k,
    YMAINSCALE_TYPE_500k,
    YMAINSCALE_TYPE_1M,
    YMAINSCALE_TYPE_2M,
    YMAINSCALE_TYPE_5M,
    YMAINSCALE_TYPE_10M,
    YMAINSCALE_TYPE_20M,
    YMAINSCALE_TYPE_50M,
    YMAINSCALE_TYPE_100M,
    YMAINSCALE_TYPE_200M,
    YMAINSCALE_TYPE_500M,
} TYPEYMAINSCALE;


class MainScaleRepository : public QObject
{
public:
    MainScaleRepository();

    // Получить лист единиц измерений X
    void GetMainXScalesList(QList<QString> &list);

    // Получить количество единиц измерений X
    void GetMainXScalesCount(ULONG *size);

    // Получить единицу измерения X
    void GetMainXScaleName(ULONG num, QString  &name);

    // Получить лист единиц измерений Y
    void GetMainYScalesList(QList<QString> &list);

    // Получить количество единиц измерений Y
    void GetMainYScalesCount(ULONG *size);

    // Получить единицу измерения Y
    void GetMainYScaleName(ULONG num, QString  &name);


private:
    QList<QString> m_MainXScale;
    QList<QString> m_MainYScale;
};

#endif // MAINSCALEREPOSITORY_H
