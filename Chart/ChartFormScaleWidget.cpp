
#include "ChartFormScaleWidget.h"
#include "AppResource.h"
#include "Errors.h"


ChartFormScaleWidget::ChartFormScaleWidget(ChartFormScene *pScene, QWidget *parent)
    : QWidget(parent)
{
    m_checkBox = new QCheckBox();

    m_groupBox = new QGroupBox();
    m_groupBox->setCheckable(true);
    m_groupBox->hide();

    QLabel *scaleLabel = new QLabel(CHARTFORM_STR_SCALE);

    m_indexScaleBox = new QComboBox();
 //   m_indexScaleBox->setFixedWidth(100);

    QPushButton *zoomPlusButton = new QPushButton();
    QIcon zoomXPlusIcon(":/images/sine_plus.ico");
    zoomPlusButton->setIcon(zoomXPlusIcon);
    zoomPlusButton->setIconSize(QSize(18,18));
    zoomPlusButton->setFixedHeight(m_indexScaleBox->sizeHint().height());
    zoomPlusButton->setContentsMargins(0,0,0,0);
    zoomPlusButton->setStyleSheet("QPushButton {border: 1px solid #adadad; background-color:#e1e1e1}"
                                   "QPushButton:hover{background-color:#e5f1fb; border: 1px solid #0078d7;}"
                                   "QPushButton:pressed{background-color:#cce4f7; border: 1px solid #005499; padding-left: 2px; padding-top: 2px;}");

    QPushButton *zoomMinusButton = new QPushButton();
    QIcon zoomMinusIcon(":/images/sine_minus2.ico");
    zoomMinusButton->setIcon(zoomMinusIcon);
    zoomMinusButton->setIconSize(QSize(18,18));
    zoomMinusButton->setFixedHeight(m_indexScaleBox->sizeHint().height());
    zoomMinusButton->setContentsMargins(0,0,0,0);
    zoomMinusButton->setStyleSheet("QPushButton {border: 1px solid #adadad; background-color:#e1e1e1}"
                                   "QPushButton:hover{background-color:#e5f1fb; border: 1px solid #0078d7;}"
                                   "QPushButton:pressed{background-color:#cce4f7; border: 1px solid #005499; padding-left: 2px; padding-top: 2px;}");

    QHBoxLayout *ScaleLayout = new QHBoxLayout();
    ScaleLayout->addWidget(m_indexScaleBox, 1);
    ScaleLayout->addWidget(zoomPlusButton, 0);
    ScaleLayout->addWidget(zoomMinusButton, 0);
    ScaleLayout->setSpacing(0);
    ScaleLayout->setAlignment(Qt::AlignLeft);

    QLabel *offsetLabel = new QLabel(CHARTFORM_STR_OFFSET);
    m_offsetBox = new QComboBox();
  //  m_offsetBox->setFixedWidth(100);

    QPushButton *offsetLeftButton = new QPushButton();
    QIcon offsetLeftIcon(":/images/pos_left.ico");
    offsetLeftButton->setIcon(offsetLeftIcon);
    offsetLeftButton->setIconSize(QSize(18,18));
    offsetLeftButton->setFixedHeight(m_offsetBox->sizeHint().height());
    offsetLeftButton->setContentsMargins(0,0,0,0);
    offsetLeftButton->setStyleSheet("QPushButton {border: 1px solid #adadad; background-color:#e1e1e1}"
                                   "QPushButton:hover{background-color:#e5f1fb; border: 1px solid #0078d7;}"
                                   "QPushButton:pressed{background-color:#cce4f7; border: 1px solid #005499; padding-left: 2px; padding-top: 2px;}");

    QPushButton *offsetRightButton = new QPushButton();
    QIcon offsetRightIcon(":/images/pos_right.ico");
    offsetRightButton->setIcon(offsetRightIcon);
    offsetRightButton->setIconSize(QSize(18,18));
    offsetRightButton->setFixedHeight(m_offsetBox->sizeHint().height());
    offsetRightButton->setContentsMargins(0,0,0,0);
    offsetRightButton->setStyleSheet("QPushButton {border: 1px solid #adadad; background-color:#e1e1e1}"
                                   "QPushButton:hover{background-color:#e5f1fb; border: 1px solid #0078d7;}"
                                   "QPushButton:pressed{background-color:#cce4f7; border: 1px solid #005499; padding-left: 2px; padding-top: 2px;}");

    QHBoxLayout *OffsetLayout = new QHBoxLayout();
    OffsetLayout->addWidget(m_offsetBox, 1);
    OffsetLayout->addWidget(offsetLeftButton, 0);
    OffsetLayout->addWidget(offsetRightButton, 0);
    OffsetLayout->setSpacing(0);
    OffsetLayout->setAlignment(Qt::AlignLeft);

    QGridLayout *Layout = new QGridLayout();
    Layout->addWidget(scaleLabel, 0, 0, Qt::AlignLeft);
    Layout->addLayout(ScaleLayout, 0, 1, Qt::AlignLeft);
    Layout->addWidget(offsetLabel, 1, 0, Qt::AlignLeft);
    Layout->addLayout(OffsetLayout, 1, 1, Qt::AlignLeft);
    Layout->setAlignment(Qt::AlignTop);
    Layout->setSpacing(0);
    Layout->setRowStretch(0, 0);
    Layout->setRowStretch(0, 1);

    m_groupBox->setLayout(Layout);

    QHBoxLayout *centralLayout = new QHBoxLayout();
    centralLayout->addWidget(m_checkBox);
    centralLayout->addWidget(m_groupBox);
    centralLayout->setContentsMargins(0,0,0,0);

    setLayout(centralLayout);

    connect(m_indexScaleBox, &QComboBox::currentIndexChanged, [=](int mainScale) {
        if((mainScale >= 0) && (mainScale < m_indexScaleBox->count())) {
            emit OnSetIndex(mainScale);
            emit IndexScaleChanged(mainScale);
        }
    });

    connect(zoomMinusButton, &QPushButton::clicked, [=]() {
        int mainScale = m_indexScaleBox->currentIndex();
        mainScale++;
        if((mainScale >= 0) && (mainScale < m_indexScaleBox->count()))
            m_indexScaleBox->setCurrentIndex(mainScale);
    });

    connect(zoomPlusButton, &QPushButton::clicked, [=]() {
        int mainScale = m_indexScaleBox->currentIndex();
        mainScale--;
        if((mainScale >= 0) && (mainScale < m_indexScaleBox->count()))
            m_indexScaleBox->setCurrentIndex(mainScale);
    });

    connect(m_offsetBox, &QComboBox::currentIndexChanged, [=](int offsetIndex) {
        if((offsetIndex >= 0) && (offsetIndex < m_offsetBox->count())) {
            QVariant var = m_offsetBox->itemData(offsetIndex);
            if(var.isValid()) {
                double offset = var.value<double>();
                emit VisibleOffsetChanged(offset);
                SetVisibleOffset(offset);
            }
        }
    });

    connect(offsetRightButton, &QPushButton::clicked, [=]() {
        int offsetIndex = m_offsetBox->currentIndex();
        offsetIndex++;
        if(offsetIndex < m_offsetBox->count())
            m_offsetBox->setCurrentIndex(offsetIndex);
    });

    connect(offsetLeftButton, &QPushButton::clicked, [=]() {
        int offsetIndex = m_offsetBox->currentIndex();
        offsetIndex--;
        if(offsetIndex >= 0)
            m_offsetBox->setCurrentIndex(offsetIndex);
    });

    connect(m_checkBox, SIGNAL(clicked()), this, SIGNAL(Select()));

    connect(m_checkBox, &QCheckBox::stateChanged, [=](int state) {
        if(state == Qt::Checked) {
            m_groupBox->setVisible(true);
            m_groupBox->setChecked(true);
            m_checkBox->setVisible(false);
            m_userSelect = true;
        }
    });

    connect(m_groupBox, &QGroupBox::clicked, [=](bool checked) {
        if(checked == false) {
            m_groupBox->setVisible(false);
            m_checkBox->setVisible(true);
            m_checkBox->setChecked(false);
            m_userSelect = false;
        }
    });

    m_SeriesItem = NULL;
    m_Scene = pScene;

    m_mainScaleRepository.GetMainXScalesList(m_listMainScale);
    m_userSelect = false;
}


