#include "ChartForm.h"
#include <QIcon>
#include <QLabel>
#include <QHeaderView>
#include <QScrollBar>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QMenu>
#include <QAction>
#include "AppResource.h"
#include "profile.h"
#include "Errors.h"
#include "ChartFormScene.h"
#include "ChartFormSource.h"


#define DEFAULT_X_MAINSCALE_NUM   10
#define SCALE_MINIMUM_WIDTH     200


//***********************************************************************//

ChartForm::ChartForm(QWidget *parent)
    : QFrame(parent)
{
    m_SizeScene = QRectF(0, 0, 500, 200);

    m_Scene = new ChartFormScene(parent);

    m_Canvas = new ChartFormCanvas();
    m_Canvas->setScene(m_Scene);
    m_Canvas->setMinimumSize(m_SizeScene.width(), m_SizeScene.height());
    m_Canvas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_Canvas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_Scene->setSceneRect(m_SizeScene);

    m_AbscissScrollBar = new ChartFormScrollBar(Qt::Horizontal);
    m_OrdinateScrollBar = new ChartFormScrollBar(Qt::Vertical);

    m_scaleAbscissWidget = new ChartFormScaleWidget(m_Scene, this);

    QScrollArea *scaleScroll = new QScrollArea(this);
    scaleScroll->setFrameShape(QFrame::NoFrame);
    scaleScroll->setFrameShadow(QFrame::Plain);
    scaleScroll->setWidgetResizable(true);
    scaleScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scaleScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scaleScroll->setContentsMargins(0, 0, 0, 0);
    scaleScroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scaleScroll->setMinimumWidth(SCALE_MINIMUM_WIDTH);

    m_ScaleOrdinateLayout = new QVBoxLayout();
    m_ScaleOrdinateLayout->setContentsMargins(0, 0, 0, 0);
    m_ScaleOrdinateLayout->setAlignment(Qt::AlignTop);
    m_ScaleOrdinateLayout->addWidget(m_scaleAbscissWidget, 0, Qt::AlignTop);

    QWidget *scaleWidget = new QWidget(scaleScroll);
    scaleWidget->setLayout(m_ScaleOrdinateLayout);
    scaleWidget->setContentsMargins(0, 0, 0, 0);
    scaleWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    scaleScroll->setWidget(scaleWidget);
    scaleScroll->setContentsMargins(0, 0, 0, 0);

    QWidget *widget = new QWidget();
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGridLayout *chartLayout = new QGridLayout(widget);
    chartLayout->addWidget(m_OrdinateScrollBar, 1, 0, 1, 1);
    chartLayout->addWidget(m_AbscissScrollBar, 2, 1, 1, 1);
    chartLayout->addWidget(m_Canvas, 1, 1, 1, 1);

    m_Splitter = new QSplitter();
    m_Splitter->addWidget(scaleScroll);
    m_Splitter->addWidget(widget);
    m_Splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *centralLayout = new QHBoxLayout();
    centralLayout->addWidget(m_Splitter);
    centralLayout->setAlignment(Qt::AlignTop);
    centralLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(centralLayout);

    connect(m_Canvas, SIGNAL(resizeCanvas(QSize)), this, SLOT(resize_Canvas(QSize)));

    connect(m_scaleAbscissWidget, SIGNAL(VisibleOffsetChanged(double)), this, SLOT(AbscissScaleWidgetOffsetChanged(double)));
    connect(m_scaleAbscissWidget, SIGNAL(IndexScaleChanged(unsigned int)), this, SLOT(AbscissScaleWidgetIndexChanged(unsigned int)));
    connect(m_Scene, SIGNAL(AbscissMoveChanged(double)), this, SLOT(AbscissMouseMoveChanged(double)));
    connect(m_Scene, SIGNAL(AbscissOffsetChanged(double)), this, SLOT(AbscissMouseOffsetChanged(double)));
    connect(m_AbscissScrollBar, SIGNAL(OffsetChanged(double)), this, SLOT(AbscissScrollBarOffsetChanged(double)));

    m_msgCountSave = 0;
}

