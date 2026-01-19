#include "timelinewidget.h"

TimelineWidget::TimelineWidget(QWidget* parent)
    : QWidget(parent)
    , m_slider(nullptr)
    , m_timeLabel(nullptr)
    , m_descriptionLabel(nullptr)
    , m_restoreButton(nullptr)
    , m_currentIndex(-1)
{
    // 创建主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);

    // 创建时间轴标题
    QLabel* titleLabel = new QLabel("历史时间轴", this);
    QFont titleFont = titleLabel->font();
    titleFont.setBold(true);
    titleFont.setPointSize(10);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    // 创建时间显示标签
    m_timeLabel = new QLabel("时间: --", this);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_timeLabel);

    // 创建快照描述标签
    m_descriptionLabel = new QLabel("描述: --", this);
    m_descriptionLabel->setWordWrap(true);
    m_descriptionLabel->setStyleSheet("color: gray; font-size: 9pt;");
    mainLayout->addWidget(m_descriptionLabel);

    // 创建滑块
    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(0, 0);  // 初始范围 0-0
    m_slider->setValue(0);
    m_slider->setTickPosition(QSlider::TicksBelow);
    m_slider->setTickInterval(1);
    mainLayout->addWidget(m_slider);

    // 创建返回最新按钮
    m_restoreButton = new QPushButton("返回最新状态", this);
    m_restoreButton->setEnabled(false);  // 初始禁用
    m_restoreButton->setStyleSheet("QPushButton:disabled { color: gray; }");
    mainLayout->addWidget(m_restoreButton);

    // 添加弹性空间
    mainLayout->addStretch();

    // 连接信号
    connect(m_slider, &QSlider::valueChanged, this, &TimelineWidget::onSliderValueChanged);
    connect(m_restoreButton, &QPushButton::clicked, this, [this]() {
        emit restoreLatestRequested();
    });
}

void TimelineWidget::setSnapshots(const QList<MapSnapshot>& snapshots) {
    m_snapshots = snapshots;

    if (m_snapshots.isEmpty()) {
        m_slider->setRange(0, 0);
        m_slider->setEnabled(false);
        m_restoreButton->setEnabled(false);
        updateDisplay();
        return;
    }

    // 更新滑块范围
    m_slider->setRange(0, m_snapshots.size() - 1);
    m_slider->setEnabled(true);

    // 默认选中最新快照
    setCurrentIndex(m_snapshots.size() - 1);
}

void TimelineWidget::setCurrentIndex(int index) {
    if (index < 0 || index >= m_snapshots.size()) {
        return;
    }

    m_currentIndex = index;
    m_slider->blockSignals(true);  // 阻止信号触发
    m_slider->setValue(index);
    m_slider->blockSignals(false);

    // 更新按钮状态
    bool isLatest = (index == m_snapshots.size() - 1);
    m_restoreButton->setEnabled(!isLatest);

    updateDisplay();
}

void TimelineWidget::onSliderValueChanged(int value) {
    if (value < 0 || value >= m_snapshots.size()) {
        return;
    }

    m_currentIndex = value;

    // 更新按钮状态
    bool isLatest = (value == m_snapshots.size() - 1);
    m_restoreButton->setEnabled(!isLatest);

    updateDisplay();

    emit indexChanged(value);
}

void TimelineWidget::updateDisplay() {
    if (m_snapshots.isEmpty() || m_currentIndex < 0 || m_currentIndex >= m_snapshots.size()) {
        m_timeLabel->setText("时间: --");
        m_descriptionLabel->setText("描述: --");
        return;
    }

    const MapSnapshot& snapshot = m_snapshots[m_currentIndex];

    // 显示时间（格式: HH:mm:ss）
    QString timeStr = snapshot.timestamp().toString("HH:mm:ss");
    QString dateStr = snapshot.timestamp().toString("yyyy-MM-dd");
    m_timeLabel->setText(QString("时间: %1 %2").arg(dateStr, timeStr));

    // 显示描述
    QString desc = snapshot.description();
    if (desc.isEmpty()) {
        desc = QString("快照 #%1").arg(m_currentIndex + 1);
    }
    m_descriptionLabel->setText(QString("描述: %1").arg(desc));

    // 显示标记数量
    int markerCount = snapshot.markers().size();
    m_descriptionLabel->setText(m_descriptionLabel->text() +
                                QString("\n标记数: %1").arg(markerCount));
}
