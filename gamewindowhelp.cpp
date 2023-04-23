#include "gamewindowhelp.h"
#include "ui_gamewindowhelp.h"

GameWindowHelp::GameWindowHelp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindowHelp)
{
    ui->setupUi(this);

    connect(ui->backButton, &QPushButton::clicked, this, &GameWindowHelp::backButtonClicked);
}

GameWindowHelp::~GameWindowHelp()
{
    delete ui;
}

void GameWindowHelp::backButtonClicked()
{
    emit returnToGame();
}