ChartFormScaleWidget::ChartFormScaleWidget(ChartGraphics2DGraphItem *pSeriesItem, QWidget *parent)
    : QWidget(parent)
{
    m_checkBox = new QCheckBox();

    m_groupBox = new QGroupBox();
    m_groupBox->setCheckable(true);
    m_groupBox->hide();

    QLabel *scaleLabel = new QLabel(CHARTFORM_STR_SCALE);

    m_indexScaleBox = new QComboBox();
  //  m_indexScaleBox->setFixedWidth(100);

    QPushButton *zoomPlusButton = new QPushButton();
    QIcon zoomPlusIcon(":/images/sine_plus.ico");
    zoomPlusButton->setIcon(zoomPlusIcon);
    zoomPlusButton->setIconSize(QSize(18,18));
    zoomPlusButton->setFixedHeight(m_indexScaleBox->sizeHint().height());
    zoomPlusButton->setContentsMargins(0,0,0,0);
    zoomPlusButton->setStyleSheet("QPushButton {border: 1px solid #adadad; background-color:#e1e1e1}"
                                   "QPushButton:hover{background-color:#e5f1fb; border: 1px solid #0078d7;}"
                                   "QPushButton:pressed{background-color:#cce4f7; border: 1px solid #005499; padding-left: 2px; padding-top: 2px;}");


    QPushButton *zoomMinusButton = new QPushButton();
    QIcon zoomMinusIcon(":/images/sine_minus.ico");
    zoomMinusButton->setIcon(zoomMinusIcon);
    zoomMinusButton->setIconSize(QSize(18,18));
    zoomMinusButton->setFixedHeight(m_indexScaleBox->sizeHint().height());
    zoomMinusButton->setContentsMargins(0,0,0,0);
    zoomMinusButton->setStyleSheet("QPushButton {border: 1px solid #adadad; background-color:#e1e1e1}"
                                   "QPushButton:hover{background-color:#e5f1fb; border: 1px solid #0078d7;}"
                                   "QPushButton:pressed{background-color:#cce4f7; border: 1px solid #005499; padding-left: 2px; padding-top: 2px;}");

    QHBoxLayout *scaleLayout = new QHBoxLayout();
    scaleLayout->addWidget(m_indexScaleBox, 1);
    scaleLayout->addWidget(zoomMinusButton, 0);
    scaleLayout->addWidget(zoomPlusButton, 0);
    scaleLayout->setSpacing(0);
    scaleLayout->setAlignment(Qt::AlignLeft);

    QLabel *offsetLabel = new QLabel(CHARTFORM_STR_OFFSET);
    m_offsetBox = new QComboBox();
 //   m_offsetBox->setFixedWidth(100);

    QPushButton *offsetHighButton = new QPushButton();
    QIcon offsetHighIcon(":/images/pos_high.ico");
    offsetHighButton->setIcon(offsetHighIcon);
    offsetHighButton->setIconSize(QSize(18,18));
    offsetHighButton->setFixedHeight(m_offsetBox->sizeHint().height());
    offsetHighButton->setContentsMargins(0,0,0,0);
    offsetHighButton->setStyleSheet("QPushButton {border: 1px solid #adadad; background-color:#e1e1e1;}"
                                   "QPushButton:hover{background-color:#e5f1fb; border: 1px solid #0078d7;}"
                                   "QPushButton:pressed{background-color:#cce4f7; border: 1px solid #005499; padding-left: 2px; padding-top: 2px;}");

    QPushButton *offsetLowButton = new QPushButton();
    QIcon offsetLowIcon(":/images/pos_low.ico");
    offsetLowButton->setIcon(offsetLowIcon);
    offsetLowButton->setIconSize(QSize(18,18));
    offsetLowButton->setFixedHeight(m_offsetBox->sizeHint().height());
    offsetLowButton->setContentsMargins(0,0,0,0);
    offsetLowButton->setStyleSheet("QPushButton {border: 1px solid #adadad; background-color:#e1e1e1}"
                                   "QPushButton:hover{background-color:#e5f1fb; border: 1px solid #0078d7;}"
                                   "QPushButton:pressed{background-color:#cce4f7; border: 1px solid #005499; padding-left: 2px; padding-top: 2px;}");

    QHBoxLayout *offsetLayout = new QHBoxLayout();
    offsetLayout->addWidget(m_offsetBox, 1);
    offsetLayout->addWidget(offsetHighButton, 0);
    offsetLayout->addWidget(offsetLowButton, 0);
    offsetLayout->setSpacing(0);
    offsetLayout->setAlignment(Qt::AlignLeft);

    QGridLayout *Layout = new QGridLayout();
    Layout->addWidget(scaleLabel, 0, 0, Qt::AlignLeft);
    Layout->addLayout(scaleLayout, 0, 1, Qt::AlignLeft);
    Layout->addWidget(offsetLabel, 1, 0, Qt::AlignLeft);
    Layout->addLayout(offsetLayout, 1, 1, Qt::AlignLeft);
    Layout->setAlignment(Qt::AlignTop);
    Layout->setSpacing(0);
    Layout->setRowStretch(0, 0);
    Layout->setRowStretch(0, 1);

    m_groupBox->setLayout(Layout);

    QHBoxLayout *centralLayout = new QHBoxLayout();
    centralLayout->addWidget(m_checkBox);
    centralLayout->addWidget(m_groupBox);
    centralLayout->setContentsMargins(0,0,0,0);

    setLayout(centralLayout);


    connect(m_indexScaleBox, &QComboBox::currentIndexChanged, [=](int mainScale) {
        if((mainScale >= 0) && (mainScale < m_indexScaleBox->count())) {
            emit IndexScaleChanged(mainScale);
            emit OnSetIndex(mainScale);
        }
    });

    connect(zoomPlusButton, &QPushButton::clicked, [=]() {
        int mainScale = m_indexScaleBox->currentIndex();
        mainScale++;
        if((mainScale >= 0) && (mainScale < m_indexScaleBox->count()))
            m_indexScaleBox->setCurrentIndex(mainScale);
    });

    connect(zoomMinusButton, &QPushButton::clicked, [=]() {
        int mainScale = m_indexScaleBox->currentIndex();
        mainScale--;
        if((mainScale >= 0) && (mainScale < m_indexScaleBox->count()))
            m_indexScaleBox->setCurrentIndex(mainScale);
    });

    connect(m_offsetBox, &QComboBox::currentIndexChanged, [=](int offsetIndex) {
        if((offsetIndex >= 0) && (offsetIndex < m_offsetBox->count())) {
            QVariant var = m_offsetBox->itemData(offsetIndex);
            if(var.isValid()) {
                double offset = var.value<double>();
                bool root = false;
                pSeriesItem->getRoot(&root);
                if(root) {
                    emit VisibleOffsetChanged(offset);
                    emit OnSetVisibleOffset(offset);
                }
                else
                    emit OnSetVisibleOffset(offset);
            }
        }
    });

    connect(offsetHighButton, &QPushButton::clicked, [=]() {
        int offsetIndex = m_offsetBox->currentIndex();
        offsetIndex++;
        if(offsetIndex < m_offsetBox->count())
            m_offsetBox->setCurrentIndex(offsetIndex);
    });

    connect(offsetLowButton, &QPushButton::clicked, [=]() {
        int offsetIndex = m_offsetBox->currentIndex();
        offsetIndex--;
        if(offsetIndex >= 0)
            m_offsetBox->setCurrentIndex(offsetIndex);
    });

    connect(m_checkBox, &QCheckBox::stateChanged, [=](int state) {
        if(state == Qt::Checked) {
            m_groupBox->setVisible(true);
            m_groupBox->setChecked(true);
            m_checkBox->setVisible(false);
            m_userSelect = true;
        }
    });

    connect(m_groupBox, &QGroupBox::clicked, [=](bool checked) {
        if(checked == false) {
            m_groupBox->setVisible(false);
            m_checkBox->setVisible(true);
            m_checkBox->setChecked(false);
            m_userSelect = false;
        }
    });


    m_SeriesItem = pSeriesItem;
    m_Scene = NULL;

    m_mainScaleRepository.GetMainYScalesList(m_listMainScale);
    m_userSelect = false;
}

