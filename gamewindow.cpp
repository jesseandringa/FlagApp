#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    //don't call this normally here..
    //just here to see it in action
    //also set all these to false. true is just to see what it could look like
    ui->arrowLabel1->setVisible(true);
    ui->arrowLabel2->setVisible(false);
    ui->arrowLabel3->setVisible(false);
    ui->arrowLabel4->setVisible(false);
    ui->arrowLabel5->setVisible(false);

    ui->distanceLine1->setVisible(true);
    ui->distanceLine2->setVisible(false);
    ui->distanceLine3->setVisible(false);
    ui->distanceLine4->setVisible(false);
    ui->distanceLine5->setVisible(false);

    //Would probably go off the difficulty of the game to select from a certain file, and rand1-12 for which flag is being quizzed (Sean)
    QPixmap image(":/flags/FlagImagesHard/liechtenstein.jpg");
    ui->flagImageLabel->setPixmap(image.scaled(ui->flagImageLabel->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));

}

GameWindow::~GameWindow()
{
    delete ui;
}

///SLOT
/// resets ui when new game is created
void GameWindow::initNewGame()
{
    ui->arrowLabel1->setVisible(false);
    ui->arrowLabel2->setVisible(false);
    ui->arrowLabel3->setVisible(false);
    ui->arrowLabel4->setVisible(false);
    ui->arrowLabel5->setVisible(false);

    ui->distanceLine1->setVisible(false);
    ui->distanceLine2->setVisible(false);
    ui->distanceLine3->setVisible(false);
    ui->distanceLine4->setVisible(false);
    ui->distanceLine5->setVisible(false);

}


