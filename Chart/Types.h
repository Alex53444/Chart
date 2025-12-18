#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QColor>
#include <QImage>
#include <QtGlobal>

typedef int64_t LONGLONG;
typedef uint64_t ULONGLONG;
typedef int32_t LONG;
typedef uint32_t ULONG;
typedef int16_t SHORT;
typedef uint16_t USHORT;
typedef uint8_t UBYTE;
typedef int8_t BYTE;
typedef uint8_t BOOL;
typedef uint64_t ULONGLONG;

typedef LONG RESULT;
typedef ULONG CLASSID;
typedef ULONG DEVICESTATE;
typedef ULONG SCALESTATE;
typedef ULONG NOTIFY_DEV;
typedef ULONG NOTIFY_CHAN;
typedef ULONG CHANSTATE;
typedef ULONG EVENTSTATE;
typedef ULONG SCALESTATE;
typedef ULONG TARESTATE;
typedef ULONG TYPESOURCE;
typedef ULONG APPSTATE;

#define ROLE_BUS            Qt::UserRole + 1
#define ROLE_DEVICE         Qt::UserRole + 2
#define ROLE_MODULE         Qt::UserRole + 3
#define ROLE_CHANNEL        Qt::UserRole + 4
#define ROLE_GROUP          Qt::UserRole + 5
#define ROLE_SOFTCHAN       Qt::UserRole + 6
#define ROLE_SOFTCHAN_DATA  Qt::UserRole + 7
#define ROLE_CHAN_PROP      Qt::UserRole + 8
#define ROLE_TAG_PROP       Qt::UserRole + 9
#define ROLE_DATABANK       Qt::UserRole + 10
#define ROLE_TARE_PROP      Qt::UserRole + 11
#define ROLE_NUMBER         Qt::UserRole + 12
#define ROLE_EVENT_PROP     Qt::UserRole + 13
#define ROLE_SOFTEVENT      Qt::UserRole + 14
#define ROLE_BUTTON         Qt::UserRole + 15

class IDeviceWidget;

typedef enum
{
    ERROR_OK = 0,
    ERROR_FAULT = 1,
    ERROR_WARNING = 2,
    ERROR_INFO = 3
} ER_TYPE;

struct UNITS_TYPE{
    USHORT Type;
    USHORT numDegree;
};

typedef struct
{
    IDeviceWidget *deviceWidget;
    QWidget *widget;
} QDeviceWidget;

typedef struct
{
    QString Name;
    QString Descriptor;
    ULONG Id;
} TDllInfo;

typedef struct
{
    double min;
    double max;
} TRange;

typedef struct
{
    QString Name;
    QColor Color;
    QImage Image;
    ULONGLONG Time_ns;
} TEventMessage;

typedef struct
{
    ULONGLONG RxBytes;
    ULONGLONG TxBytes;
    ULONGLONG LifeTime;
    ULONGLONG LostRxPacket;
} TStatistics;
//
typedef struct
{
    SHORT voltage;
    SHORT leak;
} TLeak;

typedef struct
{
    union {
        BYTE        dataI1;
        SHORT       dataI2;
        LONG        dataI4;
        LONGLONG    dataI8;
        UBYTE       dataUI1;
        USHORT      dataUI2;
        ULONG       dataUI4;
        ULONGLONG   dataUI8;
        float       dataR4;
        double      dataR8;
        BOOL        dataBool;
        union {
            TLeak   dataLeak;
        } dataSuper;
    };
} TData;


typedef QHash<ULONG, QVariant> PROPERTY;

#endif // TYPES_H