void ChartFormScaleWidget::Init(const QColor colorStart, const QString strName, const QString strUnitName)
{
    m_color = colorStart;

    QColor colorEnd;
    colorEnd = colorStart;
    colorEnd.setAlphaF(0.2);


    m_checkBox->setText(strName);
    m_checkBox->setStyleSheet("QCheckBox {border: 1px solid gray; border-radius: 2px; padding-left: 1px; background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 " +  colorStart.name(QColor::HexArgb) + ",stop: 1 " + colorEnd.name(QColor::HexArgb)+")};");

    m_groupBox->setTitle(strName);
    m_groupBox->setStyleSheet("QGroupBox {border: 1px solid gray; border-radius: 2px; padding-top: 12px; background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 " +  colorStart.name(QColor::HexArgb) + ",stop: 1 " + colorEnd.name(QColor::HexArgb)+")};"
                              "QGroupBox::title {subcontrol-origin: margin; subcontrol-position: top left; padding-left: 0px;}");

    m_UnitName = strUnitName;

    Update();
}

void ChartFormScaleWidget::SetName(const QString strName)
{
    m_checkBox->setText(strName);
    m_groupBox->setTitle(strName);
}

void ChartFormScaleWidget::SetSelect(const bool select)
{
    if(!m_userSelect) {
        if(select) {
            m_groupBox->setVisible(true);
            m_groupBox->setChecked(true);
            m_checkBox->setVisible(false);
        }
        else {
            m_groupBox->setVisible(false);
            m_checkBox->setChecked(false);
            m_checkBox->setVisible(true);
        }
    }
}

