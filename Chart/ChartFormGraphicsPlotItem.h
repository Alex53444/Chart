#ifndef CHARTGRAPHICSPLOTITEM_H
#define CHARTGRAPHICSPLOTITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStaticText>
#include <qmath.h>
#include <QTime>
#include <QMap>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QWheelEvent>
#include "Types.h"


class ChartGraphics2DPlotGrid;
class ChartGraphicsMainLine;
class ChartGraphicsPlotNocks;
class ChartGraphics2DGraphItem;
class ChartGraphics2DLegend;


#define MAXVISIBLECOUNTLINE 60
#define MAXCOUNTMESSAGES 255
#define MAXCOUNTLEGEND  255
#define MAXVISIBLECOUNTPOINTS 60

#define POINTS_WIDTH 50                 // разрешенная ширина под текст точки
#define DIAMETERPOINT 5

bool convertTime(QString &strTime, qint64 time_ns, int precision);
void convertTime(QString &strTime, qint64 time_ns);
QString convertToFreq(qint64 time_ns);

//***************************************Absciss****************************************************
class ChartGraphicsAbscissTube: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ChartGraphicsAbscissTube(QFont, QColor shadowColor, QObject *parent = nullptr);
    ~ChartGraphicsAbscissTube();

    void setRange(const TRange);
    void getRange(TRange*) const;
    void getVisibleRange(TRange*) const;
    void getPrecision(unsigned int*) const;
    void getStep(double*) const;
    void setVisibleOffset(const double);
    void getVisibleOffset(double*) const;
    void setIndexScale(const unsigned int);
    void getIndexScale(unsigned int*) const;
    double mapFromScene(const double) const;
    double mapToScene(const double) const;
    double mapFromSceneGridCorrect(const double) const;

    void setBottomPadding(const double);
    void setScene(const QRectF);
    void setFontBrush(const QBrush);
    void setBrush(const QBrush);

    QRectF boundingRect()const {return m_boundRect;}
    void exec();


private:
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    QVector<ChartGraphicsPlotNocks*> m_nocks;
    QVector<QTransform> m_transform;
    QGraphicsDropShadowEffect *m_shadow;

    QBrush m_brush;
    TRange m_range;
    double m_visible_offset;
    double m_visible_offset_save;
    unsigned int m_index_scale;
    QRectF m_boundRect;
    QRectF m_rect;
    double m_padding;
    double m_nocks_height;
    QRectF m_scene;
    bool m_mouse_pressed;
    double m_pos_save;
    double m_visible_count_save;

signals:
    void mousePress(double);
    void mouseMove(double);
    void mouseRelease(double);
    void mouseWheel(double);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
};

//***************************************Ordinate****************************************************
class ChartGraphicsOrdinateTube: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ChartGraphicsOrdinateTube(QFont font, QColor shadowColor, QObject *parent = nullptr);
    ~ChartGraphicsOrdinateTube();

    void setRange(const TRange);
    void getRange(TRange*) const;
    void getVisibleRange(TRange*) const;
    void setVisibleOffset(const double);
    void getVisibleOffset(double*) const;
    void getPrecision(int*) const;
    void getStep(double*) const;
    void setIndexScale(const unsigned int);
    void getIndexScale(unsigned int*) const;
    double mapFromScene(const double) const;
    double mapToScene(const double) const;
    double mapFromSceneGridCorrect(const double) const;

    void setLeftPadding(const double);
    void setScene(const QRectF);
    void setBorderBottom(const double);
    void setFontBrush(const QBrush);
    void setBrush(const QBrush);
    void getOrdinateIndexScaleHint(int *ordinateIndexScale, TRange ordinate_range);

    QRectF boundingRect()const {return m_boundRect;}
    void exec();


private:
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    QVector<ChartGraphicsPlotNocks*> m_nocks;
    QVector<QTransform> m_transform;
    QGraphicsDropShadowEffect *m_shadow;

    QPen m_pen;
    QBrush m_brush;
    TRange m_range;
    double m_visible_offset;
    double m_visible_offset_save;
    unsigned int m_index_scale;
    QRectF m_boundRect;
    QRectF m_rect;
    double m_left_padding;
    double m_border_bottom;
    QRectF m_scene;
    bool m_mouse_pressed;
    double m_pos_save;
    double m_visible_count_save;

signals:
    void mousePress(double);
    void mouseMove(double);
    void mouseRelease(double);
    void mouseWheel(double);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void wheelEvent(QGraphicsSceneWheelEvent*);

};

//************************************NOCKS**************************************************
class ChartGraphicsPlotNocks: public QGraphicsSimpleTextItem
{
public:
    ChartGraphicsPlotNocks(QFont font, QColor shadowColor, QGraphicsItem *parent=nullptr);
    ChartGraphicsPlotNocks(QFont font, QString text, QColor shadowColor, QGraphicsItem *parent=nullptr);

};

