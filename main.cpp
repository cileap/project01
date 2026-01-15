#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Widget main_window;
    main_window.setWindowTitle("Library Map");
    main_window.resize(800, 500);
    main_window.show();

    return app.exec();
}