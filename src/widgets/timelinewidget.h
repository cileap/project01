#ifndef TimELINEWIDGET_H
#define TimELINEWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "../data/mapsnapshot.h"

/**
 * @class TimelineWidget
 * @brief 时间轴控制组件
 *
 * 提供时间回溯的用户界面：
 * - 滑块选择历史时间点
 * - 显示当前时间和快照描述
 * - 返回最新状态按钮
 */
class TimelineWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口
     */
    explicit TimelineWidget(QWidget* parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~TimelineWidget() override = default;

    /**
     * @brief 设置快照列表
     * @param snapshots 快照列表
     */
    void setSnapshots(const QList<MapSnapshot>& snapshots);

    /**
     * @brief 设置当前快照索引
     * @param index 快照索引
     */
    void setCurrentIndex(int index);

    /**
     * @brief 获取当前选中的索引
     * @return 索引值
     */
    int currentIndex() const { return m_currentIndex; }

signals:
    /**
     * @brief 快照索引改变信号
     * @param index 新的索引值
     *
     * 用户拖动滑块时触发。
     */
    void indexChanged(int index);

    /**
     * @brief 请求返回最新状态信号
     */
    void restoreLatestRequested();

private slots:
    /**
     * @brief 滑块值改变处理
     * @param value 滑块位置值
     */
    void onSliderValueChanged(int value);

private:
    /**
     * @brief 更新时间显示标签
     */
    void updateDisplay();

private:
    QSlider* m_slider;                  ///< 时间轴滑块
    QLabel* m_timeLabel;                ///< 当前时间显示
    QLabel* m_descriptionLabel;         ///< 快照描述显示
    QPushButton* m_restoreButton;       ///< 返回最新按钮
    QList<MapSnapshot> m_snapshots;     ///< 快照列表
    int m_currentIndex;                 ///< 当前索引
};

#endif // TimELINEWIDGET_H
