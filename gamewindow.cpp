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

    ui->winLabel->setVisible(false);
    ui->winLabel->setEnabled(false);
    ui->nextFlag->setVisible(false);
    ui->nextFlag->setEnabled(false);
    ui->newGame->setVisible(false);
    ui->newGame->setEnabled(false);

    //signal with string of guess connect to model
    connect(this, &GameWindow::newGuess, &model, &GameModel::newGuessSlot);
    connect(this, &GameWindow::newGame, &model, &GameModel::newGameStartedSlot);
    connect(&model, &GameModel::sendUIGuessInfo, this, &GameWindow::receiveCurrentGuessInfo);
    connect(&model, &GameModel::newCountryPicked, this, &GameWindow::setUIforNewCountry);

    //When player guesses correct, change ui to reflect win
    connect(&model, &GameModel::sendWin, this, &GameWindow::winScreen);
}

GameWindow::~GameWindow()
{
    delete ui;
}

///SLOT
/// resets ui when new game is created.. send signal to reset model
void GameWindow::initNewGame(int difficulty)
{
    ui->hintLabel1->setText("Hint 1:");
    ui->hintLabel2->setText("Hint 2:");
    ui->hintLabel3->setText("Hint 3:");
    ui->hintLabel4->setText("Hint 4:");
    ui->hintLabel5->setText("Hint 5:");
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
    ui->hintLabel1->setText("Hint 1: " + fact1);
}

void GameWindow::receiveCurrentGuessInfo(std::string guess, int guessNum, double distance, std::vector<QString> hints, std::string arrowDirection)
{
    //if distance == 0, maybe do something else? 0 meaning that the guess was not found in resource
    QString guessStr = QString::fromStdString(guess);
    QString distanceStr = QString::number(distance);
    QString arrowDir = QString::fromStdString(arrowDirection);
    if(guessNum == 0)
    {
        ui->hintLabel2->setText("Hint 2: " + hints[1]);
        ui->guessLine1->setText(guessStr);
        ui->distanceLine1->setText(distanceStr + " Miles");
    }
    else if(guessNum == 1)
    {
        ui->hintLabel3->setText("Hint 3: " + hints[2]);
        ui->guessLine2->setText(guessStr);
        ui->distanceLine2->setText(distanceStr + " Miles");
    }
    else if(guessNum == 2)
    {
        ui->hintLabel4->setText("Hint 4: " + hints[3]);
        ui->guessLine3->setText(guessStr);
        ui->distanceLine3->setText(distanceStr + " Miles");
    }
    else if(guessNum == 3)
    {
        ui->hintLabel5->setText("Hint 5: " + hints[4]);
        ui->guessLine4->setText(guessStr);
        ui->distanceLine4->setText(distanceStr + " Miles");
    }
    else if(guessNum == 4)
    {
        ui->guessLine5->setText(guessStr);
        ui->distanceLine5->setText(distanceStr + " Miles");
    }
}

void GameWindow::winScreen(){
    foreach (QWidget *widget, this->findChildren<QWidget *>()) {
        widget->setVisible(false);
    }
    ui->frame_2->setVisible(true);
    ui->frame_3->setVisible(true);
    ui->winLabel->setVisible(true);
    ui->winLabel->setEnabled(true);
    ui->horizontalFrame->setVisible(true);
    ui->horizontalFrame->setEnabled(true);
    ui->nextFlag->setVisible(true);
    ui->nextFlag->setEnabled(true);
    ui->newGame->setVisible(true);
    ui->newGame->setEnabled(true);

}

