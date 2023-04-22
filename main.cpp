#include "mainwindow.h"
#include "gamewindow.h"
#include "studywindow.h"
#include "uiphysics.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameModel model;
    MainWindow w(model);
    GameWindow gameWindow(model);
    StudyWindow studyWindow;
    UIPhysics UIPhysics;
    w.show();
    return a.exec();
}
