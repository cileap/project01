#include <QApplication>
#include "mainwindow.h"

/**
 * @brief 程序入口点
 *
 * 初始化Qt应用并显示主窗口。
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 设置应用信息
    app.setApplicationName("NPU Virtual Campus Map");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("NPU");

    // 创建并显示主窗口
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
