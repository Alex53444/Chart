#include "ChartFormScene.h"
#include "AppResource.h"

//***************************VIEV**********************************************
ChartFormCanvas::ChartFormCanvas(QWidget * parent)
    :QGraphicsView(parent)
{

}

void ChartFormCanvas::resizeEvent(QResizeEvent* e)
{
    emit resizeCanvas(e->size());
}

QRectF ChartFormCanvas::boundingRect() const
{
    return m_scene;
}

//***************************SCENE**********************************************
ChartFormScene::ChartFormScene(QWidget * parent)
    :QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(Qt::black));

    m_rootSeriesItem = NULL;
    m_rootAbscissTube = NULL;
    m_rootOrdinateTube = NULL;
    m_rootGridItem = NULL;
    m_rootLegendItem = NULL;
    m_messagesItem = NULL;

    m_series_font = QFont("Tahoma", 8, 0);

    m_rootAbscissMouseOffsetSave = 0;
    m_rootOrdinateMouseOffsetSave = 0;
    m_userSetAbscissBeforeVisibleArea = false;
}


ChartFormScene::~ChartFormScene()
{

}

void ChartFormScene::SetRootSeries(ChartGraphics2DGraphItem *pSeriesItem)
{
    TRange rootAbscissRange;
    TRange rootVisibleAbscissRange;
    TRange rootOrdinateRange;
    TRange rootVisibleOrdinateRange;
    unsigned int ordinateIndexScale;
    double visibleOrdinateOffset;

    pSeriesItem->getAbscissRange(&rootAbscissRange);
    pSeriesItem->getOrdinateRange(&rootOrdinateRange);
    pSeriesItem->getOrdinateIndexScale(&ordinateIndexScale);
    pSeriesItem->getVisibleOrdinateOffset(&visibleOrdinateOffset);
    pSeriesItem->getVisibleAbscissRange(&rootVisibleAbscissRange);
    pSeriesItem->getVisibleOrdinateRange(&rootVisibleOrdinateRange);

    SetRootAbscissRange(rootAbscissRange);
    SetRootOrdinateRange(rootOrdinateRange);
    SetRootVisibleOrdinateOffset(visibleOrdinateOffset);
    SetRootOrdinateIndexScale(ordinateIndexScale);

    m_rootSeriesItem = pSeriesItem;
}

void ChartFormScene::GetRootSeries(ChartGraphics2DGraphItem **pSeriesItem) const
{
    *pSeriesItem = m_rootSeriesItem;
}

void ChartFormScene::SetRootAbscissRange(const TRange absciss_range)
{
    m_rootAbscissTube->setRange(absciss_range);
    m_rootGridItem->setAbscissRange(absciss_range);
    m_messagesItem->setRange(absciss_range);
}

void ChartFormScene::GetRootAbscissRange(TRange *absciss_range) const
{
    m_rootAbscissTube->getRange(absciss_range);
}

void ChartFormScene::SetRootOrdinateRange(const TRange ordinate_range)
{
    m_rootOrdinateTube->setRange(ordinate_range);
    m_rootGridItem->setOrdinateRange(ordinate_range);
}

void ChartFormScene::GetRootOrdinateRange(TRange *ordinate_range) const
{
    m_rootOrdinateTube->getRange(ordinate_range);
}

void ChartFormScene::SetRootVisibleAbscissOffset(const double visible_absciss_offset)
{
    m_rootAbscissTube->setVisibleOffset(visible_absciss_offset);

    m_rootGridItem->setVisibleAbscissOffset(visible_absciss_offset);

    m_messagesItem->setVisibleOffset(visible_absciss_offset);
}

void ChartFormScene::GetRootVisibleAbscissOffset(double *absciss_offset) const
{
    m_rootAbscissTube->getVisibleOffset(absciss_offset);
}

void ChartFormScene::SetRootAbscissIndexScale(const unsigned int indexScale)
{
    m_rootAbscissTube->setIndexScale(indexScale);

    m_rootGridItem->setAbscissIndexScale(indexScale);

    m_messagesItem->setIndexScale(indexScale);
}

void ChartFormScene::GetRootAbscissIndexScale(unsigned int *indexScale) const
{
    m_rootAbscissTube->getIndexScale(indexScale);
}

