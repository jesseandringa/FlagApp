#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    //Would probably go off the difficulty of the game to select from a certain file, and rand1-12 for which flag is being quizzed (Sean)
    ui->distanceLine1->setReadOnly(true);
    ui->distanceLine2->setReadOnly(true);
    ui->distanceLine3->setReadOnly(true);
    ui->distanceLine4->setReadOnly(true);
    ui->distanceLine5->setReadOnly(true);
    ui->guessLine1->setReadOnly(true);
    ui->guessLine2->setReadOnly(true);
    ui->guessLine3->setReadOnly(true);
    ui->guessLine4->setReadOnly(true);
    ui->guessLine5->setReadOnly(true);


    QPixmap image(":/flags/FlagImagesHard/liechtenstein.jpg");
    ui->flagImageLabel->setPixmap(image.scaled(ui->flagImageLabel->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));

}

GameWindow::~GameWindow()
{
    delete ui;
}

///SLOT
/// resets ui when new game is created
void GameWindow::initNewGame(int difficulty)
{

    // load countries
    countries = Country::loadCountries(difficulty);

}


