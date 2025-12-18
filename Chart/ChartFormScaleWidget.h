#ifndef CHARTFORMSCALEWIDGET_H
#define CHARTFORMSCALEWIDGET_H

#include <QString>
#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include "UnitsRepository.h"
#include "MainScaleRepository.h"
#include "ChartFormGraphicsPlotItem.h"
#include "ChartFormScene.h"
#include "Types.h"


class ChartFormScaleWidget : public QWidget
{
    Q_OBJECT
public:
    ChartFormScaleWidget(ChartFormScene *pScene, QWidget *parent=nullptr);
    ChartFormScaleWidget(ChartGraphics2DGraphItem *pSeriesItem, QWidget *parent=nullptr);
    void Init(const QColor color, const QString strName, const QString strBaseUnitName);
    void SetName(const QString strName);
    void SetSelect(const bool select);
    void GetSelect(bool *select) const;
    void SetActive(const bool active);
    void SetColor(const QColor color);
    void SetUnit(const QString strUnitName);
    void SetVisibleOffset(double offset);
    void SetIndexScale(const unsigned int index);
    void Update();

signals:
    void IndexScaleChanged(unsigned int index);
    void VisibleOffsetChanged(double offset);
    void Select();

private slots:
    void OnSetIndex(unsigned int index);
    void OnSetVisibleOffset(double offset);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QCheckBox *m_checkBox;
    QGroupBox *m_groupBox;
    MainScaleRepository m_mainScaleRepository;
    QList<QString> m_listMainScale;
    ChartFormScene *m_Scene;
    ChartGraphics2DGraphItem *m_SeriesItem;
    QComboBox *m_indexScaleBox;
    QComboBox *m_offsetBox;
    QString m_UnitName;
    bool m_userSelect;
    QColor m_color;
};

#endif // CHARTFORMSCALEWIDGET_H
