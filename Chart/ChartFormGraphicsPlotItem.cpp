#include <QCursor>
#include "ChartFormGraphicsPlotItem.h"
#include "MainScaleRepository.h"
#include "QGraphicsDropShadowEffect"
#include "QGraphicsSceneHoverEvent"
#include "AppResource.h"
#include "Errors.h"

#define DEFAULT_LEFT_WIDTH_ORDINATE         40
#define LEGEND_LINE_WIDTH                   15
#define LEGEND_PADDING                      2
#define DEFAULT_LEFT_WIDTH_ORDINATE         40

//*****************************************************************************************************
//********************************************ABSCISS**************************************************
//*****************************************************************************************************

typedef struct {
    int IndexScale;
    double Width;
    int Pixels;
    unsigned int nDeg;
} INDEXSCALETUBE;

INDEXSCALETUBE IndexScaleAbscissTube[] =
{
    {XMAINSCALE_TYPE_1nsec, 1, 50, XMAINSCALE_DEG_nsec},
    {XMAINSCALE_TYPE_2nsec, 2, 50, XMAINSCALE_DEG_nsec},
    {XMAINSCALE_TYPE_5nsec, 5, 50, XMAINSCALE_DEG_nsec},
    {XMAINSCALE_TYPE_10nsec, 10, 50, XMAINSCALE_DEG_nsec},
    {XMAINSCALE_TYPE_20nsec, 20, 50, XMAINSCALE_DEG_nsec},
    {XMAINSCALE_TYPE_50nsec, 50, 50, XMAINSCALE_DEG_nsec},
    {XMAINSCALE_TYPE_100nsec, 100, 50, XMAINSCALE_DEG_nsec},
    {XMAINSCALE_TYPE_200nsec, 200, 50, XMAINSCALE_DEG_nsec},
    {XMAINSCALE_TYPE_500nsec, 500, 50, XMAINSCALE_DEG_nsec},
    {XMAINSCALE_TYPE_1usec, 1e3, 50, XMAINSCALE_DEG_usec},
    {XMAINSCALE_TYPE_2usec, 2e3, 50, XMAINSCALE_DEG_usec},
    {XMAINSCALE_TYPE_5usec, 5e3, 50, XMAINSCALE_DEG_usec},
    {XMAINSCALE_TYPE_10usec, 10e3, 50, XMAINSCALE_DEG_usec},
    {XMAINSCALE_TYPE_20usec, 20e3, 50, XMAINSCALE_DEG_usec},
    {XMAINSCALE_TYPE_50usec, 50e3, 50, XMAINSCALE_DEG_usec},
    {XMAINSCALE_TYPE_100usec, 100e3, 50, XMAINSCALE_DEG_usec},
    {XMAINSCALE_TYPE_200usec, 200e3, 50, XMAINSCALE_DEG_usec},
    {XMAINSCALE_TYPE_500usec, 500e3, 50, XMAINSCALE_DEG_usec},
    {XMAINSCALE_TYPE_1msec, 1e6, 50, XMAINSCALE_DEG_msec},
    {XMAINSCALE_TYPE_2msec, 2e6, 50, XMAINSCALE_DEG_msec},
    {XMAINSCALE_TYPE_5msec, 5e6, 50, XMAINSCALE_DEG_msec},
    {XMAINSCALE_TYPE_10msec, 10e6, 50, XMAINSCALE_DEG_msec},
    {XMAINSCALE_TYPE_20msec, 20e6, 50, XMAINSCALE_DEG_msec},
    {XMAINSCALE_TYPE_50msec, 50e6, 50, XMAINSCALE_DEG_msec},
    {XMAINSCALE_TYPE_100msec, 100e6, 50, XMAINSCALE_DEG_msec},
    {XMAINSCALE_TYPE_200msec, 200e6, 50, XMAINSCALE_DEG_msec},
    {XMAINSCALE_TYPE_500msec, 500e6, 50, XMAINSCALE_DEG_msec},
    {XMAINSCALE_TYPE_1sec, 1e9, 50, XMAINSCALE_DEG_sec},
    {XMAINSCALE_TYPE_2sec, 2e9, 50, XMAINSCALE_DEG_sec},
    {XMAINSCALE_TYPE_5sec, 5e9, 50, XMAINSCALE_DEG_sec},
    {XMAINSCALE_TYPE_10sec, 10e9, 50, XMAINSCALE_DEG_sec},
    {XMAINSCALE_TYPE_30sec, 30e9, 50, XMAINSCALE_DEG_sec},
    {XMAINSCALE_TYPE_1min, 60e9, 50, XMAINSCALE_DEG_min},
    {XMAINSCALE_TYPE_2min, 120e9, 50, XMAINSCALE_DEG_min},
    {XMAINSCALE_TYPE_5min, 300e9, 50, XMAINSCALE_DEG_min},
    {XMAINSCALE_TYPE_10min, 600e9, 50, XMAINSCALE_DEG_min},
    {XMAINSCALE_TYPE_30min, 1800e9, 50, XMAINSCALE_DEG_min},
    {XMAINSCALE_TYPE_1hour, 3600e9, 50, XMAINSCALE_DEG_hour},
    {XMAINSCALE_TYPE_2hour, 7200e9, 50, XMAINSCALE_DEG_hour}
};

const int SIZE_ABSCISSSCALE = 39;

INDEXSCALETUBE IndexScaleOrdinateTube[] =
{
    {YMAINSCALE_TYPE_1u, 1e-6, 16, 6},
    {YMAINSCALE_TYPE_2u, 2e-6, 16, 6},
    {YMAINSCALE_TYPE_5u, 5e-6, 16, 6},
    {YMAINSCALE_TYPE_10u, 10e-6, 16, 5},
    {YMAINSCALE_TYPE_20u, 20e-6, 16, 5},
    {YMAINSCALE_TYPE_50u, 50e-6, 16, 5},
    {YMAINSCALE_TYPE_100u, 100e-6, 16, 4},
    {YMAINSCALE_TYPE_200u, 200e-6, 16, 4},
    {YMAINSCALE_TYPE_500u, 500e-6, 16, 4},
    {YMAINSCALE_TYPE_1m, 1e-3, 16, 3},
    {YMAINSCALE_TYPE_2m, 2e-3, 16, 3},
    {YMAINSCALE_TYPE_5m, 5e-3, 16, 3},
    {YMAINSCALE_TYPE_10m, 10e-3, 16, 2},
    {YMAINSCALE_TYPE_20m, 20e-3, 16, 2},
    {YMAINSCALE_TYPE_50m, 50e-3, 16, 2},
    {YMAINSCALE_TYPE_100m, 100e-3, 16, 1},
    {YMAINSCALE_TYPE_200m, 200e-3, 16, 1},
    {YMAINSCALE_TYPE_500m, 500e-3, 16, 1},
    {YMAINSCALE_TYPE_1, 1, 16, 0},
    {YMAINSCALE_TYPE_2, 2, 16, 0},
    {YMAINSCALE_TYPE_5, 5, 16, 0},
    {YMAINSCALE_TYPE_10, 10, 16, 0},
    {YMAINSCALE_TYPE_20, 20, 16, 0},
    {YMAINSCALE_TYPE_50, 50, 16, 0},
    {YMAINSCALE_TYPE_100, 100, 16, 0},
    {YMAINSCALE_TYPE_200, 200, 16, 0},
    {YMAINSCALE_TYPE_500, 500, 16, 0},
    {YMAINSCALE_TYPE_1k, 1e3, 16, 0},
    {YMAINSCALE_TYPE_2k, 2e3, 16, 0},
    {YMAINSCALE_TYPE_5k, 5e3, 16, 0},
    {YMAINSCALE_TYPE_10k, 10e3, 16, 0},
    {YMAINSCALE_TYPE_20k, 20e3, 16, 0},
    {YMAINSCALE_TYPE_50k, 50e3, 16, 0},
    {YMAINSCALE_TYPE_100k, 100e3, 16, 0},
    {YMAINSCALE_TYPE_200k, 200e3, 16, 0},
    {YMAINSCALE_TYPE_500k, 500e3, 16, 0},
    {YMAINSCALE_TYPE_1M, 1e6, 16, 0},
    {YMAINSCALE_TYPE_2M, 2e6, 16, 0},
    {YMAINSCALE_TYPE_5M, 5e6, 16, 0},
    {YMAINSCALE_TYPE_10M, 10e6, 16, 0},
    {YMAINSCALE_TYPE_20M, 20e6, 16, 0},
    {YMAINSCALE_TYPE_50M, 50e6, 16, 0},
    {YMAINSCALE_TYPE_100M, 100e6, 16, 0},
    {YMAINSCALE_TYPE_200M, 200e6, 16, 0},
    {YMAINSCALE_TYPE_500M, 500e6, 16, 0},
};

const int SIZE_ORDINATESCALE = 45;