void ChartFormScaleWidget::GetSelect(bool *select) const
{
    *select = m_userSelect;
}

void ChartFormScaleWidget::SetActive(const bool active)
{
    QColor color = m_color;
    if(!active)
        color.setAlpha(50);

    QColor colorEnd;
    colorEnd = color;
    colorEnd.setAlphaF(0.2);

    m_checkBox->setStyleSheet("QCheckBox {border: 1px solid gray; border-radius: 2px; padding-left: 1px; background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 " +  color.name(QColor::HexArgb) + ",stop: 1 " + colorEnd.name(QColor::HexArgb)+")};");
    m_groupBox->setStyleSheet("QGroupBox {border: 1px solid gray; border-radius: 2px; padding-top: 12px; background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 " +  color.name(QColor::HexArgb) + ",stop: 1 " + colorEnd.name(QColor::HexArgb)+")};"
                              "QGroupBox::title {subcontrol-origin: margin; subcontrol-position: top left; padding-left: 0px;}");
}

void ChartFormScaleWidget::SetColor(const QColor color)
{
    m_color = color;

    QColor colorEnd;
    colorEnd = color;
    colorEnd.setAlphaF(0.2);

    m_checkBox->setStyleSheet("QCheckBox {border: 1px solid gray; border-radius: 2px; padding-left: 1px; background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 " +  color.name(QColor::HexArgb) + ",stop: 1 " + colorEnd.name(QColor::HexArgb)+")};");
    m_groupBox->setStyleSheet("QGroupBox {border: 1px solid gray; border-radius: 2px; padding-top: 12px; background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 " +  color.name(QColor::HexArgb) + ",stop: 1 " + colorEnd.name(QColor::HexArgb)+")};"
                              "QGroupBox::title {subcontrol-origin: margin; subcontrol-position: top left; padding-left: 0px;}");
}