void ChartFormScene::SetRootVisibleOrdinateOffset(const double ordinate_offset)
{
    m_rootOrdinateTube->setVisibleOffset(ordinate_offset);

    m_rootGridItem->setVisibleOrdinateOffset(ordinate_offset);
}

void ChartFormScene::GetRootVisibleOrdinateOffset(double *ordinate_offset) const
{
    m_rootOrdinateTube->getVisibleOffset(ordinate_offset);
}

void ChartFormScene::SetRootOrdinateIndexScale(const unsigned int indexScale)
{
    m_rootOrdinateTube->setIndexScale(indexScale);

    m_rootGridItem->setOrdinateIndexScale(indexScale);
}

void ChartFormScene::GetRootOrdinateIndexScale(unsigned int* indexScale) const
{
    m_rootOrdinateTube->getIndexScale(indexScale);
}

void ChartFormScene::GetRootVisibleAbscissRange(TRange *absciss_range) const
{
    m_rootAbscissTube->getVisibleRange(absciss_range);
}

void ChartFormScene::GetRootAbscissPrecision(unsigned int* precision) const
{
    m_rootAbscissTube->getPrecision(precision);
}

void ChartFormScene::GetRootAbscissStep(double* step) const
{
    m_rootAbscissTube->getStep(step);
}

void ChartFormScene::GetRootOrdinateStep(double* step) const
{
    m_rootOrdinateTube->getStep(step);
}

QString ChartFormScene::convertAbscissTime(quint64 time_ns, int precision) const
{
    QString str;
    convertTime(str, time_ns, precision);
    return str;
}

void ChartFormScene::GetRootVisibleOrdinateRange(TRange *absciss_range) const
{
    m_rootOrdinateTube->getVisibleRange(absciss_range);
}

void ChartFormScene::SetSeriesVisibleAbscissOffset(const double absciss_offset)
{
    foreach(ChartGraphics2DGraphItem* item, m_listSeriesItem)
        item->setVisibleAbscissOffset(absciss_offset);
}

void ChartFormScene::SetSeriesAbscissIndexScale(const unsigned int indexScale)
{
    foreach(ChartGraphics2DGraphItem* item, m_listSeriesItem)
        item->setAbscissIndexScale(indexScale);
}

void ChartFormScene::Initialize()
{
    m_rootAbscissTube = new ChartGraphicsAbscissTube(m_axis_font, QColor(0, 0, 0, 255), this);
    m_rootOrdinateTube = new ChartGraphicsOrdinateTube(m_axis_font, QColor(0, 0, 0, 255), this);
    m_rootGridItem = new ChartGraphics2DPlotGrid(this);
    m_rootLegendItem = new ChartGraphics2DLegend(m_axis_font, QColor(0, 0, 0, 255), this);
    m_messagesItem = new ChartGraphicsMessages(m_axis_font, QColor(0, 0, 0, 255), this);


    m_rootAbscissTube->setFontBrush(QBrush (Qt::white, Qt::SolidPattern));
    m_rootAbscissTube->setBrush(QBrush(QColor(100, 100, 100, 255), Qt::SolidPattern));

    m_messagesItem->setFontBrush(QBrush (Qt::white, Qt::SolidPattern));
    m_messagesItem->setBrush(QBrush(QColor(255, 242, 0, 255), Qt::SolidPattern));

    m_rootOrdinateTube->setLeftPadding(10);
    m_rootOrdinateTube->setBorderBottom(m_rootAbscissTube->boundingRect().height());
    m_rootOrdinateTube->setFontBrush(QBrush (Qt::white, Qt::SolidPattern));
    m_rootOrdinateTube->setBrush(QBrush(QColor(100, 100, 100, 150), Qt::SolidPattern));

    m_rootAbscissTube->setCursor(Qt::OpenHandCursor);
    m_rootOrdinateTube->setCursor(Qt::OpenHandCursor);

    m_rootGridItem->setBorderBottom(m_rootAbscissTube->boundingRect().height());
    m_rootGridItem->setPen(QPen(QColor(50, 50, 50, 255), 1, Qt::DotLine, Qt::SquareCap, Qt::BevelJoin));

    m_rootLegendItem->setFontBrush(QBrush (Qt::white, Qt::SolidPattern));


    m_rootAbscissTube->setScene(sceneRect());
    m_rootOrdinateTube->setScene(sceneRect());
    m_rootGridItem->setScene(sceneRect());
    m_rootLegendItem->setScene(sceneRect());
    m_messagesItem->setScene(sceneRect());

    connect(m_rootAbscissTube, SIGNAL(mousePress(double)), this, SLOT(abscissMousePress(double)));
    connect(m_rootAbscissTube, SIGNAL(mouseMove(double)), this, SLOT(abscissMouseMove(double)));
    connect(m_rootAbscissTube, SIGNAL(mouseRelease(double)), this, SLOT(abscissMouseRelease(double)));
    connect(m_rootAbscissTube, SIGNAL(mouseWheel(double)), this, SLOT(abscissMouseWheel(double)));

    connect(m_rootOrdinateTube, SIGNAL(mousePress(double)), this, SLOT(ordinateMousePress(double)));
    connect(m_rootOrdinateTube, SIGNAL(mouseMove(double)), this, SLOT(ordinateMouseMove(double)));
    connect(m_rootOrdinateTube, SIGNAL(mouseRelease(double)), this, SLOT(ordinateMouseRelease(double)));
    connect(m_rootOrdinateTube, SIGNAL(mouseWheel(double)), this, SLOT(ordinateMouseWheel(double)));
}