bool convertTime(QString &strTime, qint64 time_ns, int precision)
{
    bool wide = false;

    qint64 time_us      = time_ns   / 1000;
    int ns              = time_ns   % 1000;
    qint64 time_ms      = time_us   / 1000;
    int us              = time_us   % 1000;
    qint64 time_sec     = time_ms   / 1000;
    int ms              = time_ms   % 1000;
    qint64 time_minutes = time_sec  / 60;
    int sec             = time_sec  % 60;
    int time_hours      = time_minutes / 60;
    int minutes         = time_minutes % 60;

    switch (precision)
    {
        case XMAINSCALE_DEG_nsec:
            if(time_hours) {
                strTime += QString("%1h:%2m:%3s %4us ").arg(time_hours, 2, 10, QLatin1Char('0')).arg(minutes, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0')).arg(1e3*ms + us);
                wide = true;
            }
            else
                if(minutes) {
                    strTime += QString("%1m:%2s %3us ").arg(minutes, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0')).arg(1e3*ms + us);
                    wide = true;
                }
                else
                    if(sec) {
                        strTime += QString("%1s %2us ").arg(sec, 2, 10, QLatin1Char('0')).arg(1e3*ms + us);
                        wide = true;
                    }
                    else
                        if(ms) {
                            strTime += QString("%1us ").arg(1e3*ms + us);
                            wide = true;
                        }
                        else
                            if(us) {
                                strTime += QString("%1us ").arg(us);
                                wide = true;
                            }
            strTime += QString("%1ns").arg(ns);
            break;

        case XMAINSCALE_DEG_usec:
            if(time_hours) {
                strTime += QString("%1h:%2m:%3s %4ms ").arg(time_hours, 2, 10, QLatin1Char('0')).arg(minutes, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0')).arg(ms);
                wide = true;
            }
            else
                if(minutes) {
                    strTime += QString("%1m:%2s %3ms ").arg(minutes, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0')).arg(ms);
                    wide = true;
                }
                else
                    if(sec) {
                        strTime += QString("%1s %2ms ").arg(sec, 2, 10, QLatin1Char('0')).arg(ms);
                        wide = true;
                    }
                    else
                        if(ms) {
                            strTime += QString("%1ms ").arg(ms);
                            wide = true;
                        }
            strTime += QString("%1us").arg(us);
            break;

        case XMAINSCALE_DEG_msec:
            if(time_hours) {
                strTime += QString("%1h:%2m:%3s ").arg(time_hours, 2, 10, QLatin1Char('0')).arg(minutes, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0'));
                wide = true;
            }
            else
                if(minutes) {
                    strTime += QString("%1m:%2s ").arg(minutes, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0'));
                    wide = true;
                }
                else
                    if(sec) {
                        strTime += QString("%1s ").arg(sec, 2, 10, QLatin1Char('0'));
                        wide = true;
                    }
            strTime += QString("%1ms").arg(ms);
            break;

        case XMAINSCALE_DEG_sec:
            if(time_hours) {
                strTime += QString("%1h:%2m:").arg(time_hours, 2, 10, QLatin1Char('0')).arg(minutes, 2, 10, QLatin1Char('0'));
                wide = true;
            }
            else
                if(minutes)
                    strTime += QString("%1m:").arg(minutes, 2, 10, QLatin1Char('0'));
            strTime += QString("%1s").arg(sec, 2, 10, QLatin1Char('0'));
            break;

        case XMAINSCALE_DEG_min:
            if(time_hours)
                strTime += QString("%1h:").arg(time_hours, 2, 10, QLatin1Char('0'));
            strTime += QString("%1m").arg(minutes, 2, 10, QLatin1Char('0'));
            break;

        case XMAINSCALE_DEG_hour:
            strTime += QString("%1h").arg(time_hours, 2, 10, QLatin1Char('0'));
            break;

        default:
            strTime += QString("%1ns").arg(time_ns);
            break;
    }
    return wide;
}

void convertTime(QString &strTime, qint64 time_ns)
{
    qint64 time_us      = time_ns   / 1000;
    int ns              = time_ns   % 1000;
    qint64 time_ms      = time_us   / 1000;
    int us              = time_us   % 1000;
    qint64 time_sec     = time_ms   / 1000;
    int ms              = time_ms   % 1000;
    qint64 time_minutes = time_sec  / 60;
    int sec             = time_sec  % 60;
    int time_hours      = time_minutes / 60;
    int minutes         = time_minutes % 60;

    if(time_hours)
        strTime += QString("%1h:%2m:%3s %4us %5ns").arg(time_hours, 2, 10, QLatin1Char('0')).arg(minutes, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0')).arg(1e3*ms + us).arg(ns);
    else
        if(minutes)
            strTime += QString("%1m:%2s %3us %4ns").arg(minutes, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0')).arg(1e3*ms + us).arg(ns);
        else
            if(sec)
                strTime += QString("%1s %2us %3ns").arg(sec, 2, 10, QLatin1Char('0')).arg(1e3*ms + us).arg(ns);
            else
                if(ms)
                    strTime += QString("%1us %2ns").arg(1e3*ms + us).arg(ns);
                else
                    if(us)
                        strTime += QString("%1us %2ns").arg(us).arg(ns);
                    else
                        strTime += QString("%1ns").arg(ns);
}

QString convertToFreq(qint64 time_ns)
{
    qint64 time_us      = time_ns   / 1000;
    int ns              = time_ns   % 1000;
    qint64 time_ms      = time_us   / 1000;
    int us              = time_us   % 1000;
    qint64 time_sec     = time_ms   / 1000;
    int ms              = time_ms   % 1000;
    qint64 time_minutes = time_sec  / 60;
    int sec             = time_sec  % 60;
    int time_hours      = time_minutes / 60;
    int minutes         = time_minutes % 60;

    if(minutes || time_hours)   // Если есть часы и минуты, то не показывает частоту
        return QString("~");

    if(sec || ms) {
        double freq = 1./time_ns;
        return QString("%1Hz").arg(1e9*freq);
    }
    else if(us) {
        double freq = 1./time_ns;
        return QString("%1kHz").arg(1e6*freq);
    }
    else if(ns) {
        double freq = 1./time_ns;
        return QString("%1MHz").arg(1e3*freq);
    }
    else
        return "";
}

ChartGraphicsAbscissTube::ChartGraphicsAbscissTube(QFont font, QColor shadowColor, QObject *parent)
    : QObject(parent),
      QGraphicsItem(),
      m_index_scale(0)
{
    m_visible_offset = 0;
    m_visible_offset_save = 0;
    m_index_scale = 0;
    m_range = {0, 0};

    m_padding = 2;
    m_mouse_pressed = false;
    m_visible_count_save = 0;
    m_pos_save = 0;

    setFlag(QGraphicsItem::ItemIsSelectable, true);

    m_brush = QBrush(QColor(100, 100, 100, 255), Qt::SolidPattern);

    m_transform.resize(MAXVISIBLECOUNTLINE);
    m_nocks.resize(MAXVISIBLECOUNTLINE);
    for (int i = 0; i < m_nocks.size(); ++i)
    {
       m_nocks[i] = new ChartGraphicsPlotNocks(font, shadowColor, this);
       m_nocks[i]->setFont(font);
       m_nocks[i]->setVisible(false);
    }

    m_nocks[0]->setText("0");
    m_nocks_height = m_nocks[0]->boundingRect().height();
    m_nocks[0]->setText("");
}

ChartGraphicsAbscissTube::~ChartGraphicsAbscissTube()
{

}

void ChartGraphicsAbscissTube::setRange(const TRange range)
{
    m_range = range;
}

void ChartGraphicsAbscissTube::getRange(TRange *range) const
{
    *range = m_range;
}

void ChartGraphicsAbscissTube::getVisibleRange(TRange *visible_range) const
{
    double step = IndexScaleAbscissTube[m_index_scale].Width;
    double visible_count = m_scene.width()/IndexScaleAbscissTube[m_index_scale].Pixels;
    double visible_width = visible_count*step;

    visible_range->min = (m_visible_offset - m_range.min);
    visible_range->max = (visible_width + m_visible_offset - m_range.min);
}

void ChartGraphicsAbscissTube::getPrecision(unsigned int* numPrecision) const
{
    *numPrecision = IndexScaleAbscissTube[m_index_scale].nDeg;
}

void ChartGraphicsAbscissTube::getStep(double *step) const
{
    *step = IndexScaleAbscissTube[m_index_scale].Width;
}

void ChartGraphicsAbscissTube::setVisibleOffset(const double offset)
{
    m_visible_offset = offset;
    if(!m_mouse_pressed)
        m_visible_offset_save = offset;
}

void ChartGraphicsAbscissTube::getVisibleOffset(double *offset) const
{
    *offset = m_visible_offset;
}

void ChartGraphicsAbscissTube::setIndexScale(const unsigned int index)
{
    if(index < SIZE_ABSCISSSCALE)
        m_index_scale = index;
}

void ChartGraphicsAbscissTube::getIndexScale(unsigned int* index) const
{
    *index = m_index_scale;
}

double ChartGraphicsAbscissTube::mapFromScene(const double x) const
{
    double step = IndexScaleAbscissTube[m_index_scale].Width;
    double visible_count = m_scene.width()/IndexScaleAbscissTube[m_index_scale].Pixels;
    double visible_width = visible_count*step;
    double scale = visible_width/m_scene.width();

    double pos = scale*(x - m_scene.x()) + m_visible_offset_save;
    return pos;
}

double ChartGraphicsAbscissTube::mapToScene(const double offset) const
{
    double step = IndexScaleAbscissTube[m_index_scale].Width;
    double visible_count = m_scene.width()/IndexScaleAbscissTube[m_index_scale].Pixels;
    double visible_width = visible_count*step;
    double scale = visible_width/m_scene.width();

    double pos = (offset - m_visible_offset_save)/scale + m_scene.x();
    return pos;
}

double ChartGraphicsAbscissTube::mapFromSceneGridCorrect(const double x) const
{
    double step = IndexScaleAbscissTube[m_index_scale].Width;
    double visible_count = m_scene.width()/IndexScaleAbscissTube[m_index_scale].Pixels;
    double visible_width = visible_count*step;
    double scale = visible_width/m_scene.width();

    double pos = scale*(x - m_scene.x()) + m_visible_offset_save;
    double pos_correct = step*round(pos/step);
    return pos_correct;
}

void ChartGraphicsAbscissTube::setBottomPadding(double padding)
{
    m_padding = padding;
}

void ChartGraphicsAbscissTube::setScene(const QRectF scene)
{
    m_scene = scene;
}

void ChartGraphicsAbscissTube::setFontBrush(const QBrush brush)
{
    for (int i = 0; i < m_nocks.size(); ++i)
        m_nocks[i]->setBrush(brush);
}

void ChartGraphicsAbscissTube::setBrush(const QBrush brush)
{
    m_brush = brush;
}

void ChartGraphicsAbscissTube::exec()
{
    double step;
    double visible_count;
    double pixels_step, pixels_offset;

    step = IndexScaleAbscissTube[m_index_scale].Width;
    visible_count = m_scene.width()/IndexScaleAbscissTube[m_index_scale].Pixels;
    double visible_width = visible_count*step;
    double scale = m_scene.width()/visible_width;
    pixels_step = IndexScaleAbscissTube[m_index_scale].Pixels;
    pixels_offset = scale * (m_visible_offset - m_range.min);
    int nDegree = IndexScaleAbscissTube[m_index_scale].nDeg;

    qint64 index_min = (m_visible_offset - m_range.min)/step;
    qint64 index_max = (visible_width + m_visible_offset - m_range.min)/step;

    if(index_min < 0)
        index_min = 0;

    visible_count++;
    if(visible_count > MAXVISIBLECOUNTLINE)
        visible_count = MAXVISIBLECOUNTLINE;

    qint64 index = index_min;
    for(int i=0; i<visible_count; i++) {

        double val = step*index;

        QString strTime;
        bool wide = convertTime(strTime, val, nDegree);

        if(wide) {
            if(index%2) {
                m_nocks[i]->setVisible(false);
            }
            else {
                m_nocks[i]->setText(strTime);
                m_nocks[i]->setVisible(true);

                m_transform[i].reset();
                m_transform[i].translate(index*pixels_step - pixels_offset - m_nocks[i]->boundingRect().width()/2, m_scene.height() - m_nocks_height - m_padding);
                m_nocks[i]->setTransform(m_transform[i]);
            }
        }
        else {
            m_nocks[i]->setText(strTime);
            m_nocks[i]->setVisible(true);

            m_transform[i].reset();
            m_transform[i].translate(index*pixels_step - pixels_offset - m_nocks[i]->boundingRect().width()/2, m_scene.height() - m_nocks_height - m_padding);
            m_nocks[i]->setTransform(m_transform[i]);
        }
        index++;
    }

    for(int i = visible_count; i < m_visible_count_save; i++)
        m_nocks[i]->setVisible(false);
    m_visible_count_save = visible_count;

    m_rect.setX(m_scene.x());
    m_rect.setWidth(m_scene.width() - 1);

    m_rect.setY(m_scene.y() + m_scene.height() - m_nocks_height - 2*m_padding);
    m_rect.setHeight(m_nocks_height + 2*m_padding - 1);

    m_boundRect.setX(m_scene.x());
    m_boundRect.setWidth(m_scene.width());

    m_boundRect.setY(m_scene.y() + m_scene.height() - m_nocks_height - 2*m_padding);
    m_boundRect.setHeight(m_nocks_height + 2*m_padding);
}

void ChartGraphicsAbscissTube::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(m_brush);
    painter->drawRect(m_rect);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}


void ChartGraphicsAbscissTube::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        setCursor(Qt::ClosedHandCursor);

        double pos = mapFromSceneGridCorrect(event->pos().x());

        m_mouse_pressed = true;
        emit mousePress(pos);
    }
}

void ChartGraphicsAbscissTube::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_mouse_pressed)
    {
        setCursor(Qt::ClosedHandCursor);

        double pos = mapFromSceneGridCorrect(event->pos().x());

        if(m_pos_save != pos) {
            emit mouseMove(pos);
            m_pos_save = pos;
        }
    }
}

void ChartGraphicsAbscissTube::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if((event->button() == Qt::LeftButton) && m_mouse_pressed)
    {
        setCursor(Qt::OpenHandCursor);

        double pos = mapFromSceneGridCorrect(event->pos().x());

        emit mouseRelease(pos);
        m_mouse_pressed = false;
    }
}

void ChartGraphicsAbscissTube::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    emit mouseWheel(event->delta()/120);
}


//*****************************************************************************************************
//********************************************ORDINATE**************************************************
//*****************************************************************************************************
ChartGraphicsOrdinateTube::ChartGraphicsOrdinateTube(QFont font, QColor shadowColor, QObject *parent)
    : QObject(parent),
      QGraphicsItem(),
      m_index_scale(0)
{
    m_visible_offset = 0;
    m_visible_offset_save = 0;
    m_index_scale = 0;
    m_range = {0, 0};

    m_left_padding = 0;
    m_border_bottom = 0;
    m_mouse_pressed = false;
    m_visible_count_save = 0;
    m_pos_save = 0;

    setFlag(QGraphicsItem::ItemIsSelectable, true);

    m_brush = QBrush(QColor(100, 100, 100, 150), Qt::SolidPattern);

    m_transform.resize(MAXVISIBLECOUNTLINE);
    m_nocks.resize(MAXVISIBLECOUNTLINE);
    for (int i = 0; i < m_nocks.size(); ++i)
    {
        m_nocks[i] = new ChartGraphicsPlotNocks(font, shadowColor, this);
        m_nocks[i]->setFont(font);
        m_nocks[i]->setVisible(false);
    }
}

ChartGraphicsOrdinateTube::~ChartGraphicsOrdinateTube()
{

}

void ChartGraphicsOrdinateTube::setRange(TRange range)
{
    m_range = range;
}

void ChartGraphicsOrdinateTube::getRange(TRange *range) const
{
    *range = m_range;
}

void ChartGraphicsOrdinateTube::getVisibleRange(TRange* visible_range) const
{
    double step = IndexScaleOrdinateTube[m_index_scale].Width;
    double visible_count = (m_scene.height()-m_border_bottom)/IndexScaleOrdinateTube[m_index_scale].Pixels;
    double visible_height = visible_count*step;

    visible_range->min = (m_visible_offset - m_range.min);
    visible_range->max = (visible_height + m_visible_offset - m_range.min);
}

void ChartGraphicsOrdinateTube::setVisibleOffset(double offset)
{
    m_visible_offset = offset;
    if(!m_mouse_pressed)
        m_visible_offset_save = offset;
}

void ChartGraphicsOrdinateTube::getVisibleOffset(double *offset) const
{
    *offset = m_visible_offset;
}

void ChartGraphicsOrdinateTube::getPrecision(int* numPrecision) const
{
    *numPrecision = IndexScaleOrdinateTube[m_index_scale].nDeg;
}

void ChartGraphicsOrdinateTube::getStep(double *step) const
{
    *step = IndexScaleOrdinateTube[m_index_scale].Width;
}

void ChartGraphicsOrdinateTube::setIndexScale(unsigned int index)
{
    if(index < SIZE_ORDINATESCALE)
        m_index_scale = index;
}

void ChartGraphicsOrdinateTube::getIndexScale(unsigned int* index) const
{
    *index = m_index_scale;
}

double ChartGraphicsOrdinateTube::mapFromScene(const double y) const
{
    double step = IndexScaleOrdinateTube[m_index_scale].Width;
    double visible_count = (m_scene.height() - m_border_bottom)/IndexScaleOrdinateTube[m_index_scale].Pixels;
    double visible_height = visible_count*step;
    double scale = visible_height/(m_scene.height() - m_border_bottom);

    double pos = scale*(m_scene.height() - m_border_bottom - y - m_scene.y()) + m_visible_offset_save;
    return pos;
}

double ChartGraphicsOrdinateTube::mapToScene(const double offset) const
{
    double step = IndexScaleAbscissTube[m_index_scale].Width;
    double visible_count = m_scene.width()/IndexScaleAbscissTube[m_index_scale].Pixels;
    double visible_width = visible_count*step;
    double scale = visible_width/(m_scene.height() - m_border_bottom);

    double pos = m_scene.height() - m_border_bottom - (offset - m_visible_offset_save)/scale + m_scene.y();
    return pos;
}

double ChartGraphicsOrdinateTube::mapFromSceneGridCorrect(const double y) const
{
    double step = IndexScaleOrdinateTube[m_index_scale].Width;
    double visible_count = (m_scene.height() - m_border_bottom)/IndexScaleOrdinateTube[m_index_scale].Pixels;
    double visible_height = visible_count*step;
    double scale = visible_height/(m_scene.height() - m_border_bottom);

    double pos = scale*(m_scene.height() - m_border_bottom - y - m_scene.y()) + m_visible_offset_save;
    double pos_correct = step*round(pos/step);
    return pos_correct;
}

void ChartGraphicsOrdinateTube::setLeftPadding(double left_padding)
{
    m_left_padding = left_padding;
}

void ChartGraphicsOrdinateTube::setScene(QRectF scene)
{
    m_scene = scene;
}

void ChartGraphicsOrdinateTube::setBorderBottom(double border_bottom)
{
    m_border_bottom = border_bottom;
}

void ChartGraphicsOrdinateTube::setFontBrush(const QBrush brush)
{
    for (int i = 0; i < m_nocks.size(); ++i)
        m_nocks[i]->setBrush(brush);
}

void ChartGraphicsOrdinateTube::setBrush(const QBrush brush)
{
    m_brush = brush;
}

void ChartGraphicsOrdinateTube::getOrdinateIndexScaleHint(int *ordinateIndexScale, TRange ordinate_range)
{
    double step;
    double visible_count;
    double visible_height;
    double height = ordinate_range.max - ordinate_range.min;
    for(int number=0; number<SIZE_ORDINATESCALE; number++) {
        step = IndexScaleOrdinateTube[number].Width;
        visible_count = (m_scene.height()-m_border_bottom)/IndexScaleOrdinateTube[number].Pixels;
        visible_height = visible_count*step;
        if(height < visible_height) {
            *ordinateIndexScale = number;
            break;
        }
    }
}

void ChartGraphicsOrdinateTube::exec()
{
    double maxPixelTextWidth = 0;
    double maxPixelTextHeight = 0;
    double step = IndexScaleOrdinateTube[m_index_scale].Width;
    double visible_count = (m_scene.height()-m_border_bottom)/IndexScaleOrdinateTube[m_index_scale].Pixels;
    double visible_height = visible_count*step;
    double scale = (m_scene.height()-m_border_bottom)/visible_height;
    double pixels_step = IndexScaleOrdinateTube[m_index_scale].Pixels;
    double pixels_offset = scale * (m_visible_offset - m_range.min);
    int nDegree = IndexScaleOrdinateTube[m_index_scale].nDeg;

    qint64 index_min = (m_visible_offset - m_range.min)/step;
    qint64 index_max = (visible_height + m_visible_offset - m_range.min)/step;

    visible_count++; // для отображения последней, крайней линии
    if(visible_count > MAXVISIBLECOUNTLINE)
        visible_count = MAXVISIBLECOUNTLINE;

    for(int i=0; i<visible_count; i++)
    {
        m_nocks[i]->setText(QString::number(m_range.min + step*(i+index_min), 'f', nDegree) + "-");
        m_nocks[i]->setVisible(true);
        if(m_nocks[i]->boundingRect().width() > maxPixelTextWidth)
        {
            maxPixelTextWidth = m_nocks[i]->boundingRect().width();
            maxPixelTextHeight = m_nocks[i]->boundingRect().height();
        }
    }

    for(int i = visible_count; i < m_visible_count_save; i++)
        m_nocks[i]->setVisible(false);
    m_visible_count_save = visible_count;


    qint64 index = index_min;
    for(int i=0; i<visible_count; i++) {
        m_transform[i].reset();
        m_transform[i].translate(m_left_padding + maxPixelTextWidth-m_nocks[i]->boundingRect().width(), m_scene.height() - m_border_bottom - (index * pixels_step + maxPixelTextHeight/2 - pixels_offset));
        m_nocks[i]->setTransform(m_transform[i]);

        index++;
    }


    m_rect.setX(m_scene.x());
    m_rect.setWidth(m_left_padding + maxPixelTextWidth - 1);

    m_rect.setY(m_scene.y());
    m_rect.setHeight(m_scene.height() - m_border_bottom - 1);

    m_boundRect.setX(m_scene.x());
    m_boundRect.setWidth(m_left_padding + maxPixelTextWidth);

    m_boundRect.setY(m_scene.y());
    m_boundRect.setHeight(m_scene.height() - m_border_bottom);
}

void ChartGraphicsOrdinateTube::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(m_brush);
    painter->drawRect(m_rect);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void ChartGraphicsOrdinateTube::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        setCursor(Qt::ClosedHandCursor);

        double pos = mapFromSceneGridCorrect(event->pos().y());

        m_mouse_pressed = true;
        emit mousePress(pos);
    }
}

