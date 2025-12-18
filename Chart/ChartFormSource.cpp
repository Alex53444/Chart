#include "ChartFormSource.h"
#include "Errors.h"


ChartFormSource::ChartFormSource(ChartFormScene *scene, qsizetype hintPoints, QWidget *parent)
    : QObject(parent)
{

#if(1)
    QList<QPointF> dataOrdinate;
    QMap<qreal, ULONG> statusOrdinate;

    int offset = rand() % 100;

    TRange ordinate_range = {0, 200};

    for(long i=0; i<10000; i++) {
        dataOrdinate << QPointF(1000*(double)i, ordinate_range.max*sin(2*M_PI*(i+offset)/1000));
    }

    TRange absciss_range = {0, (double)dataOrdinate.count()};
    double visibleAbscissOffset = 0;
    int abscissIndexScale = 0;

    double visibleOrdinateOffset = 0;
    int ordinateIndexScale = 0;


    m_SeriesItem = scene->CreateSeriesItem(absciss_range, visibleAbscissOffset, abscissIndexScale, ordinate_range, visibleOrdinateOffset, ordinateIndexScale, dataOrdinate, statusOrdinate, parent);
#else
    m_SeriesItem = scene->CreateSeriesItem(parent);
#endif

    m_scaleWidget = new ChartFormScaleWidget(m_SeriesItem, parent);

    m_SeriesItem->setHintVisibleCount(hintPoints);

    scene->AddSeriesItem(m_SeriesItem);

    connect(scene, SIGNAL(OrdinateMoveChanged(double)), this, SLOT(MouseMoveChanged(double)));
    connect(scene, SIGNAL(OrdinateOffsetChanged(double)), this, SLOT(MouseOffsetChanged(double)));
    connect(m_SeriesItem, SIGNAL(VisibleMoveChanged(double)), this, SLOT(ScalePointMoveChanged(double)));
    connect(m_SeriesItem, SIGNAL(VisibleOffsetChanged(double)), this, SLOT(ScalePointOffsetChanged(double)));
    connect(m_SeriesItem, SIGNAL(Select()), this, SIGNAL(SelectSource()));
    connect(m_SeriesItem, SIGNAL(ClearSelect()), this, SIGNAL(ClearSelect()));
    connect(m_scaleWidget, SIGNAL(IndexScaleChanged(unsigned int)), this, SLOT(ScaleWidgetIndexChanged(unsigned int)));
    connect(m_scaleWidget, SIGNAL(VisibleOffsetChanged(double)), this, SLOT(ScaleWidgetOffsetChanged(double)));
    connect(m_scaleWidget, SIGNAL(Select()), this, SIGNAL(SelectSource()));

    m_scene = scene;
}

ChartFormSource::~ChartFormSource()
{
    if(m_SeriesItem)
        delete m_SeriesItem;
}

RESULT ChartFormSource::Init()
{
    TRange absciss_range = {0, 0};
    double visibleAbscissOffset = 0;
    unsigned int abscissIndexScale = 0;
    m_scene->GetRootVisibleAbscissOffset(&visibleAbscissOffset);
    m_scene->GetRootAbscissIndexScale(&abscissIndexScale);

    TRange ordinate_range = {0, 100};

    int ordinateIndexScale = 0;
    m_scene->GetOrdinateIndexScaleHint(&ordinateIndexScale, ordinate_range);

    double visibleOrdinateOffset = ordinate_range.min;

    m_SeriesItem->setAbscissRange(absciss_range);
    m_SeriesItem->setAbscissIndexScale(abscissIndexScale);
    m_SeriesItem->setVisibleAbscissOffset(visibleAbscissOffset);

    m_SeriesItem->setOrdinateRange(ordinate_range);
    m_SeriesItem->setOrdinateIndexScale(ordinateIndexScale);
    m_SeriesItem->setVisibleOrdinateOffset(visibleOrdinateOffset);

    QColor colors[] = {Qt::gray, Qt::lightGray, Qt::red, Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow, QColor("#FFD700"), QColor("#FF6347"), QColor("#FFC0CB"), QColor("#FF00FF"), QColor("#D2691E"),
                      QColor("#00FFFF"), QColor("#ADFF2F"), QColor("#7B68EE"), QColor("#E6E6FA"), QColor("#D8BFD8"), QColor("#F0E68C"), QColor("#55aa7f")};

    int idx = rand() % (sizeof(colors)/sizeof(*colors));

    QColor color = QColor(colors[idx]);
    QString strUnitName = "В";
    QString strName = "Напряжение";


    m_scaleWidget->Init(color, strName, strUnitName);
    m_SeriesItem->setDevName(strName);
    m_SeriesItem->setName(strName);
    m_SeriesItem->setUnit(strUnitName);
    m_SeriesItem->setColor(color);
    return S_OK;
}

RESULT ChartFormSource::Uninit()
{
    m_scene->RemoveSeriesItem(m_SeriesItem);
    m_scene->updateSeries();

    return S_OK;
}

void ChartFormSource::OnAllBufferChanged(const QList<QPointF> &points, const QMap<qreal, ULONG> &status, const QList<ULONGLONG> &time_ns)
{
    TRange absciss_range = {0, 0};
    if(time_ns.count() != 0) {
        uint64_t absciss_count = time_ns.count();
        uint64_t absciss_end = time_ns[absciss_count-1];
        absciss_range = {0, (double)absciss_end};
    }
    else
        absciss_range = {0, (double)points.count()};

    emit RangeChanged(absciss_range);

    m_SeriesItem->setAbscissRange(absciss_range);
    m_SeriesItem->setData(points, status);

    m_SeriesItem->exec();
    m_SeriesItem->update();
}

