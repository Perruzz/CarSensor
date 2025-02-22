#include "View/mainwindow.h"
#include <QApplication>
#include <QCursor>
#include <QPixmap>
#include <QSvgRenderer>
#include <QPainter>

QPixmap svgToPixmap(const QString& filePath, const QSize& size)
{
    QSvgRenderer svgRenderer(filePath);
    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    svgRenderer.render(&painter);
    return pixmap;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/Icons/app_icon.svg"));

    app.setStyleSheet("QWidget { background-color: #EBDED1; }");

    QPixmap cursorPixmap = svgToPixmap(":/Icons/car_key_cursor_icon.svg", QSize(32, 32));

    QCursor customCursor(cursorPixmap, 30, 0);

    app.setOverrideCursor(customCursor);

    View::MainWindow window;
    window.resize(1050, 750);
    window.show();

    return app.exec();
}
