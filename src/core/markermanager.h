#ifndef MARKERMANAGER_H
#define MARKERMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QDateTime>

#include "../data/marker.h"
#include "../data/mapsnapshot.h"

/**
 * @class MarkerManager
 * @brief 标记和快照管理器
 *
 * 负责管理地图标记和历史快照的核心业务逻辑：
 * - 添加/删除标记
 * - 自动创建快照
 * - 时间回溯（切换到历史快照）
 * - 数据持久化（内存 -> 后端同步由 ApiClient 负责）
 */
class MarkerManager : public QObject {
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象
     */
    explicit MarkerManager(QObject* parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~MarkerManager() override = default;

    // ========== 标记操作 ==========

    /**
     * @brief 添加一个新标记
     * @param marker 标记数据
     * @param createdBy 操作者（可选）
     * @return 成功返回 true
     *
     * 添加后会自动创建新的快照。
     */
    bool addMarker(const Marker& marker, const QString& createdBy = QString());

    /**
     * @brief 删除指定标记
     * @param markerId 标记ID
     * @param deletedBy 删除操作者（可选）
     * @return 成功返回 true
     *
     * 删除后会自动创建新的快照。
     */
    bool deleteMarker(const QString& markerId, const QString& deletedBy = QString());

    /**
     * @brief 获取当前显示的所有标记
     * @return 标记列表
     */
    QList<Marker> currentMarkers() const;

    /**
     * @brief 根据ID查找标记
     * @param markerId 标记ID
     * @return 找到返回标记对象，否则返回无效标记
     */
    Marker findMarker(const QString& markerId) const;

    // ========== 快照操作 ==========

    /**
     * @brief 获取所有历史快照
     * @return 快照列表（按时间顺序）
     */
    const QList<MapSnapshot>& snapshots() const { return m_snapshots; }

    /**
     * @brief 获取当前快照索引
     * @return 索引值（0 到 snapshotCount() - 1）
     */
    int currentSnapshotIndex() const { return m_currentSnapshotIndex; }

    /**
     * @brief 获取快照总数
     * @return 快照数量
     */
    int snapshotCount() const { return m_snapshots.size(); }

    /**
     * @brief 回溯到指定索引的快照
     * @param index 快照索引
     * @return 成功返回 true
     *
     * 切换后会触发 currentSnapshotChanged 信号。
     */
    bool restoreSnapshot(int index);

    /**
     * @brief 回溯到最新快照（即当前状态）
     */
    void restoreLatestSnapshot();

    /**
     * @brief 手动创建快照
     * @param description 快照描述（可选）
     *
     * 通常不需要手动调用，增删标记会自动创建快照。
     */
    void createSnapshot(const QString& description = QString());

    /**
     * @brief 获取指定索引的快照
     * @param index 快照索引
     * @return 快照对象
     */
    const MapSnapshot& snapshotAt(int index) const;

    // ========== 数据导入/导出 ==========

    /**
     * @brief 从快照列表加载历史数据
     * @param snapshots 快照列表
     *
     * 用于从后端同步数据。
     */
    void loadFromSnapshots(const QList<MapSnapshot>& snapshots);

    /**
     * @brief 导出当前所有快照
     * @return 快照列表
     *
     * 用于同步到后端。
     */
    QList<MapSnapshot> exportSnapshots() const { return m_snapshots; }

signals:
    /**
     * @brief 当前快照改变信号
     * @param index 新的快照索引
     * @param snapshot 快照对象
     *
     * 当回溯到不同时间点时触发。
     */
    void currentSnapshotChanged(int index, const MapSnapshot& snapshot);

    /**
     * @brief 新快照创建信号
     * @param snapshot 新创建的快照
     *
     * 当添加/删除标记创建新快照时触发。
     */
    void snapshotCreated(const MapSnapshot& snapshot);

    /**
     * @brief 标记列表改变信号
     * @param markers 当前显示的标记列表
     *
     * 当切换快照或修改标记时触发。
     */
    void markersChanged(const QList<Marker>& markers);

private:
    /**
     * @brief 创建快照的内部实现
     * @param description 快照描述
     * @return 新创建的快照
     */
    MapSnapshot createSnapshotInternal(const QString& description);

private:
    QList<MapSnapshot> m_snapshots;        ///< 历史快照列表
    int m_currentSnapshotIndex;            ///< 当前查看的快照索引
    QMap<QString, Marker> m_currentMarkers; ///< 当前显示的标记 (ID -> Marker)
};

#endif // MARKERMANAGER_H
