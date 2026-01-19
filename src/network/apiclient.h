#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

#include "../data/marker.h"
#include "../data/mapsnapshot.h"

/**
 * @class ApiClient
 * @brief 后端API通信客户端
 *
 * 负责与后端服务器进行HTTP通信：
 * - 同步标记数据
 * - 同步快照数据
 * - 发送添加/删除标记请求
 *
 * 设计为可扩展，后端API地址可配置。
 */
class ApiClient : public QObject {
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象
     */
    explicit ApiClient(QObject* parent = nullptr);

    /**
     * @brief 析构函数
     */
    ~ApiClient() override = default;

    // ========== 配置 ==========

    /**
     * @brief 设置后端API基础URL
     * @param baseUrl 基础URL（例如: "http://localhost:8080/api"）
     */
    void setBaseUrl(const QString& baseUrl);

    /**
     * @brief 获取当前基础URL
     * @return 基础URL字符串
     */
    QString baseUrl() const { return m_baseUrl; }

    /**
     * @brief 设置用户身份（用于权限验证）
     * @param username 用户名
     */
    void setUsername(const QString& username);

    // ========== API 调用 ==========

    /**
     * @brief 请求获取所有快照
     *
     * 请求成功后触发 snapshotsFetched 信号。
     */
    void fetchSnapshots();

    /**
     * @brief 请求添加新标记
     * @param marker 标记数据
     *
     * 请求成功后触发 markerAdded 信号。
     */
    void addMarker(const Marker& marker);

    /**
     * @brief 请求删除标记
     * @param markerId 标记ID
     *
     * 请求成功后触发 markerDeleted 信号。
     */
    void deleteMarker(const QString& markerId);

    /**
     * @brief 上传本地快照到服务器
     * @param snapshots 快照列表
     *
     * 用于同步本地数据到服务器。
     */
    void uploadSnapshots(const QList<MapSnapshot>& snapshots);

signals:
    /**
     * @brief 快照数据获取成功信号
     * @param snapshots 快照列表
     */
    void snapshotsFetched(const QList<MapSnapshot>& snapshots);

    /**
     * @brief 标记添加成功信号
     * @param marker 添加的标记
     */
    void markerAdded(const Marker& marker);

    /**
     * @brief 标记删除成功信号
     * @param markerId 被删除的标记ID
     */
    void markerDeleted(const QString& markerId);

    /**
     * @brief 网络错误信号
     * @param error 错误描述
     */
    void errorOccurred(const QString& error);

private slots:
    /**
     * @brief 处理网络响应
     * @param reply 网络回复对象
     */
    void onNetworkReply(QNetworkReply* reply);

private:
    /**
     * @brief 创建完整的API URL
     * @param endpoint API端点路径
     * @return 完整URL
     */
    QString buildUrl(const QString& endpoint) const;

private:
    QNetworkAccessManager* m_networkManager;  ///< 网络管理器
    QString m_baseUrl;                        ///< 后端API基础URL
    QString m_username;                       ///< 当前用户名
};

#endif // APICLIENT_H
