# CLAUDE.md

此文件为 Claude Code (claude.ai/code) 提供项目指导信息。

## 项目概述

本项目是"NPU 虚拟校园地图 - 交互系统"——一个基于 Qt6 和 C++ 开发的桌面应用程序。

## 构建系统

本项目使用 CMake（最低版本 3.16）和 Qt6。

### 编译项目

在项目根目录下执行：

```bash
# 配置 CMake（输出到 build 目录）
cmake -B build

# 编译可执行文件
cmake --build build

# 输出文件位于：build/bin/LibraryMap.exe
```

或使用提供的 PowerShell 脚本：
```powershell
.\script\build.ps1
```

### 运行应用程序

```bash
.\build\bin\LibraryMap.exe
```

## 架构设计

- **构建系统**：CMake + Qt6 (已启用 automoc)
- **框架**：Qt6 Widgets
- **入口点**：`main.cpp` - 创建 QApplication 并启动事件循环
- **项目名称**：LibraryMap（定义在 CMakeLists.txt 中）

## 项目结构

```
project01/
├── CMakeLists.txt              # CMake 构建配置
├── main.cpp                    # 应用程序入口
├── mainwindow.h / .cpp         # 主窗口
│
├── src/data/                   # 数据结构层
│   ├── marker.h / .cpp         # 标记数据（位置、备注、颜色、时间）
│   └── mapsnapshot.h / .cpp    # 历史快照数据（完整标记列表）
│
├── src/widgets/                # UI 组件层
│   ├── mapview.h / .cpp        # 地图显示组件（缩放、拖拽、标记渲染）
│   └── timelinewidget.h / .cpp # 时间轴控制组件
│
├── src/core/                   # 业务逻辑层
│   └── markermanager.h / .cpp  # 标记和快照管理器
│
├── src/network/                # 网络通信层
│   └── apiclient.h / .cpp      # RESTful API 客户端
│
├── build/                      # 编译输出目录（已忽略）
├── script/                     # 构建脚本
└── .vscode/                    # VSCode 配置（已忽略）
```

## 核心功能

### 1. 地图交互（MapView）
- 基于 QGraphicsView 实现
- 支持鼠标拖拽平移
- 支持滚轮缩放
- 归一化坐标系统（0.0-1.0）适配不同分辨率

### 2. 标记管理（Marker + MarkerManager）
- 标记包含：位置、备注、颜色、创建时间、创建者
- 支持添加/删除标记
- 删除标记会自动创建新快照
- 管理员权限验证（防止恶意标记）

### 3. 时间回溯（MapSnapshot + TimelineWidget）
- 每次标记变更自动创建快照
- 快照保存完整的标记列表
- 通过时间轴滑块回溯到任意历史时间点
- 类似 Git 的版本控制机制

### 4. 网络同步（ApiClient）
- RESTful API 通信
- 与后端服务器同步快照数据
- 支持添加/删除标记的远程操作

## Qt 配置

项目已通过 `CMAKE_AUTOMOC` 自动启用 Qt 的元对象编译器（MOC）。添加带 Q_OBJECT 宏的新 Qt 类时，CMake 会自动处理 MOC 处理。

## API 接口规范

后端需要实现的 RESTful API：

| 端点 | 方法 | 说明 | 请求体 |
|------|------|------|--------|
| `/api/map/snapshots` | GET | 获取所有历史快照 | - |
| `/api/map/markers` | POST | 创建新标记 | `{"x": 0.5, "y": 0.3, "note": "备注", "color": "#FF0000"}` |
| `/api/map/markers/{id}` | DELETE | 删除指定标记 | - |

响应格式示例：
```json
{
  "snapshotId": "snap-20250119-103000-123",
  "timestamp": "2025-01-19T10:30:00Z",
  "description": "添加标记: 图书馆",
  "markers": [
    {
      "id": "marker-123",
      "x": 0.5,
      "y": 0.3,
      "note": "图书馆",
      "color": "#FF5733",
      "createTime": "2025-01-19T10:30:00Z",
      "createdBy": "用户A"
    }
  ]
}
```

## 开发注意事项

1. **添加新文件时**：CMakeLists.txt 使用 `file(GLOB_RECURSE SOURCES ...)` 自动收集所有 .cpp/.h/.ui 文件，无需手动添加
2. **Doxygen 注释**：所有公共 API 都有详细的 Doxygen 风格注释
3. **中文显示**：确保源文件使用 UTF-8 编码
4. **地图图片**：默认使用占位符，需要通过 `MapView::setMapPixmap()` 设置实际地图