//************************************POINT**************************************************
class ChartGraphicsPlotPoint: public QObject, public QGraphicsSimpleTextItem
{
    Q_OBJECT
public:
    ChartGraphicsPlotPoint(QObject *parent = nullptr);
    ChartGraphicsPlotPoint(QGraphicsItem *item=nullptr, QObject *parent = nullptr);
    void setText(const QString&);
    QString text() const;
    void setColor(const QColor&);
    QColor color() const;
    void setBackgroundColor(const QColor&);
    QColor backgroundColor() const;
    void setActive(bool);
    QRectF boundingRect() const {return m_boundRect;}
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void wheelEvent(QGraphicsSceneWheelEvent*);

signals:
    void mousePress(QPointF);
    void mouseMove(QPointF);
    void mouseRelease(QPointF);
    void mouseWheel(double);

private:
    QPen m_pen;
    QColor m_penColor;
    QColor m_colorText;
    QBrush m_brush;
    QColor m_brushColor;
    QRectF m_boundRect;
    QRectF m_boundText;
    QRectF m_boundEllipse;
    QString m_text;
    QList<QString> m_listText;
    QList<QRectF> m_listTextRect;
    QPainterPath m_path;
    int m_spacing;
    bool m_mouse_pressed;
};


//***************************************GRID*******************************************************
class ChartGraphics2DPlotGrid: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ChartGraphics2DPlotGrid(QObject *parent = nullptr);
    ~ChartGraphics2DPlotGrid();

    void setAbscissRange(const TRange);
    void setVisibleAbscissOffset(const double);
    void setAbscissIndexScale(const unsigned int);
    void setOrdinateRange(const TRange);
    void setVisibleOrdinateOffset(const double);
    void setOrdinateIndexScale(const unsigned int);

    void setBorderBottom(const double);
    void setScene(const QRectF);
    void setPen(const QPen);

    QRectF boundingRect()const {return m_boundRect;}
    void exec();

private:
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    void paintAxeGuidLines(const QVector<QLineF> axe, QPainter *painter, const QPen &linePen);

    QPen m_pen;
    TRange m_absciss_range;
    TRange m_ordinate_range;
    double m_visible_absciss_offset;
    double m_visible_ordinate_offset;
    unsigned int m_absciss_index_scale;
    unsigned int m_ordinate_index_scale;
    double m_absciss_visible_count_save;
    double m_ordinate_visible_count_save;
    QRectF m_boundRect;
    double m_border_bottom;
    QRectF m_scene;
    bool m_mouse_pressed;

    QVector<QLineF> m_abscissLines;
    QVector<QLineF> m_ordinateLines;

};

//**************************************SERIES****************************************************************
class ChartGraphics2DGraphItem: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ChartGraphics2DGraphItem(QFont font, ChartGraphicsPlotPoint *pointItem, QObject *parent = nullptr);
    ~ChartGraphics2DGraphItem();

    void setAbscissRange(const TRange);
    void getAbscissRange(TRange*) const;
    void setOrdinateRange(const TRange);
    void getOrdinateRange(TRange*) const;
    void getVisibleAbscissRange(TRange*) const;
    void getVisibleOrdinateRange(TRange*) const;
    void setVisibleAbscissOffset(const double);
    void getVisibleAbscissOffset(double*) const;
    void setAbscissIndexScale(const unsigned int);
    void getAbscissIndexScale(unsigned int*) const;
    void getAbscissStep(double*) const;
    void getAbscissPrecision(unsigned int*) const;
    void setVisibleOrdinateOffset(const double);
    void getVisibleOrdinateOffset(double*) const;
    void setOrdinateIndexScale(const unsigned int);
    void getOrdinateIndexScale(unsigned int*) const;
    void getOrdinateStep(double*) const;
    void getOrdinatePrecision(unsigned int*) const;
    void setRoot(const bool root);
    void getRoot(bool *root) const;
    void setUnit(const QString&);
    void getUnit(QString&) const;
    void setDevName(const QString&);
    void getDevName(QString&) const;
    void setName(const QString);
    void getName(QString&) const;
    void setMvtValueList(const QMap<ULONG, QString>&);
    void setActive(const bool);
    void setSelect(const bool);
    QPointF mapFromScene(const QPointF&) const;
    QPointF mapToScene(const QPointF&) const;
    QPointF mapFromSceneGridCorrect(const QPointF&) const;
    QSizeF mapFromScene(const QSizeF&) const;

    void setHintVisibleCount(const qsizetype) ;

    void getPointItem(ChartGraphicsPlotPoint**) const;

    void setData(const QList<QPointF>&, const QMap<qreal, ULONG>&);
    void setColor(const QColor&);
    void setBorderBottom(const double);
    void setScene(const QRectF&);
    void getScene(QRectF&) const;
    void exec();