void ChartFormScene::LoadItems()
{
    addItem(m_rootGridItem);

    foreach(ChartGraphics2DGraphItem *seriesItem, m_listSeriesItem) {
        addItem(seriesItem);

        ChartGraphicsPlotPoint *pointItem = NULL;
        seriesItem->getPointItem(&pointItem);
        addItem(pointItem);
    }
    addItem(m_rootOrdinateTube);
    addItem(m_rootAbscissTube);
    addItem(m_rootLegendItem);
    addItem(m_messagesItem);

    CalcZValue();
}

void ChartFormScene::CalcZValue()
{
    int zValue = 0;
    m_rootGridItem->setZValue(zValue);
    zValue++;

    foreach(ChartGraphics2DGraphItem *seriesItem, m_listSeriesItem) {
        seriesItem->setZValue(zValue);
        zValue++;
    }

    foreach(ChartGraphics2DGraphItem *seriesItem, m_listSeriesItem) {
        ChartGraphicsPlotPoint *pointItem = NULL;
        seriesItem->getPointItem(&pointItem);
        pointItem->setZValue(zValue);
        zValue++;
    }

    m_rootOrdinateTube->setZValue(zValue);
    zValue++;

    m_rootAbscissTube->setZValue(zValue);
    zValue++;

    m_rootLegendItem->setZValue(zValue);
    zValue++;

    m_messagesItem->setZValue(zValue);
    zValue++;
}

ChartGraphics2DGraphItem* ChartFormScene::CreateSeriesItem(QWidget *parent)
{     
    ChartGraphicsPlotPoint *pointItem = new ChartGraphicsPlotPoint(parent);
    ChartGraphics2DGraphItem *seriesItem = new ChartGraphics2DGraphItem(m_series_font, pointItem, parent);
    seriesItem->setBorderBottom(m_rootAbscissTube->boundingRect().height());
    seriesItem->setScene(sceneRect());

    connect(seriesItem, SIGNAL(updateCursorChanged()), this, SLOT(updateCursorChanged()));
    connect(seriesItem, SIGNAL(updateSeriesChanged()), this, SLOT(updateSeriesChanged()));

    return seriesItem;
}

