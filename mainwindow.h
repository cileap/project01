#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QDockWidget>

#include "src/widgets/mapview.h"
#include "src/widgets/timelinewidget.h"
#include "src/core/markermanager.h"
#include "src/network/apiclient.h"

/**
 * @class MainWindow
 * @brief 主窗口
 *
 * 整合所有功能模块的主界面：
 * - 中央地图显示区域
 * - 左侧控制面板（添加标记按钮、同步按钮等）
 * - 底部时间轴（可停靠为独立窗口）
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~MainWindow() override = default;

private slots:
    /**
     * @brief 处理添加标记请求
     * @param normalizedPos 归一化坐标位置
     */
    void onAddMarkerRequested(const QPointF& normalizedPos);

    /**
     * @brief 处理删除标记请求
     * @param markerId 标记ID
     */
    void onDeleteMarkerRequested(const QString& markerId);

    /**
     * @brief 处理添加标记按钮点击
     */
    void onAddMarkerButtonClicked();

    /**
     * @brief 处理时间轴索引变化
     * @param index 新的索引
     */
    void onTimelineIndexChanged(int index);

    /**
     * @brief 处理返回最新状态按钮
     */
    void onRestoreLatestClicked();

    /**
     * @brief 处理标记列表变化
     * @param markers 新的标记列表
     */
    void onMarkersChanged(const QList<Marker>& markers);

    /**
     * @brief 处理从服务器同步数据
     */
    void onSyncFromServer();

    /**
     * @brief 处理快照获取成功
     * @param snapshots 快照列表
     */
    void onSnapshotsFetched(const QList<MapSnapshot>& snapshots);

    /**
     * @brief 处理网络错误
     * @param error 错误信息
     */
    void onNetworkError(const QString& error);

private:
    /**
     * @brief 初始化UI
     */
    void setupUi();

    /**
     * @brief 创建控制面板
     * @return 控制面板widget
     */
    QWidget* createControlPanel();

    /**
     * @brief 显示添加标记对话框
     * @param normalizedPos 点击位置
     * @return 用户输入的标记，如果取消则返回无效标记
     */
    Marker showAddMarkerDialog(const QPointF& normalizedPos);

private:
    // UI组件
    MapView* m_mapView;                 ///< 地图显示视图
    TimelineWidget* m_timelineWidget;   ///< 时间轴组件
    QPushButton* m_addMarkerButton;     ///< 添加标记按钮
    QPushButton* m_syncButton;          ///< 同步按钮

    // 业务逻辑组件
    MarkerManager* m_markerManager;     ///< 标记管理器
    ApiClient* m_apiClient;             ///< API客户端
};

#endif // MAINWINDOW_H
