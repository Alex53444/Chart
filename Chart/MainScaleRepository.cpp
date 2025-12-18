#include "MainScaleRepository.h"
#include "UnitsRepository.h"

const int SIZE_XMAINSCALE = 39;
const int SIZE_YMAINSCALE = 45;

MainScaleRepository::MainScaleRepository()
{
    m_MainXScale.resize(SIZE_XMAINSCALE);

    m_MainXScale[XMAINSCALE_TYPE_1nsec] = tr("1нс");
    m_MainXScale[XMAINSCALE_TYPE_2nsec] = tr("2нс");
    m_MainXScale[XMAINSCALE_TYPE_5nsec] = tr("5нс");
    m_MainXScale[XMAINSCALE_TYPE_10nsec] = tr("10нс");
    m_MainXScale[XMAINSCALE_TYPE_20nsec] = tr("20нс");
    m_MainXScale[XMAINSCALE_TYPE_50nsec] = tr("50нс");
    m_MainXScale[XMAINSCALE_TYPE_100nsec] = tr("100нс");
    m_MainXScale[XMAINSCALE_TYPE_200nsec] = tr("200нс");
    m_MainXScale[XMAINSCALE_TYPE_500nsec] = tr("500нс");
    m_MainXScale[XMAINSCALE_TYPE_1usec] = tr("1мкс");
    m_MainXScale[XMAINSCALE_TYPE_2usec] = tr("2мкс");
    m_MainXScale[XMAINSCALE_TYPE_5usec] = tr("5мкс");
    m_MainXScale[XMAINSCALE_TYPE_10usec] = tr("10мкс");
    m_MainXScale[XMAINSCALE_TYPE_20usec] = tr("20мкс");
    m_MainXScale[XMAINSCALE_TYPE_50usec] = tr("50мкс");
    m_MainXScale[XMAINSCALE_TYPE_100usec] = tr("100мкс");
    m_MainXScale[XMAINSCALE_TYPE_200usec] = tr("200мкс");
    m_MainXScale[XMAINSCALE_TYPE_500usec] = tr("500мкс");
    m_MainXScale[XMAINSCALE_TYPE_1msec] = tr("1мс");
    m_MainXScale[XMAINSCALE_TYPE_2msec] = tr("2мс");
    m_MainXScale[XMAINSCALE_TYPE_5msec] = tr("5мс");
    m_MainXScale[XMAINSCALE_TYPE_10msec] = tr("10мс");
    m_MainXScale[XMAINSCALE_TYPE_20msec] = tr("20мс");
    m_MainXScale[XMAINSCALE_TYPE_50msec] = tr("50мс");
    m_MainXScale[XMAINSCALE_TYPE_100msec] = tr("100мс");
    m_MainXScale[XMAINSCALE_TYPE_200msec] = tr("200мс");
    m_MainXScale[XMAINSCALE_TYPE_500msec] = tr("500мс");
    m_MainXScale[XMAINSCALE_TYPE_1sec] = tr("1с");
    m_MainXScale[XMAINSCALE_TYPE_2sec] = tr("2с");
    m_MainXScale[XMAINSCALE_TYPE_5sec] = tr("5с");
    m_MainXScale[XMAINSCALE_TYPE_10sec] = tr("10с");
    m_MainXScale[XMAINSCALE_TYPE_30sec] = tr("30с");
    m_MainXScale[XMAINSCALE_TYPE_1min] = tr("1мин");
    m_MainXScale[XMAINSCALE_TYPE_2min] = tr("2мин");
    m_MainXScale[XMAINSCALE_TYPE_5min] = tr("5мин");
    m_MainXScale[XMAINSCALE_TYPE_10min] = tr("10мин");
    m_MainXScale[XMAINSCALE_TYPE_30min] = tr("30мин");
    m_MainXScale[XMAINSCALE_TYPE_1hour] = tr("1час");
    m_MainXScale[XMAINSCALE_TYPE_2hour] = tr("2час");


    m_MainYScale.resize(SIZE_YMAINSCALE);

    m_MainYScale[YMAINSCALE_TYPE_1u] = tr("1мк");
    m_MainYScale[YMAINSCALE_TYPE_2u] = tr("2мк");
    m_MainYScale[YMAINSCALE_TYPE_5u] = tr("5мк");
    m_MainYScale[YMAINSCALE_TYPE_10u] = tr("10мк");
    m_MainYScale[YMAINSCALE_TYPE_20u] = tr("20мк");
    m_MainYScale[YMAINSCALE_TYPE_50u] = tr("50мк");
    m_MainYScale[YMAINSCALE_TYPE_100u] = tr("100мк");
    m_MainYScale[YMAINSCALE_TYPE_200u] = tr("200мк");
    m_MainYScale[YMAINSCALE_TYPE_500u] = tr("500мк");
    m_MainYScale[YMAINSCALE_TYPE_1m] = tr("1м");
    m_MainYScale[YMAINSCALE_TYPE_2m] = tr("2м");
    m_MainYScale[YMAINSCALE_TYPE_5m] = tr("5м");
    m_MainYScale[YMAINSCALE_TYPE_10m] = tr("10м");
    m_MainYScale[YMAINSCALE_TYPE_20m] = tr("20м");
    m_MainYScale[YMAINSCALE_TYPE_50m] = tr("50м");
    m_MainYScale[YMAINSCALE_TYPE_100m] = tr("100м");
    m_MainYScale[YMAINSCALE_TYPE_200m] = tr("200м");
    m_MainYScale[YMAINSCALE_TYPE_500m] = tr("500м");
    m_MainYScale[YMAINSCALE_TYPE_1] = tr("1");
    m_MainYScale[YMAINSCALE_TYPE_2] = tr("2");
    m_MainYScale[YMAINSCALE_TYPE_5] = tr("5");
    m_MainYScale[YMAINSCALE_TYPE_10] = tr("10");
    m_MainYScale[YMAINSCALE_TYPE_20] = tr("20");
    m_MainYScale[YMAINSCALE_TYPE_50] = tr("50");
    m_MainYScale[YMAINSCALE_TYPE_100] = tr("100");
    m_MainYScale[YMAINSCALE_TYPE_200] = tr("200");
    m_MainYScale[YMAINSCALE_TYPE_500] = tr("500");
    m_MainYScale[YMAINSCALE_TYPE_1k] = tr("1к");
    m_MainYScale[YMAINSCALE_TYPE_2k] = tr("2к");
    m_MainYScale[YMAINSCALE_TYPE_5k] = tr("5к");
    m_MainYScale[YMAINSCALE_TYPE_10k] = tr("10к");
    m_MainYScale[YMAINSCALE_TYPE_20k] = tr("20к");
    m_MainYScale[YMAINSCALE_TYPE_50k] = tr("50к");
    m_MainYScale[YMAINSCALE_TYPE_100k] = tr("100к");
    m_MainYScale[YMAINSCALE_TYPE_200k] = tr("200к");
    m_MainYScale[YMAINSCALE_TYPE_500k] = tr("500к");
    m_MainYScale[YMAINSCALE_TYPE_1M] = tr("1М");
    m_MainYScale[YMAINSCALE_TYPE_2M] = tr("2М");
    m_MainYScale[YMAINSCALE_TYPE_5M] = tr("5М");
    m_MainYScale[YMAINSCALE_TYPE_10M] = tr("10М");
    m_MainYScale[YMAINSCALE_TYPE_20M] = tr("20М");
    m_MainYScale[YMAINSCALE_TYPE_50M] = tr("50М");
    m_MainYScale[YMAINSCALE_TYPE_100M] = tr("100М");
    m_MainYScale[YMAINSCALE_TYPE_200M] = tr("200М");
    m_MainYScale[YMAINSCALE_TYPE_500M] = tr("500М");
}

// Получить лист единиц измерений X
void MainScaleRepository::GetMainXScalesList(QList<QString> &list)
{
    list = m_MainXScale;
}

// Получить количество единиц измерений X
void MainScaleRepository::GetMainXScalesCount(ULONG *size)
{
    *size = m_MainXScale.count();
}

// Получить единицу измерения X
void MainScaleRepository::GetMainXScaleName(ULONG num, QString &name)
{
    if(num < m_MainXScale.count())
        name = m_MainXScale[num];
    else
        name = "?";
}

// Получить лист единиц измерений Y
void MainScaleRepository::GetMainYScalesList(QList<QString> &list)
{
    list = m_MainYScale;
}

// Получить количество единиц измерений Y
void MainScaleRepository::GetMainYScalesCount(ULONG *size)
{
    *size = m_MainYScale.count();
}

// Получить единицу измерения Y
void MainScaleRepository::GetMainYScaleName(ULONG num, QString &name)
{
    if(num < m_MainYScale.count())
        name = m_MainYScale[num];
    else
        name = "?";
}


