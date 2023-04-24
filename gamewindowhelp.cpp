#include "gamewindowhelp.h"
#include "ui_gamewindowhelp.h"

GameWindowHelp::GameWindowHelp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindowHelp)
{
    ui->setupUi(this);

    connect(ui->backButton, &QPushButton::clicked, this, &GameWindowHelp::backButtonClicked);
    QPixmap feedbackImage(":/HelpWindowImages/HelpWindowImages/feedback.PNG");
    QPixmap guessImage(":/HelpWindowImages/HelpWindowImages/GuessArea.PNG");
    QPixmap hintImage(":/HelpWindowImages/HelpWindowImages/hintarea.PNG");
    ui->feedbackImage->setPixmap(feedbackImage.scaled(ui->feedbackImage->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->guessImage->setPixmap(guessImage.scaled(ui->guessImage->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->hintImage->setPixmap(hintImage.scaled(ui->hintImage->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

GameWindowHelp::~GameWindowHelp()
{
    delete ui;
}

void GameWindowHelp::backButtonClicked()
{
    emit returnToGame();
}
