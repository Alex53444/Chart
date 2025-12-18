#ifndef CHARTFORM_H
#define CHARTFORM_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSplitter>
#include <QVBoxLayout>
#include <QComboBox>
#include "ChartFormSource.h"
#include "ChartFormScrollBar.h"
#include "Types.h"

class ChartFormCanvas;
class ChartFormScene;


class ChartForm : public QFrame
{
    Q_OBJECT

public:
    ChartForm(QWidget *parent=nullptr);
    virtual ~ChartForm();

// Инициализация формы
    virtual RESULT Init();

// Закрыть форму
    virtual RESULT Uninit();

// Получить флаг активности формуляра
    virtual RESULT GetActive(bool *pActive) const;

// Получить геометрию формуляра
    virtual RESULT GetGeometry(QRect *pGeometry) const;

// Создать график
    virtual RESULT CreateSource(ChartFormSource **pSource);

// Удалить график
    virtual void RemoveSource(ChartFormSource *pSource);

// Удалить все графики
    virtual void DeleteSources();

public slots:

private:
    ChartFormScaleWidget *m_scaleAbscissWidget;
    ChartFormScene *m_Scene;
    QRectF m_SizeScene;
    ChartFormCanvas *m_Canvas;
    ChartFormScrollBar *m_AbscissScrollBar;
    ChartFormScrollBar *m_OrdinateScrollBar;
    QVBoxLayout *m_ScaleOrdinateLayout;
    QSplitter *m_Splitter;
    int m_msgCountSave;

    QList<ChartFormSource*> m_ListSource;
    qsizetype m_HintPoints;


public slots:
    void AbscissRangeChanged(TRange range);

    void AbscissScaleWidgetIndexChanged(unsigned int index);
    void AbscissScaleWidgetOffsetChanged(double offset);
    void AbscissMouseOffsetChanged(double offset);
    void AbscissMouseMoveChanged(double offset);
    void AbscissScrollBarOffsetChanged(double offset);

    void UserHasSetsAbsciss();
    void UpdateAbscissScrollBar();
    void UpdateOrdinateScrollBar();

    void OnSelectSource(ChartFormSource *pSources);
    void OnClearSelect();

    void resize_Canvas(QSize);

};

#endif // CHARTFORM_H
