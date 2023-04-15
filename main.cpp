#include "mainwindow.h"
#include "gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameModel model;
    MainWindow w(model);
    GameWindow gameWindow(model);
    w.show();
    return a.exec();
}
