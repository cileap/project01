#ifndef MARKER_H
#define MARKER_H

#include <QPointF>
#include <QString>
#include <QColor>
#include <QDateTime>
#include <QJsonObject>

/**
 * @class Marker
 * @brief 地图标记点数据结构
 *
 * 表示地图上的一个标记点，包含位置、备注、颜色和时间信息。
 * 坐标使用归一化坐标系统（0.0 - 1.0），便于适配不同分辨率的地图图片。
 */
class Marker {
public:
    /**
     * @brief 默认构造函数
     */
    Marker() = default;

    /**
     * @brief 完整构造函数
     * @param position 标记在地图上的归一化坐标 (0.0-1.0)
     * @param note 标记备注信息
     * @param color 标记显示颜色
     * @param createTime 标记创建时间，默认为当前时间
     * @param createdBy 标记创建者（可选）
     */
    Marker(const QPointF& position,
           const QString& note,
           const QColor& color,
           const QDateTime& createTime = QDateTime::currentDateTime(),
           const QString& createdBy = QString());

    // ========== Getters ==========
    /**
     * @brief 获取标记的唯一标识符
     * @return 标记ID字符串
     */
    QString id() const { return m_id; }

    /**
     * @brief 获取标记位置（归一化坐标）
     * @return 归一化坐标点 (x: 0.0-1.0, y: 0.0-1.0)
     */
    QPointF position() const { return m_position; }

    /**
     * @brief 获取备注信息
     * @return 备注文本
     */
    QString note() const { return m_note; }

    /**
     * @brief 获取标记颜色
     * @return 颜色对象
     */
    QColor color() const { return m_color; }

    /**
     * @brief 获取创建时间
     * @return 创建时间
     */
    QDateTime createTime() const { return m_createTime; }

    /**
     * @brief 获取创建者
     * @return 创建者名称
     */
    QString createdBy() const { return m_createdBy; }

    // ========== Setters ==========
    /**
     * @brief 设置标记位置
     * @param position 新的归一化坐标位置
     */
    void setPosition(const QPointF& position) { m_position = position; }

    /**
     * @brief 设置备注信息
     * @param note 新的备注文本
     */
    void setNote(const QString& note) { m_note = note; }

    /**
     * @brief 设置标记颜色
     * @param color 新的颜色
     */
    void setColor(const QColor& color) { m_color = color; }

    // ========== JSON 序列化 ==========
    /**
     * @brief 将标记数据转换为 JSON 对象
     * @return JSON 对象
     */
    QJsonObject toJson() const;

    /**
     * @brief 从 JSON 对象创建标记
     * @param json JSON 对象
     * @return 标记对象
     */
    static Marker fromJson(const QJsonObject& json);

    /**
     * @brief 生成唯一标记ID
     * @return 唯一ID字符串（格式: marker-时间戳-随机数）
     */
    static QString generateId();

private:
    QString m_id;              ///< 唯一标识符
    QPointF m_position;        ///< 归一化坐标 (0.0-1.0)
    QString m_note;            ///< 备注信息
    QColor m_color;            ///< 标记颜色
    QDateTime m_createTime;    ///< 创建时间
    QString m_createdBy;       ///< 创建者
};

#endif // MARKER_H
