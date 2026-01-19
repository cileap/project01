#include "mapsnapshot.h"

MapSnapshot::MapSnapshot(const QDateTime& timestamp,
                         const QList<Marker>& markers,
                         const QString& description)
    : m_snapshotId(generateId(timestamp))
    , m_timestamp(timestamp)
    , m_markers(markers)
    , m_description(description)
{
}

QString MapSnapshot::generateId(const QDateTime& timestamp) {
    // 使用时间戳生成唯一ID，格式: snap-YYYYMMDD-HHMMSS-mmm
    return QString("snap-%1")
        .arg(timestamp.toString("yyyyMMdd-HHmmss-zzz"));
}

QJsonObject MapSnapshot::toJson() const {
    QJsonObject obj;
    obj["snapshotId"] = m_snapshotId;
    obj["timestamp"] = m_timestamp.toString(Qt::ISODate);
    obj["description"] = m_description;

    // 序列化标记列表
    QJsonArray markersArray;
    for (const Marker& marker : m_markers) {
        markersArray.append(marker.toJson());
    }
    obj["markers"] = markersArray;

    return obj;
}

MapSnapshot MapSnapshot::fromJson(const QJsonObject& json) {
    MapSnapshot snapshot;
    snapshot.m_snapshotId = json["snapshotId"].toString();
    snapshot.m_timestamp = QDateTime::fromString(json["timestamp"].toString(), Qt::ISODate);
    snapshot.m_description = json["description"].toString();

    // 反序列化标记列表
    QJsonArray markersArray = json["markers"].toArray();
    for (const QJsonValue& value : markersArray) {
        snapshot.m_markers.append(Marker::fromJson(value.toObject()));
    }

    return snapshot;
}