void ChartGraphicsOrdinateTube::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_mouse_pressed)
    {
        setCursor(Qt::ClosedHandCursor);

        double pos = mapFromSceneGridCorrect(event->pos().y());

        if(m_pos_save != pos) {
            emit mouseMove(pos);
            m_pos_save = pos;
        }
    }
}

void ChartGraphicsOrdinateTube::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if((event->button() == Qt::LeftButton) && m_mouse_pressed)
    {
        setCursor(Qt::OpenHandCursor);

        double pos = mapFromSceneGridCorrect(event->pos().y());

        emit mouseRelease(pos);
        m_mouse_pressed = false;
    }
}

void ChartGraphicsOrdinateTube::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    emit mouseWheel(event->delta()/120);
}

//*****************************************************************************************************
//**********************************************NOCKS**************************************************
//*****************************************************************************************************

ChartGraphicsPlotNocks::ChartGraphicsPlotNocks(QFont font, QColor shadowColor, QGraphicsItem *parent)
    : QGraphicsSimpleTextItem(parent)
{
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(4.0);
    shadow->setColor(shadowColor);
    shadow->setOffset(2.0);

    setFont(font);
    setBrush(Qt::white);
    setGraphicsEffect(shadow);
}

ChartGraphicsPlotNocks::ChartGraphicsPlotNocks(QFont font, QString text, QColor shadowColor, QGraphicsItem *parent)
    : QGraphicsSimpleTextItem(text, parent)
{
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(4.0);
    shadow->setColor(shadowColor);
    shadow->setOffset(2.0);

    setFont(font);
    setBrush(Qt::white);
    setGraphicsEffect(shadow);
}