ChartGraphics2DGraphItem* ChartFormScene::CreateSeriesItem(const TRange absciss_range, const double visible_absciss_offset, const int abscissIndexScale, const TRange ordinate_range, const double visible_ordinate_offset, const int ordinateIndexScale, const QList<QPointF> dataOrdinate, const QMap<qreal, ULONG> statusOrdinate, QWidget *parent)
{
    ChartGraphicsPlotPoint *pointItem = new ChartGraphicsPlotPoint(parent);
    ChartGraphics2DGraphItem *seriesItem = new ChartGraphics2DGraphItem(m_series_font, pointItem, parent);
    seriesItem->setAbscissRange(absciss_range);
    seriesItem->setOrdinateRange(ordinate_range);
    seriesItem->setVisibleAbscissOffset(visible_absciss_offset);
    seriesItem->setAbscissIndexScale(abscissIndexScale);
    seriesItem->setVisibleOrdinateOffset(visible_ordinate_offset);
    seriesItem->setOrdinateIndexScale(ordinateIndexScale);
    seriesItem->setBorderBottom(m_rootAbscissTube->boundingRect().height());
    seriesItem->setScene(sceneRect());
    seriesItem->setData(dataOrdinate, statusOrdinate);

    connect(seriesItem, SIGNAL(updateSeriesChanged()), this, SLOT(updateSeriesChanged()));

    return seriesItem;
}

void ChartFormScene::AddSeriesItem(ChartGraphics2DGraphItem *seriesItem)
{
    addItem(seriesItem);

    ChartGraphicsPlotPoint *pointItem = NULL;
    seriesItem->getPointItem(&pointItem);
    addItem(pointItem);

    int index = -1;
    for(int i=0; i<m_listSeriesItem.count(); i++) {
        ChartGraphics2DGraphItem *locSeriesItem = m_listSeriesItem[i];
        if(locSeriesItem == seriesItem)
            index = i;
    }
    if(index == -1)                         // Если не нашли, добавляем последним
        m_listSeriesItem << seriesItem;
    else {
        m_listSeriesItem.remove(index);     // Если нашли, то также будет последний
        m_listSeriesItem << seriesItem;
    }

    CalcZValue();
}

void ChartFormScene::RemoveSeriesItem(ChartGraphics2DGraphItem *seriesItem)
{
    removeItem(seriesItem);

    ChartGraphicsPlotPoint *item = NULL;
    seriesItem->getPointItem(&item);
    removeItem(item);

    for(int i=0; i<m_listSeriesItem.count(); i++) {
        if(m_listSeriesItem[i] == seriesItem) {
            delete m_listSeriesItem[i];
            m_listSeriesItem.remove(i);
            break;
        }
    }

    CalcZValue();
}

void ChartFormScene::SetLastSeries(ChartGraphics2DGraphItem *seriesItem)
{
    ChartGraphics2DGraphItem *lastItem = NULL;
    for(int i=0; i<m_listSeriesItem.count(); i++) {
        ChartGraphics2DGraphItem *locSeriesItem = m_listSeriesItem[i];
        if(locSeriesItem == seriesItem) {
            lastItem = m_listSeriesItem[i];
            m_listSeriesItem.remove(i);
            break;
        }
    }
    if(lastItem) {
        m_listSeriesItem << lastItem;
        CalcZValue();
    }
}

void ChartFormScene::AddLegend(const QString name, const QColor color)
{
    m_rootLegendItem->addLegend(name, color);
}

void ChartFormScene::AddMessage(const quint64 time, const QString name, const QColor color)
{
    m_messagesItem->addMessage(time, name, color);
}

void ChartFormScene::ClearLegend()
{
    m_rootLegendItem->clearLegend();
}

void ChartFormScene::ClearMessages()
{
    m_messagesItem->clear();
}

void ChartFormScene::Clear()
{
    this->removeItem(m_rootGridItem);
    foreach(ChartGraphics2DGraphItem *seriesItem, m_listSeriesItem) {
        this->removeItem(seriesItem);

        ChartGraphicsPlotPoint *item = NULL;
        seriesItem->getPointItem(&item);
        this->removeItem(item);
    }
    m_listSeriesItem.clear();
    this->removeItem(m_rootOrdinateTube);
    this->removeItem(m_rootAbscissTube);
    this->removeItem(m_rootLegendItem);
    this->removeItem(m_messagesItem);
}

void ChartFormScene::GetOrdinateIndexScaleHint(int *ordinateIndexScale, TRange ordinate_range)
{
    m_rootOrdinateTube->getOrdinateIndexScaleHint(ordinateIndexScale, ordinate_range);
}

void ChartFormScene::SetAbscissUserSetsInVisibleArea(bool flag)
{
    m_userSetAbscissBeforeVisibleArea = flag;
}

void ChartFormScene::GetAbscissUserSetsInVisibleArea(bool *flag)
{
    *flag = m_userSetAbscissBeforeVisibleArea;
}

