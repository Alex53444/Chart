#ifndef CHARTFORMSCROLLBAR_H
#define CHARTFORMSCROLLBAR_H

#include <QScrollBar>
#include "Types.h"
#include "ChartFormGraphicsPlotItem.h"

class ChartFormScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    ChartFormScrollBar(Qt::Orientation, QWidget *parent=nullptr);

signals:
    void OffsetChanged(double offset);

public slots:
    void SetRange(TRange absciss_range, TRange visible_absciss_range, double step);

private:
    TRange m_range;
    TRange m_visible_range;
    double m_step;

};

#endif // CHARTFORMSCALEWIDGET_H
