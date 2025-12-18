
#include "ChartFormScrollBar.h"

#define SCROLL_POINTS    32000

ChartFormScrollBar::ChartFormScrollBar(Qt::Orientation orientation, QWidget *parent)
    : QScrollBar(orientation, parent)
{
    if(orientation == Qt::Vertical) {
        setStyleSheet("QScrollBar { background: white; width: 8px; }"
                        "QScrollBar::handle:vertical { background: rgb(10, 149, 255); border-radius: 4px;}"
                        );
    }
    if(orientation == Qt::Horizontal) {
        setStyleSheet("QScrollBar { background: white; height: 8px; }"
                        "QScrollBar::handle:horizontal { background: rgb(10, 149, 255); border-radius: 4px;}"
                        );
    }

    connect(this, &QScrollBar::sliderMoved, [=] (int value) {

        double norm_value = (m_range.max - m_range.min)*value/SCROLL_POINTS;
        double correct_norm_value = m_step*round(norm_value/m_step);

        emit OffsetChanged(correct_norm_value);
    });
}

void ChartFormScrollBar::SetRange(TRange range, TRange visible_range, double step)
{
    const bool oldState = blockSignals(true);

    m_range = range;
    m_visible_range = visible_range;
    m_step = step;

    double pageStep = SCROLL_POINTS*(visible_range.max - visible_range.min)/(range.max - range.min);
    double norm_value = SCROLL_POINTS*visible_range.min/(range.max - range.min);

    setRange(0, SCROLL_POINTS - pageStep);
    setPageStep(pageStep);
    setValue(norm_value);

    blockSignals(oldState);
}

