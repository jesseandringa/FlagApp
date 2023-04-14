#include "gamewindow.h"
#include "gamemodel.h"
#include "ui_gamewindow.h"

#include <iostream>
using std::cout;
using std::endl;

//default constructor ------not sure if we need this
GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{ui->setupUi(this);}


GameWindow::GameWindow(GameModel &model,QWidget *parent) :
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

    //signal with string of guess connect to model
    connect(this, &GameWindow::newGuess, &model, &GameModel::newGuessSlot);
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


///\brief SLOT when user guesses country
/// sees if text is in it
///sends signal to model with text
///
void GameWindow::on_currentGuess_returnPressed()
{

    QString currentGuess ="";
    if(ui->currentGuess->text()!=""){
        cout<<"hit reutrn"<<endl;
        currentGuess = ui->currentGuess->text();
        string guessStr = currentGuess.toStdString();
        ui->currentGuess->setText("");
        ui->currentGuess->setPlaceholderText("");
        emit newGuess(guessStr);
    }

}


void GameWindow::on_guessButton_clicked()
{
    QString currentGuess ="";
    if(ui->currentGuess->text()!=""){
        cout<<"hit guess button"<<endl;
        currentGuess = ui->currentGuess->text();
        string guessStr = currentGuess.toStdString();
        ui->currentGuess->setText("");
        ui->currentGuess->setPlaceholderText("");
        emit newGuess(guessStr);
    }
}