//*******************************************************************************************************
//************************************************POINT**************************************************
//*******************************************************************************************************
ChartGraphicsPlotPoint::ChartGraphicsPlotPoint(QObject *parent)
    : QObject(parent),
      QGraphicsSimpleTextItem()
{
    m_colorText = QColor(255, 255, 255, 255);
    m_pen = QPen(QColor(255, 255, 255, 255), 0, Qt::DotLine, Qt::SquareCap, Qt::BevelJoin);
    m_brush = QBrush(CHART_FORM_COLOR_DEFAULT, Qt::SolidPattern);

    m_boundEllipse = QRect(0, 0, DIAMETERPOINT, DIAMETERPOINT);
    m_boundEllipse.moveCenter(QPoint(0,0));
    m_boundRect = m_boundEllipse;
    m_spacing = 4;

    setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    setCursor(Qt::SizeVerCursor);
}

ChartGraphicsPlotPoint::ChartGraphicsPlotPoint(QGraphicsItem *item, QObject *parent)
    : QObject(parent),
      QGraphicsSimpleTextItem(item)
{
    m_colorText = QColor(255, 255, 255, 255);
    m_pen = QPen(QColor(255, 255, 255, 255), 0, Qt::DotLine, Qt::SquareCap, Qt::BevelJoin);
    m_brush = QBrush(CHART_FORM_COLOR_DEFAULT, Qt::SolidPattern);

    m_boundEllipse = QRect(0, 0, DIAMETERPOINT, DIAMETERPOINT);
    m_boundEllipse.moveCenter(QPoint(0,0));
    m_boundRect = m_boundEllipse;
    m_spacing = 4;

    setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
}

void ChartGraphicsPlotPoint::setText(const QString &strText)
{
    m_text = strText;
    m_listText = strText.split('\n');
    m_listTextRect.clear();
    float height = 0;
    float width = 0;
    foreach(QString text, m_listText) {
        QGraphicsSimpleTextItem::setText(text);
        QRectF boundTextTime = QGraphicsSimpleTextItem::boundingRect();
        height += boundTextTime.height() + m_spacing;
        if(width < boundTextTime.width())
            width = boundTextTime.width();
        m_listTextRect << boundTextTime;
    }

    m_boundText.setHeight(height);
    m_boundText.setWidth(width + 2*m_spacing);
    m_boundText.moveLeft(-width/2 - m_spacing);
    m_boundText.moveBottom(-DIAMETERPOINT/2 - m_spacing);

    height += m_spacing;
    height += DIAMETERPOINT;
    if(DIAMETERPOINT > width)
        width = DIAMETERPOINT;

    m_boundRect.setHeight(height + DIAMETERPOINT + m_spacing);
    m_boundRect.setWidth(width + 2*m_spacing);
    m_boundRect.moveLeft(-width/2 - m_spacing);
    m_boundRect.moveBottom(DIAMETERPOINT/2);
}

QString ChartGraphicsPlotPoint::text() const
{
    return m_text;
}

void ChartGraphicsPlotPoint::setColor(const QColor &color)
{
    m_pen = QPen(color, 0, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
    m_penColor = color;
}

QColor ChartGraphicsPlotPoint::color() const
{
    return m_penColor;
}

void ChartGraphicsPlotPoint::setBackgroundColor(const QColor &color)
{
    m_brush = QBrush(color, Qt::SolidPattern);
    m_brushColor = color;
}

QColor ChartGraphicsPlotPoint::backgroundColor() const
{
    return m_brushColor;
}

void ChartGraphicsPlotPoint::setActive(bool select)
{
    if(select) {
        m_pen = QPen(m_penColor, 0, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
        m_brush = QBrush(m_brushColor, Qt::SolidPattern);
        m_colorText = QColor(255, 255, 255, 255);
    }
    else {
        QColor colorPen = m_penColor;
        colorPen.setAlpha(100);
        m_pen = QPen(colorPen, 0, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
        QColor colorBrush = m_brushColor;
        colorBrush.setAlpha(0);
        m_brush = QBrush(colorBrush, Qt::SolidPattern);
        m_colorText = QColor(255, 255, 255, 100);
    }
}

QPainterPath ChartGraphicsPlotPoint::shape() const
{
    QPainterPath path;
    path.addRect(m_boundRect);
    return path;
}

void ChartGraphicsPlotPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawEllipse(m_boundEllipse);
    if(m_listText.count() != 0)
        painter->drawRoundedRect(m_boundText, 5, 5);

    painter->setPen(m_colorText);
    painter->setFont(font());
    double posY = m_boundText.top();
    for(int i=0; i<m_listText.count(); i++) {
        QString text = m_listText[i];
        posY += m_listTextRect[i].height();
        painter->drawText(-m_listTextRect[i].width()/2, posY, text);
        posY += m_spacing;
    }
}

void ChartGraphicsPlotPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPointF pos = event->scenePos();

        m_mouse_pressed = true;
        emit mousePress(pos);
    }
}

void ChartGraphicsPlotPoint::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_mouse_pressed)
    {
        QPointF pos = event->scenePos();
        emit mouseMove(pos);
    }
}

void ChartGraphicsPlotPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if((event->button() == Qt::LeftButton) && m_mouse_pressed)
    {
        QPointF pos = event->scenePos();

        emit mouseRelease(pos);
        m_mouse_pressed = false;
    }
}

void ChartGraphicsPlotPoint::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    emit mouseWheel(event->delta()/120);
}



//*******************************************************************************************************
//************************************************GRID***************************************************
//*******************************************************************************************************

ChartGraphics2DPlotGrid::ChartGraphics2DPlotGrid(QObject *parent)
    : QObject(parent),
      QGraphicsItem(),
    m_absciss_index_scale(0),
    m_ordinate_index_scale(0)
{
    m_absciss_range = {0, 0};
    m_ordinate_range = {0, 0};
    m_visible_absciss_offset = 0;
    m_visible_ordinate_offset = 0;

    m_pen = QPen(QColor(255, 255, 255, 255), 0, Qt::DotLine, Qt::SquareCap, Qt::BevelJoin);
    m_pen.setCosmetic(true);

    m_abscissLines.resize(MAXVISIBLECOUNTLINE);
    m_ordinateLines.resize(MAXVISIBLECOUNTLINE);

    m_absciss_visible_count_save = 0;
    m_ordinate_visible_count_save = 0;
}

ChartGraphics2DPlotGrid::~ChartGraphics2DPlotGrid()
{

}

void ChartGraphics2DPlotGrid::setAbscissRange(const TRange absciss_range)
{
    m_absciss_range = absciss_range;
}

void ChartGraphics2DPlotGrid::setVisibleAbscissOffset(const double offset)
{
    m_visible_absciss_offset = offset;
}

void ChartGraphics2DPlotGrid::setAbscissIndexScale(const unsigned int index)
{
    if(index < SIZE_ABSCISSSCALE)
        m_absciss_index_scale = index;
}

void ChartGraphics2DPlotGrid::setOrdinateRange(const TRange ordinate_range)
{
    m_ordinate_range = ordinate_range;
}

void ChartGraphics2DPlotGrid::setVisibleOrdinateOffset(const double offset)
{
    m_visible_ordinate_offset = offset;
}

void ChartGraphics2DPlotGrid::setOrdinateIndexScale(const unsigned int index)
{
    if(index < SIZE_ORDINATESCALE)
        m_ordinate_index_scale = index;
}

void ChartGraphics2DPlotGrid::setBorderBottom(double border_bottom)
{
    m_border_bottom = border_bottom;
}

