#ifndef CHARTFORMSOURCE_H
#define CHARTFORMSOURCE_H

#include "ChartFormGraphicsPlotItem.h"
#include "Types.h"
#include "ChartFormScaleWidget.h"

//****************************************************************************
class ChartFormSource : public QObject
{
    Q_OBJECT
public:
    ChartFormSource(ChartFormScene *scene, qsizetype hintPoints, QWidget *parent=nullptr);
    ~ChartFormSource();
    virtual RESULT Init();
    virtual RESULT Uninit();
    virtual void OnAllBufferChanged(const QList<QPointF> &points, const QMap<qreal, ULONG> &status, const QList<ULONGLONG> &time_ns);

    void GetScaleWidget(ChartFormScaleWidget **scaleWidget) const;

    void GetRoot(bool *root) const;
    void SetRoot(const bool root);
    void SetSelect(const bool select);
    void SetActive(const bool active);
    void UpdateOrdinate();

signals:
    void RangeChanged(TRange range);
    void UpdateOrdinateScrollBar();
    void SelectSource();
    void ClearSelect();

public slots:
    void ScaleWidgetIndexChanged(unsigned int index);
    void ScaleWidgetOffsetChanged(double offset);
    void MouseOffsetChanged(double offset);
    void MouseMoveChanged(double offset);
    void ScrollBarOffsetChanged(double offset);
    void ScalePointOffsetChanged(double offset);
    void ScalePointMoveChanged(double offset);

private:
    ChartFormScene *m_scene;
    ChartGraphics2DGraphItem *m_SeriesItem;
    ChartFormScaleWidget *m_scaleWidget;
};

#endif // CHARTFORMSOURCE_H
