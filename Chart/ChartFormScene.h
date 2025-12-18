#ifndef CHARTFORMSCENE_H
#define CHARTFORMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "ChartFormGraphicsPlotItem.h"
#include "Types.h"


//***************************VIEW**********************************************
class ChartFormCanvas: public QGraphicsView
{
    Q_OBJECT
public:
    explicit ChartFormCanvas(QWidget *parent=nullptr);

    QRectF boundingRect() const;

signals:
    void resizeCanvas(QSize);

private:
    QRectF m_scene;


protected:
    void resizeEvent(QResizeEvent*);
};

//***************************SCENE**********************************************
class ChartFormScene:  public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ChartFormScene(QWidget *parent);
    ~ChartFormScene();

    void SetRootSeries(ChartGraphics2DGraphItem *pSeriesItem);
    void GetRootSeries(ChartGraphics2DGraphItem **pSeriesItem) const;

// Диапазон значений absciss, ordinate
    void SetRootAbscissRange(const TRange absciss_range);
    void GetRootAbscissRange(TRange *absciss_range) const;
    void SetRootOrdinateRange(const TRange ordinate_range);
    void GetRootOrdinateRange(TRange *ordinate_range) const;

// Смещение видимой области absciss, порядковый номер шага шкалы
    void SetRootVisibleAbscissOffset(const double absciss_offset);
    void GetRootVisibleAbscissOffset(double *absciss_offset) const;
    void SetRootAbscissIndexScale(const unsigned int);
    void GetRootAbscissIndexScale(unsigned int*) const;

    void SetRootVisibleOrdinateOffset(const double ordinate_offset);
    void GetRootVisibleOrdinateOffset(double *ordinate_offset) const;
    void SetRootOrdinateIndexScale(const unsigned int);
    void GetRootOrdinateIndexScale(unsigned int*) const;

// Получить диапазон значений видимой области
    void GetRootVisibleAbscissRange(TRange *absciss_range) const;

// Получить порядковый номер, точности предоставления absciss
    void GetRootAbscissPrecision(unsigned int* numPrecision) const;

// Получить шаг по шкале absciss
    void GetRootAbscissStep(double* step) const;

// Получить шаг по шкале ordinate
    void GetRootOrdinateStep(double* step) const;

// Получить видимую область absciss
    void GetRootVisibleOrdinateRange(TRange *absciss_range) const;

// Установить смещение видимой области графиков
    void SetSeriesVisibleAbscissOffset(const double);

// Установить порядковый номер шага графиков
    void SetSeriesAbscissIndexScale(const unsigned int);

// Преобразовать время
    QString convertAbscissTime(quint64 time_ns, int precision) const;

    void Initialize();
    void LoadItems();
    void CalcZValue();
    ChartGraphics2DGraphItem* CreateSeriesItem(QWidget *parent=nullptr);
    ChartGraphics2DGraphItem* CreateSeriesItem(const TRange absciss_range, const double visible_absciss_offset, const int abscissIndexScale, const TRange ordinate_range, const double visible_ordinate_offset, const int ordinateIndexScale, const QList<QPointF> dataOrdinate, const QMap<qreal, ULONG> statusOrdinate, QWidget *parent);
    void AddSeriesItem(ChartGraphics2DGraphItem *item);
    void RemoveSeriesItem(ChartGraphics2DGraphItem *item);
    void SetLastSeries(ChartGraphics2DGraphItem *item);
    void AddLegend(const QString name, const QColor color);
    void AddMessage(const quint64 time, const QString name, const QColor color);
    void ClearLegend();
    void ClearMessages();
    void Clear();

    void GetOrdinateIndexScaleHint(int *ordinateIndexScale, TRange ordinate_range);
    void SetAbscissUserSetsInVisibleArea(bool flag);
    void GetAbscissUserSetsInVisibleArea(bool *flag);

    void Repaint();

    void execAbscissTube();
    void execTubes();
    void execGrid();
    void execLegend();
    void execSeries();
    void execMessages();

    void updateGrid();
    void updateSeries();


signals:
    void AbscissMoveChanged(double);
    void AbscissOffsetChanged(double);
    void OrdinateMoveChanged(double);
    void OrdinateOffsetChanged(double);

public slots:
    void abscissMousePress(double);
    void abscissMouseMove(double);
    void abscissMouseRelease(double);
    void abscissMouseWheel(double);

    void ordinateMousePress(double);
    void ordinateMouseMove(double);
    void ordinateMouseRelease(double);
    void ordinateMouseWheel(double);

    void updateSeriesChanged();

private:
    QFont m_axis_font;
    QFont m_series_font;

    ChartGraphics2DGraphItem *m_rootSeriesItem;
    ChartGraphics2DPlotGrid *m_rootGridItem;
    QList<ChartGraphics2DGraphItem*> m_listSeriesItem;
    ChartGraphics2DLegend *m_rootLegendItem;
    ChartGraphicsAbscissTube *m_rootAbscissTube;
    ChartGraphicsOrdinateTube *m_rootOrdinateTube;
    ChartGraphicsMessages *m_messagesItem;

    double m_rootAbscissMouseOffsetSave;
    double m_rootOrdinateMouseOffsetSave;
    bool m_userSetAbscissBeforeVisibleArea;
};

#endif // CHARTFORM_H