ChartForm::~ChartForm()
{

}

// Инициализация формы
RESULT ChartForm::Init()
{
    double height = 0, width = 0;
    double visibleAbscissOffset = 0;
    ULONG abscissIndexScale = DEFAULT_X_MAINSCALE_NUM;
    bool abscissSelect = false;
    bool userSetsIn = false;
    QByteArray array;

    height = 100;
    width = 500;
    m_HintPoints = 100;
    userSetsIn = false;

    /*
    cfg.begin_section("Chart");
    cfg.get_value("Height", height);
    cfg.get_value("Width", width);
    cfg.get_value("AbscissIndexScale", abscissIndexScale);
    cfg.get_value("AbscissOffset", visibleAbscissOffset);
    cfg.get_value("AbscissSelect", abscissSelect);
    cfg.get_value("MaxVisibleCount", m_HintPoints);
    cfg.get_value("UserSetsIn", userSetsIn);
    cfg.get_value("Splitter", array);
    cfg.end_section();
*/


    if((height != 0) && (width != 0)) {
        m_SizeScene.setHeight(height);
        m_SizeScene.setWidth(width);
    }

  //  m_Splitter->restoreState(array);

    m_Scene->setSceneRect(m_SizeScene);
    m_Scene->Initialize();
    m_Scene->LoadItems();

    m_Scene->SetRootVisibleAbscissOffset(visibleAbscissOffset);
    m_Scene->SetRootAbscissIndexScale(abscissIndexScale);
    m_Scene->SetAbscissUserSetsInVisibleArea(userSetsIn);

    m_scaleAbscissWidget->Init(Qt::white, CHARTFORM_STR_X_NAME, "");
    m_scaleAbscissWidget->SetVisibleOffset(visibleAbscissOffset);
    m_scaleAbscissWidget->SetIndexScale(abscissIndexScale);
    m_scaleAbscissWidget->SetSelect(abscissSelect);

    return S_OK;
}

// Закрыть форму
RESULT ChartForm::Uninit()
{
    DeleteSources();

    double visibleAbscissOffset;
    m_Scene->GetRootVisibleAbscissOffset(&visibleAbscissOffset);

    unsigned int abscissIndexScale;
    m_Scene->GetRootAbscissIndexScale(&abscissIndexScale);

    bool abscissSelect = false;
    m_scaleAbscissWidget->GetSelect(&abscissSelect);

    bool userSetsIn = false;
    m_Scene->GetAbscissUserSetsInVisibleArea(&userSetsIn);

    /*
    profile cfg(strIniFullName);
    cfg.begin_section("Chart");
    cfg.set_value("Height", m_Scene->sceneRect().height());
    cfg.set_value("Width", m_Scene->sceneRect().width());
    cfg.set_value("AbscissIndexScale", (ULONG)abscissIndexScale);
    cfg.set_value("AbscissOffset", visibleAbscissOffset);
    cfg.set_value("AbscissSelect", abscissSelect);
    cfg.set_value("UserSetsIn", userSetsIn);
    cfg.set_value("Splitter", m_Splitter->saveState());
    cfg.end_section();
*/

    return S_OK;
}

// Получить флаг активности формуляра
RESULT ChartForm::GetActive(bool *pActive) const
{
    *pActive = isVisible();
    return S_OK;
}

// Получить геометрию формуляра
RESULT ChartForm::GetGeometry(QRect *pGeometry) const
{
    *pGeometry = geometry().translated(mapToGlobal(QPoint(0,0)));
    return S_OK;
}