void ChartGraphics2DPlotGrid::setScene(QRectF scene)
{
    m_scene = scene;
}

void ChartGraphics2DPlotGrid::setPen(const QPen pen)
{
    m_pen = pen;
    m_pen.setCosmetic(true);
}

void ChartGraphics2DPlotGrid::exec()
{
    // Absciss
    double absciss_step = IndexScaleAbscissTube[m_absciss_index_scale].Width;
    double absciss_visible_count = m_scene.width()/IndexScaleAbscissTube[m_absciss_index_scale].Pixels;
    double absciss_visible_width = absciss_visible_count*absciss_step;
    double absciss_scale = m_scene.width()/absciss_visible_width;

    qint64 absciss_index_min = (m_visible_absciss_offset - m_absciss_range.min)/absciss_step;
    qint64 absciss_index_max = (absciss_visible_width + m_visible_absciss_offset - m_absciss_range.min)/absciss_step;

    absciss_visible_count++;    // для отображения последней, крайней линии
    if(absciss_visible_count > MAXVISIBLECOUNTLINE)
        absciss_visible_count = MAXVISIBLECOUNTLINE;

    // Ordinate
    double ordinate_step = IndexScaleOrdinateTube[m_ordinate_index_scale].Width;
    double ordinate_visible_count = (m_scene.height()-m_border_bottom)/IndexScaleOrdinateTube[m_ordinate_index_scale].Pixels;
    double ordinate_visible_height = ordinate_visible_count*ordinate_step;
    double ordinate_scale = (m_scene.height()-m_border_bottom)/ordinate_visible_height;

    qint64 ordinate_index_min = (m_visible_ordinate_offset - m_ordinate_range.min)/ordinate_step;
    qint64 ordinate_index_max = (ordinate_visible_height + m_visible_ordinate_offset - m_ordinate_range.min)/ordinate_step;

    ordinate_visible_count++;       // для отображения последней, крайней линии
    if(ordinate_visible_count > MAXVISIBLECOUNTLINE)
        ordinate_visible_count = MAXVISIBLECOUNTLINE;

    m_boundRect.setX(m_absciss_range.min);
    m_boundRect.setWidth(absciss_visible_width + m_visible_absciss_offset - m_absciss_range.min);
    m_boundRect.setY(m_visible_ordinate_offset);
    m_boundRect.setHeight(ordinate_visible_height);

    // Absciss
    qint64 index = absciss_index_min;
    for(int i = 0; i < absciss_visible_count; i++)
    {
        if(index >= 0)
            m_abscissLines[i] = QLineF(m_boundRect.x() + absciss_step*index, m_boundRect.y(), m_boundRect.x() + absciss_step*index, m_boundRect.height() + m_boundRect.y());
        index++;
    }
    for(int i = absciss_visible_count; i < m_absciss_visible_count_save; i++) {
        m_abscissLines[i] = QLineF(0, 0, 0, 0);
    }
    m_absciss_visible_count_save = absciss_visible_count;

    // Ordinate
    index = ordinate_index_min;
    for(int i = 0; i < ordinate_visible_count; i++)
    {
        m_ordinateLines[i] = QLineF(m_boundRect.x(), ordinate_step*index + m_ordinate_range.min, m_boundRect.width() - m_boundRect.x(), ordinate_step*index + m_ordinate_range.min);
        index++;
    }
    for(int i = ordinate_visible_count; i < m_ordinate_visible_count_save; i++) {
        m_ordinateLines[i] = QLineF(0, 0, 0, 0);
    }
    m_ordinate_visible_count_save = ordinate_visible_count;

    QTransform transform;
    transform.scale(absciss_scale, -ordinate_scale);
    transform.translate(-m_visible_absciss_offset, -m_visible_ordinate_offset-ordinate_visible_height);
    setTransform(transform);
}

void ChartGraphics2DPlotGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    paintAxeGuidLines(m_abscissLines, painter, m_pen);
    paintAxeGuidLines(m_ordinateLines, painter, m_pen);
}

void ChartGraphics2DPlotGrid::paintAxeGuidLines(const QVector<QLineF> lines, QPainter *painter, const QPen &linePen)
{
    painter->setPen(linePen);
    painter->drawLines(lines);
}


