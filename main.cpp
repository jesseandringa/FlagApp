#include "mainwindow.h"
#include "gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    GameWindow gameWindow;
    gameWindow.show();
    return a.exec();
}
