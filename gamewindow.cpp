#include "gamewindow.h"
#include "gamemodel.h"
#include "ui_gamewindow.h"

#include <iostream>
using std::cout;
using std::endl;

//default constructor ------not sure if we need this
//GameWindow::GameWindow(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::GameWindow)
//{ui->setupUi(this);}


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
    connect(this, &GameWindow::newGame, &model, &GameModel::newGameStartedSlot);
    connect(&model, &GameModel::sendUIGuessInfo, this, &GameWindow::receiveCurrentGuessInfo);
    connect(&model, &GameModel::newCountryPicked, this, &GameWindow::setUIforNewCountry);
}

GameWindow::~GameWindow()
{
    delete ui;
}

///SLOT
/// resets ui when new game is created.. send signal to reset model
void GameWindow::initNewGame(int difficulty)
{
    ui->hintLabel1->setText("");
    ui->hintLabel2->setText("");
    ui->hintLabel3->setText("");
    ui->hintLabel4->setText("");
    ui->hintLabel5->setText("");
    emit newGame(difficulty);
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
        emit newGuess(guessStr);
    }
}

void GameWindow::setUIforNewCountry(QString filepath, QString fact1)
{
    //set flag
    QPixmap flag(filepath);
    ui->flagImageLabel->setPixmap(flag.scaled(ui->flagImageLabel->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));

    //set fact1
    ui->hintLabel1->setText(fact1);
}

void GameWindow::receiveCurrentGuessInfo(std::string guess, int guessNum, double distance){
    //if distance == 0, maybe do something else? 0 meaning that the guess was not found in resource
    QString guessStr = QString::fromStdString(guess);
    QString distanceStr = QString::number(distance);
    if(guessNum == 0){
        ui->guessLine1->setText(guessStr);
        ui->distanceLine1->setText(distanceStr + " Miles");
    }
    else if(guessNum == 1){
         ui->guessLine2->setText(guessStr);
         ui->distanceLine2->setText(distanceStr + " Miles");
    }
    else if(guessNum == 2){
         ui->guessLine3->setText(guessStr);
         ui->distanceLine3->setText(distanceStr + " Miles");
    }
    else if(guessNum == 3){
         ui->guessLine4->setText(guessStr);
         ui->distanceLine4->setText(distanceStr + " Miles");
    }
    else if(guessNum == 4){
         ui->guessLine5->setText(guessStr);
         ui->distanceLine5->setText(distanceStr + " Miles");
    }
}

