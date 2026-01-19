#ifndef MAPSNAPSHOT_H
#define MAPSNAPSHOT_H

#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include "marker.h"

/**
 * @class MapSnapshot
 * @brief 地图历史快照数据结构
 *
 * 表示某个时间点的地图完整状态，包含该时刻所有标记的完整数据。
 * 类似 Git 的 commit，每次快照保存完整的标记列表，支持回溯到任意历史状态。
 */
class MapSnapshot {
public:
    /**
     * @brief 默认构造函数
     */
    MapSnapshot() = default;

    /**
     * @brief 完整构造函数
     * @param timestamp 快照时间戳
     * @param markers 该时刻的所有标记列表
     * @param description 快照描述（可选）
     */
    MapSnapshot(const QDateTime& timestamp,
                const QList<Marker>& markers,
                const QString& description = QString());

    // ========== Getters ==========
    /**
     * @brief 获取快照唯一标识符
     * @return 快照ID字符串
     */
    QString snapshotId() const { return m_snapshotId; }

    /**
     * @brief 获取快照时间戳
     * @return 快照创建时间
     */
    QDateTime timestamp() const { return m_timestamp; }

    /**
     * @brief 获取该时刻的所有标记
     * @return 标记列表（const引用）
     */
    const QList<Marker>& markers() const { return m_markers; }

    /**
     * @brief 获取快照描述
     * @return 描述文本
     */
    QString description() const { return m_description; }

    // ========== Setters ==========
    /**
     * @brief 设置快照描述
     * @param description 新的描述文本
     */
    void setDescription(const QString& description) { m_description = description; }

    // ========== JSON 序列化 ==========
    /**
     * @brief 将快照数据转换为 JSON 对象
     * @return JSON 对象
     */
    QJsonObject toJson() const;

    /**
     * @brief 从 JSON 对象创建快照
     * @param json JSON 对象
     * @return 快照对象
     */
    static MapSnapshot fromJson(const QJsonObject& json);

    /**
     * @brief 生成唯一快照ID
     * @param timestamp 时间戳
     * @return 唯一ID字符串（格式: snap-YYYYMMDD-HHMMSS）
     */
    static QString generateId(const QDateTime& timestamp);

private:
    QString m_snapshotId;           ///< 唯一标识符
    QDateTime m_timestamp;          ///< 快照时间戳
    QList<Marker> m_markers;        ///< 该时刻的所有标记（完整数据）
    QString m_description;          ///< 快照描述（可选）
};

#endif // MAPSNAPSHOT_H