//*****************************************************************************************************
//********************************************SERIES***************************************************
//*****************************************************************************************************
ChartGraphics2DGraphItem::ChartGraphics2DGraphItem(QFont font, ChartGraphicsPlotPoint *pointItem, QObject *parent)
    :QObject(parent), QGraphicsItem()
{
    m_font = font;
    m_pen = QPen (QColor(1, 245, 0, 255), 0, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
    m_pen.setCosmetic(true);
    m_spacingPoints = 6;
    m_root = false;

    m_listPointsItem.resize(MAXVISIBLECOUNTPOINTS);
    for (int i = 0; i < m_listPointsItem.size(); ++i)
    {
        m_listPointsItem[i] = new ChartGraphicsPlotPoint(this, this);
        m_listPointsItem[i]->setFont(m_font);
        m_listPointsItem[i]->setVisible(false);
    }
    m_PointItem = pointItem;
    m_PointItem->setFont(m_font);

    connect(pointItem, SIGNAL(mousePress(QPointF)), this, SLOT(pointMousePress(QPointF)));
    connect(pointItem, SIGNAL(mouseMove(QPointF)), this, SLOT(pointMouseMove(QPointF)));
    connect(pointItem, SIGNAL(mouseRelease(QPointF)), this, SLOT(pointMouseRelease(QPointF)));
    connect(pointItem, SIGNAL(mouseWheel(double)), this, SLOT(pointMouseWheel(double)));

    m_ordinateCursorMode = false;

    m_visiblePointsCount = 0;
    m_visiblePointsCountSave = 0;
    m_lowQualityVisibleCount = 1000;
    m_lowQualityEnabled = false;

    m_absciss_range = TRange{0,0};
    m_ordinate_range = TRange{0,0};

    m_visible_absciss_offset = 0;
    m_absciss_index_scale = 0;

    m_visible_ordinate_offset = 0;
    m_ordinate_index_scale = 0;

    m_border_bottom = 0;
    m_active = true;
    m_select = false;
}

ChartGraphics2DGraphItem::~ChartGraphics2DGraphItem()
{
    delete m_PointItem;

    for (int i = 0; i < m_listPointsItem.size(); ++i)
        delete m_listPointsItem[i];
}

void ChartGraphics2DGraphItem::setAbscissRange(const TRange absciss_range)
{
    m_absciss_range = absciss_range;
}

void ChartGraphics2DGraphItem::getAbscissRange(TRange *absciss_range) const
{
    *absciss_range = m_absciss_range;
}

void ChartGraphics2DGraphItem::setOrdinateRange(const TRange ordinate_range)
{
    m_ordinate_range = ordinate_range;
}

void ChartGraphics2DGraphItem::getOrdinateRange(TRange *ordinate_range) const
{
    *ordinate_range = m_ordinate_range;
}

void ChartGraphics2DGraphItem::getVisibleAbscissRange(TRange *visible_absciss_range) const
{
    double step = IndexScaleAbscissTube[m_absciss_index_scale].Width;
    double visible_count = m_scene.width()/IndexScaleAbscissTube[m_absciss_index_scale].Pixels;
    double visible_width = visible_count*step;

    visible_absciss_range->min = (m_visible_absciss_offset - m_absciss_range.min);
    visible_absciss_range->max = (visible_width + m_visible_absciss_offset - m_absciss_range.min);
}

void ChartGraphics2DGraphItem::getVisibleOrdinateRange(TRange *visible_ordinate_range) const
{
    double step = IndexScaleOrdinateTube[m_ordinate_index_scale].Width;
    double visible_count = (m_scene.height()-m_border_bottom)/IndexScaleOrdinateTube[m_ordinate_index_scale].Pixels;
    double visible_width = visible_count*step;

    visible_ordinate_range->min = m_visible_ordinate_offset;
    visible_ordinate_range->max = visible_width + m_visible_ordinate_offset;
}

void ChartGraphics2DGraphItem::setVisibleAbscissOffset(const double offset)
{
    m_visible_absciss_offset = offset;
}

void ChartGraphics2DGraphItem::getVisibleAbscissOffset(double *offset) const
{
    *offset = m_visible_absciss_offset;
}

void ChartGraphics2DGraphItem::setAbscissIndexScale(const unsigned int index)
{
    m_absciss_index_scale = index;
}

void ChartGraphics2DGraphItem::getAbscissIndexScale(unsigned int *index) const
{
    *index = m_absciss_index_scale;
}

void ChartGraphics2DGraphItem::getAbscissStep(double *step) const
{
    *step = IndexScaleAbscissTube[m_absciss_index_scale].Width;
}

void ChartGraphics2DGraphItem::getAbscissPrecision(unsigned int* numPrecision) const
{
    *numPrecision = IndexScaleAbscissTube[m_absciss_index_scale].nDeg;
}

void ChartGraphics2DGraphItem::setVisibleOrdinateOffset(const double offset)
{
    m_visible_ordinate_offset = offset;
}

void ChartGraphics2DGraphItem::getVisibleOrdinateOffset(double* offset) const
{
    *offset = m_visible_ordinate_offset;
}

void ChartGraphics2DGraphItem::setOrdinateIndexScale(const unsigned int index)
{
    if(index < SIZE_ORDINATESCALE)
        m_ordinate_index_scale = index;
}

void ChartGraphics2DGraphItem::getOrdinateIndexScale(unsigned int* index) const
{
    *index = m_ordinate_index_scale;
}

void ChartGraphics2DGraphItem::getOrdinateStep(double* step) const
{
    *step = IndexScaleOrdinateTube[m_ordinate_index_scale].Width;
}

void ChartGraphics2DGraphItem::getOrdinatePrecision(unsigned int* numPrecision) const
{
    *numPrecision = IndexScaleOrdinateTube[m_ordinate_index_scale].nDeg;
}

void ChartGraphics2DGraphItem::setRoot(const bool root)
{
    m_root = root;
}

void ChartGraphics2DGraphItem::getRoot(bool *root) const
{
    *root = m_root;
}

void ChartGraphics2DGraphItem::setUnit(const QString &strUnitName)
{
    m_UnitName = strUnitName;
    exec();
}

void ChartGraphics2DGraphItem::getUnit(QString &strUnitName) const
{
    strUnitName = m_UnitName;
}

void ChartGraphics2DGraphItem::setDevName(const QString &strName)
{
    m_DevName = strName;
}

void ChartGraphics2DGraphItem::getDevName(QString &strName) const
{
    strName = m_DevName;
}

void ChartGraphics2DGraphItem::setName(const QString strName)
{
    m_Name = strName;
}

void ChartGraphics2DGraphItem::getName(QString &strName) const
{
    strName = m_Name;
}

void ChartGraphics2DGraphItem::setMvtValueList(const QMap<ULONG, QString> &valueDecr)
{
    m_valueDecr = valueDecr;
}

void ChartGraphics2DGraphItem::setActive(const bool active)
{
    m_active = active;
}

void ChartGraphics2DGraphItem::setSelect(const bool select)
{
    m_select = select;
}

QPointF ChartGraphics2DGraphItem::mapFromScene(const QPointF &pos) const
{
    double absciss_step = IndexScaleAbscissTube[m_absciss_index_scale].Width;
    double absciss_visible_count = m_scene.width()/IndexScaleAbscissTube[m_absciss_index_scale].Pixels;
    double absciss_visible_width = absciss_visible_count*absciss_step;
    double absciss_scale = absciss_visible_width/m_scene.width();

    double ordinate_step = IndexScaleOrdinateTube[m_ordinate_index_scale].Width;
    double ordinate_visible_count = (m_scene.height() - m_border_bottom)/IndexScaleOrdinateTube[m_ordinate_index_scale].Pixels;
    double ordinate_visible_height = ordinate_visible_count*ordinate_step;
    double ordinate_scale = ordinate_visible_height/(m_scene.height() - m_border_bottom);

    double x = absciss_scale*(pos.x() - m_scene.x()) + m_visible_absciss_offset;
    double y = ordinate_scale*(m_scene.height() - m_border_bottom - pos.y() - m_scene.y()) + m_visible_ordinate_offset;

    return QPointF(x, y);
}

QPointF ChartGraphics2DGraphItem::mapToScene(const QPointF &offset) const
{
    double absciss_step = IndexScaleAbscissTube[m_absciss_index_scale].Width;
    double absciss_visible_count = m_scene.width()/IndexScaleAbscissTube[m_absciss_index_scale].Pixels;
    double absciss_visible_width = absciss_visible_count*absciss_step;
    double absciss_scale = absciss_visible_width/m_scene.width();

    double ordinate_step = IndexScaleOrdinateTube[m_ordinate_index_scale].Width;
    double ordinate_visible_count = (m_scene.height() - m_border_bottom)/IndexScaleOrdinateTube[m_ordinate_index_scale].Pixels;
    double ordinate_visible_height = ordinate_visible_count*ordinate_step;
    double ordinate_scale = ordinate_visible_height/(m_scene.height() - m_border_bottom);

    double x = (offset.x() - m_visible_absciss_offset)/absciss_scale + m_scene.x();
    double y = m_scene.height() - m_border_bottom - (offset.y() - m_visible_ordinate_offset)/ordinate_scale + m_scene.y();

    return QPointF(x, y);
}

QPointF ChartGraphics2DGraphItem::mapFromSceneGridCorrect(const QPointF &pos) const
{
    double absciss_step = IndexScaleAbscissTube[m_absciss_index_scale].Width;
    double absciss_visible_count = m_scene.width()/IndexScaleAbscissTube[m_absciss_index_scale].Pixels;
    double absciss_visible_width = absciss_visible_count*absciss_step;
    double absciss_scale = absciss_visible_width/m_scene.width();

    double ordinate_step = IndexScaleOrdinateTube[m_ordinate_index_scale].Width;
    double ordinate_visible_count = (m_scene.height() - m_border_bottom)/IndexScaleOrdinateTube[m_ordinate_index_scale].Pixels;
    double ordinate_visible_height = ordinate_visible_count*ordinate_step;
    double ordinate_scale = ordinate_visible_height/(m_scene.height() - m_border_bottom);

    double x = absciss_scale*(pos.x() - m_scene.x()) + m_visible_absciss_offset;
    double y = ordinate_scale*(m_scene.height() - m_border_bottom - pos.y() - m_scene.x()) + m_visible_ordinate_offset;

    double x_correct = absciss_step*round(x/absciss_step);
    double y_correct = ordinate_step*round(y/ordinate_step);

    return QPointF(x_correct, y_correct);
}

QSizeF ChartGraphics2DGraphItem::mapFromScene(const QSizeF &size) const
{
    double absciss_step = IndexScaleAbscissTube[m_absciss_index_scale].Width;
    double absciss_visible_count = m_scene.width()/IndexScaleAbscissTube[m_absciss_index_scale].Pixels;
    double absciss_visible_width = absciss_visible_count*absciss_step;
    double absciss_scale = absciss_visible_width/m_scene.width();

    double ordinate_step = IndexScaleOrdinateTube[m_ordinate_index_scale].Width;
    double ordinate_visible_count = (m_scene.height() - m_border_bottom)/IndexScaleOrdinateTube[m_ordinate_index_scale].Pixels;
    double ordinate_visible_height = ordinate_visible_count*ordinate_step;
    double ordinate_scale = ordinate_visible_height/(m_scene.height() - m_border_bottom);

    double width = absciss_scale*size.width();
    double heigth = ordinate_scale*size.height();

    return QSizeF(width, heigth);
}

void ChartGraphics2DGraphItem::setHintVisibleCount(const qsizetype count)
{
    m_lowQualityVisibleCount = count;
}

void ChartGraphics2DGraphItem::getPointItem(ChartGraphicsPlotPoint **item) const
{
    *item = m_PointItem;
}

bool cmp(const QPointF &a, const QPointF &b) {
    return a.x() <= b.x();
}

void ChartGraphics2DGraphItem::setData(const QList<QPointF> &ordinate, const QMap<qreal, ULONG> &status)
{    
    m_poligon = ordinate;
    m_status = status;
}

QRectF ChartGraphics2DGraphItem::boundingRect() const
{
    return m_boundRect;
}

void ChartGraphics2DGraphItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setClipRect(boundingRect());

    if(m_lowQualityEnabled)
        painter->setRenderHint(QPainter::Antialiasing, false);
    else
        painter->setRenderHint(QPainter::Antialiasing, true);

    painter->setPen(m_pen);
    painter->drawPolyline(m_poligonPaint);
}

bool ChartGraphics2DGraphItem::OnSetLastPoint(const QPolygonF::Iterator &itFound, const ULONG status, const bool visibleName, const bool visibleValue, const bool visibleTime, const bool visibleError)
{
    const int nAbscissDegree = IndexScaleAbscissTube[m_absciss_index_scale].nDeg;

    QString text;
    if(visibleName)
        text += m_Name + "\n";
    if(visibleValue) {
        QString strValue;
        const float val = (*itFound).y();
        if(m_valueDecr.count() != 0)
            strValue = m_valueDecr[val];
        else
            strValue = QString::number(val) + " " + m_UnitName;
        text += strValue + "\n";
    }
    if(visibleTime) {
        QString strTime;
        const float time = (*itFound).x();
        convertTime(strTime, time, nAbscissDegree);
        text += strTime + "\n";
    }
    if(visibleError && !SUCCEDED(status))
        text += ErrorToString(status);

    QRectF rectPoint;
    if(FAILED(status))
        rectPoint = OnPrintLastPoint(text, CHART_FORM_COLOR_FAULT, (*itFound));
    else
        rectPoint = OnPrintLastPoint(text, CHART_FORM_COLOR_DEFAULT, (*itFound));

    return true;
}

bool ChartGraphics2DGraphItem::OnAddPoint(QRectF &rectPoint, const QPolygonF::Iterator &itFound, const ULONG status, const bool visibleName, const bool visibleValue, const bool visibleTime, const bool visibleError)
{
    const int nAbscissDegree = IndexScaleAbscissTube[m_absciss_index_scale].nDeg;

    QString text;
    if(visibleName)
        text += m_Name + "\n";
    if(visibleValue) {
        QString strValue;
        const float val = (*itFound).y();
        if(m_valueDecr.count() != 0)
            strValue = m_valueDecr[val];
        else
            strValue = QString::number(val) + " " + m_UnitName;
        text += strValue + "\n";
    }
    if(visibleTime) {
        QString strTime;
        const float time = (*itFound).x();
        convertTime(strTime, time, nAbscissDegree);
        text += strTime + "\n";
    }
    if(visibleError && !SUCCEDED(status))
        text += ErrorToString(status);

    if(FAILED(status))
        rectPoint = OnPrintPoint(text, CHART_FORM_COLOR_FAULT, (*itFound));
    else
        rectPoint = OnPrintPoint(text, CHART_FORM_COLOR_DEFAULT, (*itFound));

    m_visiblePointsCount++;
    if(m_visiblePointsCount > MAXVISIBLECOUNTPOINTS) {
        m_visiblePointsCount = MAXVISIBLECOUNTPOINTS;
        return false;
    }
    return true;
}

QRectF ChartGraphics2DGraphItem::OnPrintLastPoint(const QString &strText, const QColor &color, const QPointF &pos)
{
    QPointF posToScene = mapToScene(pos);

    m_PointItem->setText(strText);
    m_PointItem->setBackgroundColor(color);
    m_PointItem->setPos(posToScene);
    m_PointItem->setVisible(true);

    QRectF rect = m_PointItem->boundingRect();
    rect.setWidth(rect.width() + m_spacingPoints);
    rect.setHeight(rect.height() + m_spacingPoints);
    QSizeF sizeFromSeries = mapFromScene(rect.size());
    QRectF rectFromSeries = QRectF(pos, sizeFromSeries);
    return rectFromSeries;
}

QRectF ChartGraphics2DGraphItem::OnPrintPoint(const QString &strText, const QColor &color, const QPointF &pos)
{
    m_listPointsItem[m_visiblePointsCount]->setText(strText);
    m_listPointsItem[m_visiblePointsCount]->setBackgroundColor(color);
    m_listPointsItem[m_visiblePointsCount]->setPos(pos);
    m_listPointsItem[m_visiblePointsCount]->setVisible(true);

    QRectF rect = m_listPointsItem[m_visiblePointsCount]->boundingRect();
    rect.setWidth(rect.width() + m_spacingPoints);
    rect.setHeight(rect.height() + m_spacingPoints);
    QSizeF sizeFromSeries = mapFromScene(rect.size());
    QRectF rectFromSeries = QRectF(pos, sizeFromSeries);
    return rectFromSeries;
}