RESULT ChartForm::CreateSource(ChartFormSource **pSource)
{
    ChartFormSource *newSource = new ChartFormSource(m_Scene, m_HintPoints, this);

    ChartFormScaleWidget *scaleWidget = NULL;
    newSource->GetScaleWidget(&scaleWidget);
    m_ScaleOrdinateLayout->addWidget(scaleWidget, 0, Qt::AlignTop);

    connect(m_OrdinateScrollBar, SIGNAL(OffsetChanged(double)), newSource, SLOT(ScrollBarOffsetChanged(double)));
    connect(newSource, SIGNAL(UpdateOrdinateScrollBar()), this, SLOT(UpdateOrdinateScrollBar()));
    connect(newSource, SIGNAL(RangeChanged(TRange)), this, SLOT(AbscissRangeChanged(TRange)));

    connect(newSource, &ChartFormSource::SelectSource, [=]() {
        OnSelectSource(newSource);
    });

    connect(newSource, SIGNAL(ClearSelect()), this, SLOT(OnClearSelect()));

    *pSource = newSource;

    m_ListSource << newSource;

    return S_OK;
}

void ChartForm::RemoveSource(ChartFormSource *pSource)
{
    ChartFormScaleWidget *scaleWidget = NULL;
    pSource->GetScaleWidget(&scaleWidget);
    m_ScaleOrdinateLayout->removeWidget(scaleWidget);
    pSource->Uninit();
}

void ChartForm::DeleteSources()
{
    for(int i=0; i<m_ListSource.count(); i++) {
        RemoveSource(m_ListSource[i]);
        delete m_ListSource[i];
    }
    m_ListSource.clear();
}

// *******************Absciss*************************
void ChartForm::AbscissRangeChanged(TRange absciss_range)
{
    m_Scene->SetRootAbscissRange(absciss_range);

    TRange visible_absciss_range;
    m_Scene->GetRootVisibleAbscissRange(&visible_absciss_range);

    bool flagSetInUser = false;
    m_Scene->GetAbscissUserSetsInVisibleArea(&flagSetInUser);

    if(flagSetInUser) {
        if(visible_absciss_range.max < absciss_range.max) { // Если вышли из видимой области

            double step;
            m_Scene->GetRootAbscissStep(&step);
            double width = visible_absciss_range.max - visible_absciss_range.min;
            double offset = absciss_range.max - width;
            double correct_offset = step*round(offset/step) + step;     // step - дополнительный запас свободного пространства

            m_scaleAbscissWidget->SetVisibleOffset(correct_offset);

            m_Scene->SetSeriesVisibleAbscissOffset(correct_offset);
            m_Scene->SetRootVisibleAbscissOffset(correct_offset);

            m_Scene->execAbscissTube();
            m_Scene->execGrid();
            m_Scene->execSeries();

            m_Scene->updateGrid();
            m_Scene->updateSeries();

        }
    }
    UpdateAbscissScrollBar();
}

void ChartForm::AbscissScaleWidgetIndexChanged(unsigned int index)
{
    m_Scene->SetSeriesAbscissIndexScale(index);
    m_Scene->SetRootAbscissIndexScale(index);

    m_Scene->execAbscissTube();
    m_Scene->execGrid();
    m_Scene->execSeries();

    m_Scene->updateGrid();
    m_Scene->updateSeries();

    UserHasSetsAbsciss();
    UpdateAbscissScrollBar();
}

void ChartForm::AbscissScaleWidgetOffsetChanged(double offset)
{
    m_Scene->SetSeriesVisibleAbscissOffset(offset);
    m_Scene->SetRootVisibleAbscissOffset(offset);

    m_Scene->execAbscissTube();
    m_Scene->execGrid();
    m_Scene->execSeries();

    m_Scene->updateGrid();
    m_Scene->updateSeries();

    UserHasSetsAbsciss();
    UpdateAbscissScrollBar();
}