void ChartFormScaleWidget::SetUnit(const QString strUnitName)
{
    m_UnitName = strUnitName;
    Update();
}

void ChartFormScaleWidget::SetVisibleOffset(double offset)
{
    const bool oldState = m_offsetBox->blockSignals(true);

    if(m_SeriesItem) {
        m_SeriesItem->setVisibleOrdinateOffset(offset);
        m_SeriesItem->exec();
        m_SeriesItem->update();

        TRange visible_ordinate_range;
        m_SeriesItem->getVisibleOrdinateRange(&visible_ordinate_range);
        unsigned int precision;
        m_SeriesItem->getOrdinatePrecision(&precision);
        double step;
        m_SeriesItem->getOrdinateStep(&step);

        m_offsetBox->clear();
        double pos = visible_ordinate_range.min - step;
        double pos_correct = step*round(pos/step);
        while(pos < visible_ordinate_range.max + step) {
            QString str = QString::number(pos_correct, 'f', precision);
            m_offsetBox->addItem(str, pos);
            pos = pos + step;
            pos_correct = step*round(pos/step);
        }

        for(int i=0; i<m_offsetBox->count(); i++) {
            QVariant var = m_offsetBox->itemData(i);
            if(var.isValid()) {
                double locOffset = var.value<double>();
                if(locOffset == offset)
                    m_offsetBox->setCurrentIndex(i);
            }
        }
        if(m_offsetBox->currentIndex() == 0)    // Нулевой индекс должен быть недосягаем
            m_offsetBox->setCurrentIndex(1);
    }
    if(m_Scene) {
        TRange visible_absciss_range;
        m_Scene->GetRootVisibleAbscissRange(&visible_absciss_range);
        unsigned int precision;
        m_Scene->GetRootAbscissPrecision(&precision);
        double step;
        m_Scene->GetRootAbscissStep(&step);

        m_offsetBox->clear();
        double pos = visible_absciss_range.min - step;
        double pos_correct = step*round(pos/step);
        while(pos < visible_absciss_range.max + step) {
            QString str = m_Scene->convertAbscissTime(pos_correct, precision);
            m_offsetBox->addItem(str, pos);
            pos = pos + step;
            pos_correct = step*round(pos/step);
        }

        for(int i=0; i<m_offsetBox->count(); i++) {
            QVariant var = m_offsetBox->itemData(i);
            if(var.isValid()) {
                double locOffset = var.value<double>();
                if(locOffset == offset)
                    m_offsetBox->setCurrentIndex(i);
            }
        }
    }

    m_offsetBox->blockSignals(oldState);
}