void ChartGraphics2DGraphItem::OnGetFirstStatus(qreal *offset, ULONG *status) const
{
    if(m_status.count() != 0) {
        QMap<qreal, ULONG>::const_iterator it = m_status.begin();
        *offset = it.key();
        *status = it.value();
    }
}

void ChartGraphics2DGraphItem::OnGetFirstStatus(ULONG *status) const
{
    if(m_status.count() != 0) {
        QMap<qreal, ULONG>::const_iterator it = m_status.begin();
        *status = it.value();
    }
}

void ChartGraphics2DGraphItem::OnGetLastStatus(qreal *offset, ULONG *status) const
{
    if(m_status.count() != 0) {
        QMap<qreal, ULONG>::const_iterator it = m_status.end();
        it--;
        *offset = it.key();
        *status = it.value();
    }
}

bool ChartGraphics2DGraphItem::OnFoundPoligon(QPolygonF::Iterator &itFound, const QPolygonF::Iterator &itStart, const QPolygonF::Iterator &itStop, const qreal offset) const
{
    QPolygonF::Iterator it = std::upper_bound(itStart, itStop, QPointF{offset, 0}, cmp);
    if(it != itStop) {
        itFound = it;
        return true;
    }
    else
        return false;
}

bool ChartGraphics2DGraphItem::OnUpperStatus(const qreal offset, qreal *pos, ULONG *status) const
{
    QMap<qreal, ULONG>::const_iterator it = m_status.upperBound(offset);
    if(it != m_status.end()) {
        *status = it.value();
        *pos = it.key();
        return true;
    }
    else
        return false;
}

bool ChartGraphics2DGraphItem::OnLowerStatus(const qreal offset, qreal *pos, ULONG *status) const
{
    QMap<qreal, ULONG>::const_iterator it = m_status.lowerBound(offset);
    if(it != m_status.end()) {
        *status = it.value();
        *pos = it.key();
        return true;
    }
    else
        return false;
}


void ChartGraphics2DGraphItem::setColor(const QColor &color)
{
    m_color = color;

    foreach(ChartGraphicsPlotPoint *point, m_listPointsItem)
        point->setColor(color);
    m_PointItem->setColor(color);
    m_pen = QPen(m_color, 0);
}

void ChartGraphics2DGraphItem::setBorderBottom(const double border_bottom)
{
    m_border_bottom = border_bottom;
}

void ChartGraphics2DGraphItem::setScene(const QRectF &scene)
{
    m_scene = scene;
}

void ChartGraphics2DGraphItem::getScene(QRectF &scene) const
{
    scene = m_scene;
}

void ChartGraphics2DGraphItem::exec()
{
// Absciss series
    double absciss_step = IndexScaleAbscissTube[m_absciss_index_scale].Width;
    double absciss_visible_count = m_scene.width()/IndexScaleAbscissTube[m_absciss_index_scale].Pixels;
    double absciss_visible_width = absciss_visible_count*absciss_step;
    double absciss_scale = m_scene.width()/absciss_visible_width;

    m_boundRect.setX(m_absciss_range.min);
    m_boundRect.setWidth(absciss_visible_width + m_visible_absciss_offset - m_absciss_range.min);

// Ordinate series
    double ordinate_step = IndexScaleOrdinateTube[m_ordinate_index_scale].Width;
    double ordinate_visible_count = (m_scene.height() - m_border_bottom)/IndexScaleOrdinateTube[m_ordinate_index_scale].Pixels;
    double ordinate_visible_height = ordinate_visible_count*ordinate_step;
    double ordinate_scale = (m_scene.height() - m_border_bottom)/ordinate_visible_height;

    m_boundRect.setY(m_visible_ordinate_offset);
    m_boundRect.setHeight(ordinate_visible_height);

// Поиск видимой области
    TRange visible_absciss_range;
    getVisibleAbscissRange(&visible_absciss_range);
    QPolygonF::Iterator itVisibleStart = std::upper_bound(m_poligon.begin(), m_poligon.end(), QPointF{visible_absciss_range.min, 0}, cmp);
    QPolygonF::Iterator itVisibleEnd = std::lower_bound(m_poligon.begin(), m_poligon.end(), QPointF{visible_absciss_range.max, 0}, cmp);
    QPolygonF::Iterator itVisibleStop = itVisibleEnd - 1;

    qsizetype visibleCount = itVisibleEnd - itVisibleStart;
    QPolygonF::Iterator itPoligonStop =  m_poligon.end() - 1;
    QPolygonF::Iterator itPoligonPaintStart = itVisibleStart;
    QPolygonF::Iterator itPoligonPaintEnd = itVisibleEnd;

    if(itPoligonPaintStart != m_poligon.begin())       // Немного расширим видимые границы графика
        itPoligonPaintStart--;
    if(itPoligonPaintEnd != m_poligon.end())           // Немного расширим видимые границы графика
        itPoligonPaintEnd++;

    m_poligonPaint.clear();
    QPolygonF::Iterator it = itPoligonPaintStart;
    if((m_poligon.count() != 0) && (visibleCount != 0)) {
        if(visibleCount == m_poligon.count()) {             // Видим весь полигон
            m_poligonPaint = m_poligon;
            m_lowQualityEnabled = false;
        }
        else {
            if(visibleCount < m_lowQualityVisibleCount) {  // Если количество точек в допустимой
                while(it != itPoligonPaintEnd)
                    m_poligonPaint << *it++;
                m_lowQualityEnabled = false;
            }
            else {                                          // Выбираем точки из массива с шагом
                int step = visibleCount/m_lowQualityVisibleCount;
                while(it < itPoligonPaintEnd) {
                    m_poligonPaint << *it;
                    it += step;
                }
                m_lowQualityEnabled = true;
            }
        }
    }

    if(m_activeSave != m_active) {
        if(m_active)
            m_pen = QPen(m_color, 0);
        else
            m_pen = QPen(QColor(CHART_FORM_COLOR_SERIES_DEFAULT), 0);

        for (int i = 0; i < m_listPointsItem.size(); ++i)
            m_listPointsItem[i]->setActive(m_active);
        m_PointItem->setActive(m_active);

        m_activeSave = m_active;
    }

// Режим отображения точек
    m_visiblePointsCount = 0;
    if(visibleCount > 0) {
        bool visibleAllPoints = true;
        bool visibleErrorPoints = false;

        if(visibleCount < m_lowQualityVisibleCount) {
            QPolygonF::Iterator it = itVisibleStart;
            double lastX = 0;
            while(it != itVisibleEnd) {
                if(((*it).x() - lastX) < absciss_step)                       // Проверка шага данных и текущей сетки
                    visibleAllPoints = false;
                lastX = (*it).x();
                it++;
            }
        }
        else
            visibleAllPoints = false;

        ULONG status = S_OK;
        qreal posPoligon = 0;
        QMap<qreal, ULONG>::const_iterator itStatus = m_status.lowerBound(itVisibleStart->x());
        QMap<qreal, ULONG>::const_iterator itStatusStop = m_status.upperBound(itVisibleStop->x());
        while(itStatus != itStatusStop) {
            if(!SUCCEDED(itStatus.value())) {
                visibleErrorPoints = true;
                break;
            }
            itStatus++;
        }

        qreal offset = 0;
        posPoligon = 0;
        status = S_OK;
        if(visibleErrorPoints) {                                            // Режим поиска и отображения ошибок
            OnLowerStatus(itVisibleStart->x(), &posPoligon, &status);       // Находим первый статус в видимиом диапазоне полигона
            QPolygonF::Iterator itFound;
            QRectF rectPoint;
            if(OnFoundPoligon(itFound, itVisibleStart, itVisibleEnd, posPoligon)) {
                bool res = OnAddPoint(rectPoint, itFound, status, true, true, true, true);     // Создать точку
                if(res) {
                    offset = (*itFound).x() + rectPoint.width();
                    while(1) {
                        if(OnLowerStatus(offset, &posPoligon, &status)) {
                            if(OnFoundPoligon(itFound, itVisibleStart, itVisibleEnd, posPoligon)) {
                                res = OnAddPoint(rectPoint, itFound, status, true, true, true, true);
                                if(!res)
                                    break;
                                offset = (*itFound).x() + rectPoint.width();
                            }
                            else
                                break;
                        }
                        else
                            break;
                    }
                }
            }
        }
        else if(visibleAllPoints || m_select) {                                                 // Режим отображения всех точек
            QRectF rectPoint;
            bool res = OnAddPoint(rectPoint, itVisibleStart, S_OK, true, true, true, true);     // Добавить точку
            if(res) {
                offset = (*itVisibleStart).x() + rectPoint.width();
                while(1) {
                    QPolygonF::Iterator itFound;
                    if(OnFoundPoligon(itFound, itVisibleStart, itVisibleEnd, offset)) {
                        res = OnAddPoint(rectPoint, itFound, S_OK, true, true, true, true);
                        if(!res)
                            break;
                        offset =  (*itFound).x() + rectPoint.width();
                    }
                    else
                        break;
                }
            }
        }

        bool timeVisible = false;
        if((m_visiblePointsCount == 1) && !visibleErrorPoints) {
            m_visiblePointsCount = 0;                                           // В режиме одной точки, скрываем точку в листе, для вывода m_PointItem
            m_listPointsItem[0]->setVisible(false);
            timeVisible = true;
        }

        OnGetLastStatus(&posPoligon, &status);
        if(posPoligon == itPoligonStop->x())                                    // Время массима статуса совпадает с полигоном
            OnSetLastPoint(itPoligonStop, status, true, true, timeVisible, true);// Создаем последнюю точку
        else
            OnSetLastPoint(itPoligonStop, S_OK, true, true, timeVisible, true);  // Создаем последнюю точку
    }
    else
        m_PointItem->setVisible(false);

    for(int i = m_visiblePointsCount; i < m_visiblePointsCountSave; i++)
        m_listPointsItem[i]->setVisible(false);
    m_visiblePointsCountSave = m_visiblePointsCount;

// Преобразование сцены
    QTransform transform;
    transform.scale(absciss_scale, -ordinate_scale);
    transform.translate(-m_visible_absciss_offset, -m_visible_ordinate_offset-ordinate_visible_height);
    setTransform(transform);

    emit updateSeriesChanged();
}

