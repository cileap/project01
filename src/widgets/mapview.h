#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QPointF>
#include <QMenu>

#include "../data/marker.h"

/**
 * @class MapView
 * @brief 地图显示组件
 *
 * 基于 QGraphicsView 实现的地图显示组件，支持：
 * - 加载并显示地图图片
 * - 鼠标拖拽平移
 * - 鼠标滚轮缩放
 * - 在地图上添加/显示标记点
 * - 点击标记触发信号
 */
class MapView : public QGraphicsView {
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口
     */
    explicit MapView(QWidget* parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~MapView() override = default;

    /**
     * @brief 设置地图图片
     * @param pixmap 地图图片
     *
     * 如果没有提供地图图片，将使用占位符（灰色背景）。
     */
    void setMapPixmap(const QPixmap& pixmap);

    /**
     * @brief 清除所有标记点
     */
    void clearMarkers();

    /**
     * @brief 添加一个标记点到地图上
     * @param marker 标记数据
     */
    void addMarker(const Marker& marker);

    /**
     * @brief 批量添加标记点
     * @param markers 标记列表
     */
    void addMarkers(const QList<Marker>& markers);

    /**
     * @brief 移除指定的标记点
     * @param markerId 要移除的标记ID
     */
    void removeMarker(const QString& markerId);

    /**
     * @brief 将像素坐标转换为归一化坐标
     * @param pixelPos 场景中的像素坐标
     * @return 归一化坐标 (0.0-1.0)
     */
    QPointF pixelToNormalized(const QPointF& pixelPos) const;

    /**
     * @brief 将归一化坐标转换为像素坐标
     * @param normalizedPos 归一化坐标 (0.0-1.0)
     * @return 场景中的像素坐标
     */
    QPointF normalizedToPixel(const QPointF& normalizedPos) const;

    /**
     * @brief 启用/禁用添加标记模式
     * @param enabled true 为启用，false 为禁用
     *
     * 启用后，点击地图会触发 addMarkerRequested 信号。
     */
    void setAddMarkerMode(bool enabled);

    /**
     * @brief 获取当前缩放级别
     * @return 缩放因子 (1.0 = 原始大小)
     */
    double zoomLevel() const { return m_zoomLevel; }

signals:
    /**
     * @brief 请求添加标记信号
     * @param normalizedPos 归一化坐标位置
     *
     * 在添加标记模式下点击地图时触发。
     */
    void addMarkerRequested(const QPointF& normalizedPos);

    /**
     * @brief 标记被点击信号
     * @param markerId 标记ID
     *
     * 用户点击地图上的标记点时触发。
     */
    void markerClicked(const QString& markerId);

    /**
     * @brief 缩放级别改变信号
     * @param zoomLevel 新的缩放因子
     */
    void zoomChanged(double zoomLevel);

    /**
     * @brief 请求删除标记信号
     * @param markerId 要删除的标记ID
     *
     * 用户通过右键菜单删除标记时触发。
     */
    void deleteMarkerRequested(const QString& markerId);

protected:
    /**
     * @brief 鼠标滚轮事件处理（实现缩放）
     */
    void wheelEvent(QWheelEvent* event) override;

    /**
     * @brief 鼠标按下事件处理（实现拖拽和点击）
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * @brief 鼠标移动事件处理（实现拖拽）
     */
    void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * @brief 鼠标释放事件处理
     */
    void mouseReleaseEvent(QMouseEvent* event) override;

    /**
     * @brief 右键菜单事件处理
     */
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    /**
     * @brief 更新标记显示
     *
     * 根据当前缩放级别调整标记点的大小。
     */
    void updateMarkerAppearance();

    /**
     * @brief 显示标记的右键上下文菜单
     * @param pos 菜单位置
     * @param markerId 标记ID
     * @param note 标记备注
     */
    void showMarkerContextMenu(const QPoint& pos, const QString& markerId, const QString& note);

private:
    QGraphicsScene* m_scene;                ///< 图形场景
    QGraphicsPixmapItem* m_mapItem;         ///< 地图图片项
    QMap<QString, QGraphicsEllipseItem*> m_markerItems;  ///< 标记图形项映射 (ID -> Item)

    // 交互状态
    bool m_isDragging;                      ///< 是否正在拖拽
    QPoint m_lastDragPos;                   ///< 上次拖拽位置
    double m_zoomLevel;                     ///< 当前缩放级别
    double m_minZoom;                       ///< 最小缩放级别
    double m_maxZoom;                       ///< 最大缩放级别
    bool m_addMarkerMode;                   ///< 是否处于添加标记模式
    QPointF m_mapSize;                      ///< 地图尺寸（像素）
};

#endif // MAPVIEW_H