void ChartFormSource::GetScaleWidget(ChartFormScaleWidget **scaleWidget) const
{
    *scaleWidget = m_scaleWidget;
}

void ChartFormSource::GetRoot(bool *root) const
{
    m_SeriesItem->getRoot(root);
}

void ChartFormSource::SetRoot(const bool root)
{
    m_SeriesItem->setRoot(root);

    if(root) {
        m_scene->SetRootSeries(m_SeriesItem);
        m_scene->SetLastSeries(m_SeriesItem);

        m_scene->execTubes();
        m_scene->execGrid();
        m_scene->execSeries();

        m_scene->updateGrid();
        m_scene->updateSeries();

        emit UpdateOrdinateScrollBar();
    }
}

void ChartFormSource::SetSelect(const bool select)
{
    m_SeriesItem->setSelect(select);
    m_scaleWidget->SetSelect(select);

    m_scene->execSeries();
    m_scene->updateSeries();
}

void ChartFormSource::SetActive(const bool active)
{
    m_SeriesItem->setActive(active);
    m_scaleWidget->SetActive(active);

    m_scene->execSeries();
    m_scene->updateSeries();
}

void ChartFormSource::UpdateOrdinate()
{
    double visibleOrdinateOffset = 0;
    m_SeriesItem->getVisibleOrdinateOffset(&visibleOrdinateOffset);
    unsigned int ordinateIndexScale = 0;
    m_SeriesItem->getOrdinateIndexScale(&ordinateIndexScale);

    m_scaleWidget->SetVisibleOffset(visibleOrdinateOffset);
    m_scaleWidget->SetIndexScale(ordinateIndexScale);
    m_scaleWidget->Update();

    m_SeriesItem->exec();
    m_SeriesItem->update();
}

void ChartFormSource::ScaleWidgetIndexChanged(unsigned int index)
{
    m_scene->SetRootOrdinateIndexScale(index);

    m_scene->execTubes();
    m_scene->execGrid();
    m_scene->execSeries();

    m_scene->updateGrid();
    m_scene->updateSeries();

    emit UpdateOrdinateScrollBar();
}

void ChartFormSource::ScaleWidgetOffsetChanged(double offset)
{
    m_scene->SetRootVisibleOrdinateOffset(offset);

    m_scene->execTubes();
    m_scene->execGrid();
    m_scene->execSeries();

    m_scene->updateGrid();
    m_scene->updateSeries();

    emit UpdateOrdinateScrollBar();
}

void ChartFormSource::MouseOffsetChanged(double offset)
{
    bool root = false;
    m_SeriesItem->getRoot(&root);
    if(root) {
        m_SeriesItem->setVisibleOrdinateOffset(offset);
        m_scaleWidget->SetVisibleOffset(offset);

        m_scene->SetRootVisibleOrdinateOffset(offset);

        m_scene->execTubes();
        m_scene->execGrid();
        m_scene->execSeries();

        m_scene->updateGrid();
        m_scene->updateSeries();

        emit UpdateOrdinateScrollBar();
    }
}

void ChartFormSource::MouseMoveChanged(double offset)
{
    bool root = false;
    m_SeriesItem->getRoot(&root);
    if(root) {
        m_SeriesItem->setVisibleOrdinateOffset(offset);

        m_scene->SetRootVisibleOrdinateOffset(offset);

        m_scene->execTubes();
        m_scene->execGrid();
        m_scene->execSeries();

        m_scene->updateGrid();
        m_scene->updateSeries();

        emit UpdateOrdinateScrollBar();
    }
}

void ChartFormSource::ScrollBarOffsetChanged(double offset)
{
    bool root = false;
    m_SeriesItem->getRoot(&root);
    if(root) {
        m_SeriesItem->setVisibleOrdinateOffset(offset);
        m_scaleWidget->SetVisibleOffset(offset);

        m_scene->SetRootVisibleOrdinateOffset(offset);

        m_scene->execTubes();
        m_scene->execGrid();
        m_scene->execSeries();

        m_scene->updateGrid();
        m_scene->updateSeries();

        emit UpdateOrdinateScrollBar();
    }
}

void ChartFormSource::ScalePointOffsetChanged(double offset)
{
    bool root = false;
    m_SeriesItem->getRoot(&root);
    if(root) {
        m_SeriesItem->setVisibleOrdinateOffset(offset);
        m_scaleWidget->SetVisibleOffset(offset);

        m_scene->SetRootVisibleOrdinateOffset(offset);

        m_scene->execTubes();
        m_scene->execGrid();
        m_scene->execSeries();

        m_scene->updateGrid();
        m_scene->updateSeries();

        emit UpdateOrdinateScrollBar();
    }
    else {
        m_SeriesItem->setVisibleOrdinateOffset(offset);
        m_scaleWidget->SetVisibleOffset(offset);

        m_SeriesItem->exec();
        m_SeriesItem->update();
    }
}

void ChartFormSource::ScalePointMoveChanged(double offset)
{
    bool root = false;
    m_SeriesItem->getRoot(&root);
    if(root) {
        m_SeriesItem->setVisibleOrdinateOffset(offset);

        m_scene->SetRootVisibleOrdinateOffset(offset);

        m_scene->execTubes();
        m_scene->execGrid();
        m_scene->execSeries();

        m_scene->updateGrid();
        m_scene->updateSeries();

        emit UpdateOrdinateScrollBar();
    }
    else {
        m_SeriesItem->setVisibleOrdinateOffset(offset);
        m_scaleWidget->SetVisibleOffset(offset);

        m_SeriesItem->exec();
        m_SeriesItem->update();
    }
}