void ChartGraphics2DGraphItem::pointMousePress(const QPointF &pos)
{
    m_mouseOffset = mapFromSceneGridCorrect(pos);
    emit Select();
}

void ChartGraphics2DGraphItem::pointMouseMove(const QPointF &pos)
{
    double mouseOffset = m_mouseOffset.y() - mapFromSceneGridCorrect(pos).y();

    if(m_mouseOffsetSave != mouseOffset) {
        double offset;
        getVisibleOrdinateOffset(&offset);

        emit VisibleMoveChanged(offset + mouseOffset);

        m_mouseOffsetSave = mouseOffset;
    }
}

void ChartGraphics2DGraphItem::pointMouseRelease(const QPointF &pos)
{
    double mouseOffset = m_mouseOffset.y() - mapFromSceneGridCorrect(pos).y();

    double offset;
    getVisibleOrdinateOffset(&offset);

    emit VisibleOffsetChanged(offset + mouseOffset);
}

void ChartGraphics2DGraphItem::pointMouseWheel(const double)
{

}

void ChartGraphics2DGraphItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_root)
        update();
    else
        QGraphicsItem::mousePressEvent(event);

    emit ClearSelect();
}

void ChartGraphics2DGraphItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void ChartGraphics2DGraphItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

void ChartGraphics2DGraphItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    QGraphicsItem::wheelEvent(event);
}

//*****************************************************************************************************
//********************************************LEGEND***************************************************
//*****************************************************************************************************
ChartGraphics2DLegend::ChartGraphics2DLegend(QFont font, QColor shadowColor, QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    m_font = font;

    m_pen = QPen (QColor(0, 0, 0, 70), 0, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
    m_brush = QBrush(QColor(0, 0, 0, 70), Qt::SolidPattern);


    m_transform.resize(MAXCOUNTLEGEND);
    m_nocks.resize(MAXCOUNTLEGEND);
    m_lines.resize(MAXCOUNTLEGEND);
    m_pens.resize(MAXCOUNTLEGEND);
    for (int i = 0; i < m_nocks.size(); ++i)
    {
        m_nocks[i] = new ChartGraphicsPlotNocks(font, shadowColor, this);
        m_nocks[i]->setFont(m_font);
        m_nocks[i]->setBrush(m_fontBrush);
        m_lines[i].resize(2);
    }

    m_nocks[0]->setText("0");
    m_nocks_height = m_nocks[0]->boundingRect().height();
    m_nocks[0]->setText("");

    m_left_border = 0;
    m_countLegend = 0;
    m_iniClear = false;
}

ChartGraphics2DLegend::~ChartGraphics2DLegend()
{

}

void ChartGraphics2DLegend::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void ChartGraphics2DLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawRect(m_boundRect);
    for (int i = 0; i < m_countLegend; ++i) {
        painter->setPen(m_pens[i]);
        painter->drawLines(m_lines[i]);
    }
}

void ChartGraphics2DLegend::setLeftBorder(double left_border)
{
    m_left_border = left_border + 1;    // +1 зазор
}

void ChartGraphics2DLegend::setBorderBottom(double border_bottom)
{
    m_border_bottom = border_bottom;
}

void ChartGraphics2DLegend::setScene(QRectF scene)
{
    m_scene = scene;
}

void ChartGraphics2DLegend::setFontBrush(const QBrush brush)
{
    m_fontBrush = brush;

    for (int i = 0; i < m_nocks.size(); ++i)
        m_nocks[i]->setBrush(m_fontBrush);
}

void ChartGraphics2DLegend::addLegend(QString legend, QColor color)
{
    if(m_countLegend < m_nocks.count()) {
        m_nocks[m_countLegend]->setText(legend);
        m_nocks[m_countLegend]->setVisible(true);

        QPen pen = QPen(color, 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
        m_pens[m_countLegend] = pen;
    }
    m_countLegend++;
}

void ChartGraphics2DLegend::clearLegend()
{
    for (int i=0; i < m_countLegend; ++i) {
        m_lines[i][0].setLine(0, 0, 0, 0);
        m_lines[i][1].setLine(0, 0, 0, 0);
    }

    for (int i = 0; i < m_countLegend; ++i)
        m_nocks[i]->setVisible(false);

    m_iniClear = true;
}

void ChartGraphics2DLegend::exec()
{
    for(int i = 0; i < m_countLegend; i++)
    {
        double textWidth = m_nocks[i]->boundingRect().width();
        double textHeight = m_nocks[i]->boundingRect().height();

        QLineF lineFirst;
        lineFirst.setLine(m_left_border + LEGEND_PADDING, i*m_nocks_height + textHeight/2, m_left_border + LEGEND_PADDING + LEGEND_LINE_WIDTH, i*m_nocks_height + textHeight/2);
        QLineF lineSecond;
        lineSecond.setLine(m_left_border + LEGEND_LINE_WIDTH + textWidth + 3*LEGEND_PADDING, i*m_nocks_height + textHeight/2, m_left_border + 2*LEGEND_LINE_WIDTH + textWidth + 3*LEGEND_PADDING, i*m_nocks_height + textHeight/2);


        m_transform[i].reset();
        m_transform[i].translate(m_left_border + LEGEND_LINE_WIDTH + 2*LEGEND_PADDING, i*m_nocks_height);
        m_nocks[i]->setTransform(m_transform[i]);

        m_lines[i][0] = lineFirst;
        m_lines[i][1] = lineSecond;
    }

    double maxPixelTextWidth = 0;
    double sumPixelTextHeight = 0;
    for(int i = 0; i < m_countLegend; i++)
    {
        if(m_nocks[i]->boundingRect().width() > maxPixelTextWidth)
            maxPixelTextWidth = m_nocks[i]->boundingRect().width();

        sumPixelTextHeight += m_nocks[i]->boundingRect().height();
    }

    maxPixelTextWidth += 2*LEGEND_LINE_WIDTH + 4*LEGEND_PADDING;

    m_boundRect.setX(m_scene.x() + m_left_border);
    m_boundRect.setWidth(maxPixelTextWidth);

    m_boundRect.setY(m_scene.y());
    m_boundRect.setHeight(sumPixelTextHeight);

    if(m_iniClear) {
        m_iniClear = false;
        m_countLegend = 0;
    }
}

//*****************************************************************************************************
//*****************************************MESSAGES***************************************************
//*****************************************************************************************************
ChartGraphicsMessages::ChartGraphicsMessages(QFont font, QColor shadowColor, QObject *parent)
    : QObject(parent),
      QGraphicsItem(),
      m_index_scale(0)
{
    m_visible_offset = 0;
    m_range = {0, 0};

    m_font = font;

    m_padding = 2;
    m_bottom_border = 0;

    setFlag(QGraphicsItem::ItemIsSelectable, true);

    m_brush = QBrush(QColor(100, 100, 100, 255), Qt::SolidPattern);

    m_transform.resize(MAXCOUNTMESSAGES);
    m_nocks.resize(MAXCOUNTMESSAGES);
    m_time_ns.resize(MAXCOUNTMESSAGES);
    for (int i = 0; i < m_nocks.size(); ++i)
    {
       m_nocks[i] = new ChartGraphicsPlotNocks(font, shadowColor, this);
       m_nocks[i]->setFont(m_font);
    }

    m_nocks[0]->setText("0");
    m_nocks_height = m_nocks[0]->boundingRect().height();
    m_nocks[0]->setText("");

    m_count = 0;
}

ChartGraphicsMessages::~ChartGraphicsMessages()
{

}

void ChartGraphicsMessages::setFontBrush(const QBrush brush)
{
    for (int i = 0; i < m_nocks.size(); ++i)
        m_nocks[i]->setBrush(brush);
}

void ChartGraphicsMessages::setBrush(const QBrush brush)
{
    m_brush = brush;
}

void ChartGraphicsMessages::setBottomBorder(double border)
{
    m_bottom_border = border;
}

void ChartGraphicsMessages::setScene(QRectF scene)
{
    m_scene = scene;
}

void ChartGraphicsMessages::addMessage(quint64 time, QString name, QColor color)
{
    if(m_count < m_nocks.count()) {
        m_nocks[m_count]->setText(name);
        m_nocks[m_count]->setVisible(true);
        m_nocks[m_count]->setBrush(color);

        m_time_ns[m_count] = time;
    }
    m_count++;
}
void ChartGraphicsMessages::clear()
{
    m_count = 0;

    for (int i = 0; i < m_nocks.size(); ++i)
        m_nocks[i]->setVisible(false);
}

void ChartGraphicsMessages::setRange(const TRange range)
{
    m_range = range;
}

void ChartGraphicsMessages::setVisibleOffset(double offset)
{
    m_visible_offset = offset;
}

void ChartGraphicsMessages::setIndexScale(int index)
{
    m_index_scale = index;
}

void ChartGraphicsMessages::exec()
{
    double absciss_offset;
    double ordinate_offset;

    // Absciss
    double absciss_step = IndexScaleAbscissTube[m_index_scale].Width;
    double absciss_visible_count = m_scene.width()/IndexScaleAbscissTube[m_index_scale].Pixels;
    double absciss_visible_width = absciss_visible_count*absciss_step;
    double absciss_scale = m_scene.width()/absciss_visible_width;

    m_boundRect.setX(m_range.min);
    m_boundRect.setWidth(absciss_visible_width + m_visible_offset - m_range.min);

    absciss_offset = (m_range.min - m_visible_offset) * absciss_scale;

    // Height
    m_boundRect.setY(m_scene.height() - m_bottom_border);
    m_boundRect.setHeight(m_nocks_height + m_padding);

    ordinate_offset = m_scene.height() - m_bottom_border - m_nocks_height - m_padding;

    for(int i=0; i<m_count; i++) {
        m_transform[i].reset();
        m_transform[i].translate(m_time_ns[i] - m_nocks[i]->boundingRect().width()/absciss_scale/2, 0);
        m_nocks[i]->setTransform(m_transform[i]);
    }

    QTransform transform;
        transform.translate(absciss_offset, ordinate_offset);
        transform.scale(absciss_scale, -1);
    setTransform(transform);
}

void ChartGraphicsMessages::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(m_brush);
    painter->drawRect(m_boundRect);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}