void ChartFormScaleWidget::SetIndexScale(const unsigned int index)
{
    const bool oldState = m_indexScaleBox->blockSignals(true);

    m_indexScaleBox->setCurrentIndex(index);

    m_indexScaleBox->blockSignals(oldState);
}

void ChartFormScaleWidget::Update()
{
    const bool oldState = m_indexScaleBox->blockSignals(true);

    m_indexScaleBox->clear();

    foreach(QString strMainScale, m_listMainScale) {
        m_indexScaleBox->addItem(strMainScale + m_UnitName + CHARTFORM_STR_DIV);
    }
    unsigned int OrdinateIndexScale;
    if(m_SeriesItem)
        m_SeriesItem->getOrdinateIndexScale(&OrdinateIndexScale);
    if(m_Scene)
        m_Scene->GetRootOrdinateIndexScale(&OrdinateIndexScale);

    emit m_indexScaleBox->setCurrentIndex(OrdinateIndexScale);

    TRange visible_ordinate_range;
    if(m_SeriesItem)
        m_SeriesItem->getVisibleOrdinateRange(&visible_ordinate_range);
    if(m_Scene)
        m_Scene->GetRootVisibleOrdinateRange(&visible_ordinate_range);

    SetVisibleOffset(visible_ordinate_range.min);

    m_indexScaleBox->blockSignals(oldState);
}

void ChartFormScaleWidget::OnSetIndex(unsigned int index)
{
    TRange visible_range;
    if(m_SeriesItem) {
        m_SeriesItem->setOrdinateIndexScale(index);
        m_SeriesItem->getVisibleOrdinateRange(&visible_range);
        double step;
        m_SeriesItem->getOrdinateStep(&step);
        double pos_correct_min = step*round(visible_range.min/step);
        if(visible_range.min != pos_correct_min) {                      // Значит после смены сетки мы не в текущем шаге сетки, поэтом скорректируем видимую область
            emit VisibleOffsetChanged(pos_correct_min);                 // Обновим смещение
            m_SeriesItem->getVisibleOrdinateRange(&visible_range);      // Получаю пересчитанное значение range
        }
    }
    if(m_Scene) {
        m_Scene->SetRootAbscissIndexScale(index);
        m_Scene->GetRootVisibleAbscissRange(&visible_range);
        double step;
        m_Scene->GetRootAbscissStep(&step);
        double pos_correct_min = step*round(visible_range.min/step);
        if(visible_range.min != pos_correct_min) {                      // Значит после смены сетки мы не в текущем шаге сетки, поэтом скорректируем видимую область
            emit VisibleOffsetChanged(pos_correct_min);                 // Обновим смещение
            m_Scene->GetRootVisibleAbscissRange(&visible_range);        // Получаю пересчитанное значение range
        }
    }

    SetVisibleOffset(visible_range.min);
}

void ChartFormScaleWidget::OnSetVisibleOffset(double offset)
{
    SetVisibleOffset(offset);
}

void ChartFormScaleWidget::mousePressEvent(QMouseEvent *event)
{
    emit Select();
}

void ChartFormScaleWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
