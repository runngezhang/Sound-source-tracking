#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //screen splash display
    QPixmap pixmap(":/new/prefix1/resources/screen.png");
    QSplashScreen screen(pixmap);
    screen.show();

    //show main window
    MainWindow w;
    w.show();
    return a.exec();
}
