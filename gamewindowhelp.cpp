#include "gamewindowhelp.h"
#include "ui_gamewindowhelp.h"

GameWindowHelp::GameWindowHelp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindowHelp)
{
    ui->setupUi(this);
}

GameWindowHelp::~GameWindowHelp()
{
    delete ui;
}