signals:
    void updateSeriesChanged();
    void VisibleOffsetChanged(double);
    void VisibleMoveChanged(double);
    void Select();
    void ClearSelect();

public slots:
    void pointMousePress(const QPointF&);
    void pointMouseMove(const QPointF&);
    void pointMouseRelease(const QPointF&);
    void pointMouseWheel(const double);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void wheelEvent(QGraphicsSceneWheelEvent*);

private:
    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    bool OnSetLastPoint(const QPolygonF::Iterator&, const ULONG, const bool, const bool, const bool, const bool);
    bool OnAddPoint(QRectF&, const QPolygonF::Iterator&, const ULONG, const bool, const bool, const bool, const bool);
    QRectF OnPrintLastPoint(const QString&, const QColor&, const QPointF&);
    QRectF OnPrintPoint(const QString&, const QColor&, const QPointF&);

    void OnGetFirstStatus(qreal*, ULONG*) const;
    void OnGetFirstStatus(ULONG*) const;
    void OnGetLastStatus(qreal *offset, ULONG*) const;
    bool OnFoundPoligon(QPolygonF::Iterator&, const QPolygonF::Iterator&, const QPolygonF::Iterator&, const qreal) const;
    bool OnUpperStatus(const qreal, qreal*, ULONG*) const;
    bool OnLowerStatus(const qreal, qreal*, ULONG*) const;

    QFont m_font;
    QPolygonF m_poligon;
    QPolygonF m_poligonPaint;
    QMap<qreal, ULONG> m_status;
    QRectF m_boundRect;
    TRange m_absciss_range;
    TRange m_ordinate_range;
    double m_visible_absciss_offset;
    unsigned int m_absciss_index_scale;
    double m_visible_ordinate_offset;
    unsigned int m_ordinate_index_scale;
    QColor m_color;
    QPen m_pen;
    double m_border_bottom;
    bool m_root;
    int m_spacingPoints;
    bool m_ordinateCursorMode;
    QString m_UnitName;
    QString m_DevName;
    QString m_Name;
    QMap<ULONG, QString> m_valueDecr;
    bool m_active;
    bool m_activeSave;
    bool m_select;
    QRectF m_scene;
    QList<ChartGraphicsPlotPoint*> m_listPointsItem;
    int m_visiblePointsCount;
    ChartGraphicsPlotPoint *m_PointItem;
    int m_visiblePointsCountSave;
    qsizetype m_lowQualityVisibleCount;
    bool m_lowQualityEnabled;
    QPointF m_mouseOffset;
    double m_mouseOffsetSave;
};

//***************************************Legend****************************************************
class ChartGraphics2DLegend: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ChartGraphics2DLegend(QFont, QColor shadowColor, QObject *parent = nullptr);
    ~ChartGraphics2DLegend();

    void setLeftBorder(double);
    void setBorderBottom(double);
    void setScene(QRectF);
    void setFontBrush(const QBrush);
    void addLegend(QString, QColor);
    void clearLegend();
    void exec();

private:
    QRectF boundingRect()const {return m_boundRect;}
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QVector<ChartGraphicsPlotNocks*> m_nocks;
    QVector<QTransform> m_transform;
    QList<QList<QLineF>> m_lines;
    QList<QPen> m_pens;

    QFont m_font;
    QBrush m_fontBrush;
    QBrush m_brush;
    QPen m_pen;
    QRectF m_scene;
    QRectF m_boundRect;
    double m_left_border;
    double m_border_bottom;
    double m_nocks_height;
    int m_countLegend;
    bool m_iniClear;
};

//**************************************MESSAGES****************************************************************
class ChartGraphicsMessages: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ChartGraphicsMessages(QFont, QColor shadowColor, QObject *parent = nullptr);
    ~ChartGraphicsMessages();

    void addMessage(quint64 time, QString name, QColor color);
    void clear();
    void setRange(const TRange);
    void setVisibleOffset(double);
    void setIndexScale(int);
    void setBottomBorder(double);
    void setScene(QRectF);
    void setFontBrush(const QBrush);
    void setBrush(const QBrush);
    void exec();

private:
    QRectF boundingRect()const {return m_boundRect;}
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    QVector<ChartGraphicsPlotNocks*> m_nocks;
    QVector<QTransform> m_transform;
    QGraphicsDropShadowEffect *m_shadow;
    QVector<quint64> m_time_ns;

    QFont m_font;
    QBrush m_brush;
    TRange m_range;
    double m_visible_offset;
    int m_index_scale;
    QRectF m_boundRect;
    double m_padding;
    double m_bottom_border;
    double m_nocks_height;
    int m_count;
    QRectF m_scene;
};

#endif // CHARTGRAPHICSPLOTITEM_H