void ChartForm::AbscissMouseOffsetChanged(double offset)
{
    m_Scene->SetSeriesVisibleAbscissOffset(offset);
    m_Scene->SetRootVisibleAbscissOffset(offset);
    m_scaleAbscissWidget->SetVisibleOffset(offset);

    m_Scene->execAbscissTube();
    m_Scene->execGrid();
    m_Scene->execSeries();

    m_Scene->updateGrid();
    m_Scene->updateSeries();

    UserHasSetsAbsciss();
    UpdateAbscissScrollBar();
}

void ChartForm::AbscissMouseMoveChanged(double offset)
{
    m_Scene->SetSeriesVisibleAbscissOffset(offset);
    m_Scene->SetRootVisibleAbscissOffset(offset);
    m_scaleAbscissWidget->SetVisibleOffset(offset);

    m_Scene->execAbscissTube();
    m_Scene->execGrid();
    m_Scene->execSeries();

    m_Scene->updateGrid();
    m_Scene->updateSeries();

    UserHasSetsAbsciss();
    UpdateAbscissScrollBar();
}

void ChartForm::AbscissScrollBarOffsetChanged(double offset)
{
    m_Scene->SetRootVisibleAbscissOffset(offset);
    m_Scene->SetSeriesVisibleAbscissOffset(offset);
    m_scaleAbscissWidget->SetVisibleOffset(offset);

    m_Scene->execAbscissTube();
    m_Scene->execGrid();
    m_Scene->execSeries();

    m_Scene->updateGrid();
    m_Scene->updateSeries();

    UserHasSetsAbsciss();
}

void ChartForm::UserHasSetsAbsciss()
{
    TRange absciss_range;
    m_Scene->GetRootAbscissRange(&absciss_range);
    TRange visible_absciss_range;
    m_Scene->GetRootVisibleAbscissRange(&visible_absciss_range);

    if(visible_absciss_range.max > absciss_range.max)
        m_Scene->SetAbscissUserSetsInVisibleArea(true);
    else
        m_Scene->SetAbscissUserSetsInVisibleArea(false);
}

void ChartForm::UpdateAbscissScrollBar()
{
    TRange absciss_range;
    m_Scene->GetRootAbscissRange(&absciss_range);
    TRange visible_absciss_range;
    m_Scene->GetRootVisibleAbscissRange(&visible_absciss_range);
    double step;
    m_Scene->GetRootAbscissStep(&step);

    m_AbscissScrollBar->SetRange(absciss_range, visible_absciss_range, step);
}

void ChartForm::UpdateOrdinateScrollBar()
{
    TRange ordinate_range;
    m_Scene->GetRootOrdinateRange(&ordinate_range);
    TRange visible_ordinate_range;
    m_Scene->GetRootVisibleOrdinateRange(&visible_ordinate_range);
    double step;
    m_Scene->GetRootOrdinateStep(&step);

    m_OrdinateScrollBar->SetRange(ordinate_range, visible_ordinate_range, step);
}

void ChartForm::OnSelectSource(ChartFormSource *source)
{
    for(int i=0; i<m_ListSource.count(); i++) {

        m_ListSource[i]->SetRoot(false);
        m_ListSource[i]->SetActive(false);
        m_ListSource[i]->SetSelect(false);

        ChartFormScaleWidget *scaleWidget = NULL;
        m_ListSource[i]->GetScaleWidget(&scaleWidget);

     //   scaleWidget->setFixedWidth(SCALE_FIXED_WIDTH);
        m_ScaleOrdinateLayout->addWidget(scaleWidget, 0, Qt::AlignTop);
    }

    source->SetRoot(true);
    source->SetActive(true);
    source->SetSelect(true);
}

void ChartForm::OnClearSelect()
{
    foreach(ChartFormSource *pSource, m_ListSource) {
        pSource->SetSelect(false);
        pSource->SetActive(true);
    }
}

void ChartForm::resize_Canvas(QSize size)
{
    m_SizeScene = QRectF(0, 0, size.width(), size.height());
    m_Scene->setSceneRect(m_SizeScene);
    m_Scene->Repaint();
}