void ChartFormScene::Repaint()
{
    if(m_rootAbscissTube == NULL)
        return;

    m_rootAbscissTube->setScene(sceneRect());
    m_rootOrdinateTube->setScene(sceneRect());
    m_rootGridItem->setScene(sceneRect());
    m_rootLegendItem->setScene(sceneRect());
    m_messagesItem->setScene(sceneRect());

    foreach(ChartGraphics2DGraphItem* item, m_listSeriesItem)
        item->setScene(sceneRect());

    execTubes();
    execGrid();
    execSeries();
    execLegend();
    execMessages();

    updateGrid();
    updateSeries();
}

void ChartFormScene::execAbscissTube()
{
    m_rootAbscissTube->exec();
}

void ChartFormScene::execTubes()
{
    m_rootAbscissTube->exec();

    m_rootOrdinateTube->setBorderBottom(m_rootAbscissTube->boundingRect().height());
    m_rootOrdinateTube->exec();
}

void ChartFormScene::execGrid()
{
    m_rootGridItem->setBorderBottom(m_rootAbscissTube->boundingRect().height());
    m_rootGridItem->exec();
}

void ChartFormScene::execLegend()
{
    m_rootLegendItem->setLeftBorder(m_rootOrdinateTube->boundingRect().width());
    m_rootLegendItem->setBorderBottom(m_rootAbscissTube->boundingRect().height());
    m_rootLegendItem->exec();
}

void ChartFormScene::execSeries()
{
    foreach(ChartGraphics2DGraphItem* item, m_listSeriesItem) {
        item->setBorderBottom(m_rootAbscissTube->boundingRect().height());
        item->exec();
    }
}

void ChartFormScene::execMessages()
{
    m_messagesItem->setBottomBorder(m_rootAbscissTube->boundingRect().height());
    m_messagesItem->exec();
}

void ChartFormScene::updateGrid()
{
    m_rootGridItem->update();
}

void ChartFormScene::updateSeries()
{
    foreach(ChartGraphics2DGraphItem* seriesItem, m_listSeriesItem) {
        seriesItem->update();

        ChartGraphicsPlotPoint *item = NULL;
        seriesItem->getPointItem(&item);
        seriesItem->update();
    }
}

void ChartFormScene::abscissMousePress(double pos)
{
    double offset;
    m_rootAbscissTube->getVisibleOffset(&offset);

    m_rootAbscissMouseOffsetSave = offset + pos;
}

void ChartFormScene::abscissMouseMove(double pos)
{
    double offset = m_rootAbscissMouseOffsetSave - pos;

    emit AbscissMoveChanged(offset);
}

void ChartFormScene::abscissMouseRelease(double pos)
{
    double offset = m_rootAbscissMouseOffsetSave - pos;

    emit AbscissOffsetChanged(offset);
}

void ChartFormScene::abscissMouseWheel(double delta)
{
    double offset;
    m_rootAbscissTube->getVisibleOffset(&offset);
    double step;
    m_rootAbscissTube->getStep(&step);

    if(delta > 0)
        offset -= step;
    else
        offset += step;

    emit AbscissOffsetChanged(offset);
}

void ChartFormScene::ordinateMousePress(double pos)
{
    double offset;
    m_rootOrdinateTube->getVisibleOffset(&offset);

    m_rootOrdinateMouseOffsetSave = offset + pos;
}

void ChartFormScene::ordinateMouseMove(double pos)
{
    double offset = m_rootOrdinateMouseOffsetSave - pos;

    emit OrdinateMoveChanged(offset);
}

void ChartFormScene::ordinateMouseRelease(double pos)
{
    double offset = m_rootOrdinateMouseOffsetSave - pos;

    emit OrdinateOffsetChanged(offset);
}

void ChartFormScene::ordinateMouseWheel(double delta)
{
    double offset;
    m_rootOrdinateTube->getVisibleOffset(&offset);
    double step;
    m_rootOrdinateTube->getStep(&step);

    if(delta > 0)
        offset -= step;
    else
        offset += step;

    emit OrdinateOffsetChanged(offset);
}

void ChartFormScene::updateSeriesChanged()
{
    updateGrid();
}



