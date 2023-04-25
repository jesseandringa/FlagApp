#include "gamewindow.h"
#include "gamemodel.h"
#include "ui_gamewindow.h"

#include <iostream>
using std::cout;
using std::endl;

GameWindow::GameWindow(GameModel &model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    ui->currentGuess->setFocus();

    //Only visible at the end of a round
    ui->winLabel->setVisible(false);
    ui->winLabel->setEnabled(false);
    ui->nextFlag->setVisible(false);
    ui->nextFlag->setEnabled(false);
    ui->flagAnimation->setVisible(false);
    ui->guessButton->setStyleSheet("QPushButton {background-color: rgb(50,200,50);} "
                                   "QPushButton:pressed {background-color: rgb(150,255,150);}");


    //signal with string of guess connect to model
    connect(this, &GameWindow::newGuess, &model, &GameModel::newGuessSlot);
    connect(this, &GameWindow::newGame, &model, &GameModel::newGameStartedSlot);
    connect(&model, &GameModel::sendUIGuessInfo, this, &GameWindow::receiveCurrentGuessInfo);
    connect(&model, &GameModel::newCountryPicked, this, &GameWindow::setUIforNewCountry);

    //When player guesses correct, change ui to reflect win
    connect(&model, &GameModel::sendWin, this, &GameWindow::winScreen);
    connect(&model, &GameModel::sendLoss, this, &GameWindow::lossScreen);

    // Start new round after winning (Sam)
    connect(this, &GameWindow::nextCountry, &model, &GameModel::playNextCountry);

    //connect for typing and guesses
    connect(&model, &GameModel::invalidGuess, this, &GameWindow::invalidGuessSlot);
    connect(this, &GameWindow::userTypingAndNeedsSuggestions, &model, &GameModel::getSuggestionsForUserSlot);
    connect(&model, &GameModel::newSuggestions, this, &GameWindow::addSuggestions);

    connect(ui->homeButton, &QPushButton::clicked, this, &GameWindow::backToHomeSlot);

    connect(&model, &GameModel::sendFlagAnimation, this, &GameWindow::receiveFlagAnimation);

    //shake timer when incorrect guess
    connect(&shakeTimer, &QTimer::timeout, this, &GameWindow::shakeGuessBox);
    //connect(this, &GameWindow::sendPixmapForAnimation, &UIPhysics, UIPhysics::receivePixMap);

    //connect to help window
    connect(ui->helpButton, &QPushButton::clicked, this, &GameWindow::openHelpWindow);

    //connect from help back to game
    connect(&gameWindowHelp, &GameWindowHelp::returnToGame, this, &GameWindow::openGameWindow);

    //reset game after going home
    connect(this, &GameWindow::resetGame, &model, &GameModel::resetRound);
    connect(this, &GameWindow::resetGame, this, &GameWindow::clearHintsAndGuesses);

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

/// \brief GameWindow::makeWidgetsVisibleAndEnabled
/// Recursively make all widgets in the game window visible and enabled.
/// \param widget
void GameWindow::makeWidgetsVisibleAndEnabled(QWidget *widget)
{
    // Set visibility and enable state for widget
    widget->setVisible(true);
    widget->setEnabled(true);

    // Recursively iterate through child widgets and set visibility and enable state
    const QObjectList &children = widget->children();
    for (QObject *child : children) {
        QWidget *childWidget = qobject_cast<QWidget *>(child);
        if (childWidget) {
            makeWidgetsVisibleAndEnabled(childWidget);
        }
    }
}


/// \brief GameWindow::on_currentGuess_returnPressed
void GameWindow::on_currentGuess_returnPressed()
{
    userGuessed();
}

/// \brief GameWindow::on_guessButton_clicked
void GameWindow::on_guessButton_clicked()
{
    userGuessed();
}

/// \brief GameWindow::userGuessed
/// Emits valid input to the model for handling.
/// Valid input is concidered to be text in currentGuess.
void GameWindow::userGuessed()
{
    QString currentGuess ="";
    if(ui->currentGuess->text()!="")
    {
        currentGuess = ui->currentGuess->text();
        string guessStr = currentGuess.toStdString();
        ui->currentGuess->setText("");
        emit newGuess(guessStr);
    }
}

/// \brief GameWindow::clearHintsAndGuesses
/// Empty the hints and guess history from the previous round.
void GameWindow::clearHintsAndGuesses()
{
    // Clear guess history
    ui->guessLine1->clear();
    ui->guessLine2->clear();
    ui->guessLine3->clear();
    ui->guessLine4->clear();
    ui->guessLine5->clear();
    ui->distanceLine1->clear();
    ui->distanceLine2->clear();
    ui->distanceLine3->clear();
    ui->distanceLine4->clear();
    ui->distanceLine5->clear();
    ui->arrowLabel1->setText("<-");
    ui->arrowLabel2->setText("<-");
    ui->arrowLabel3->setText("<-");
    ui->arrowLabel4->setText("<-");
    ui->arrowLabel5->setText("<-");

    // Clear all hints
    ui->hintLabel1->clear();
    ui->hintLabel2->setText("Hint 2: ");
    ui->hintLabel3->setText("Hint 3: ");
    ui->hintLabel4->setText("Hint 4: ");
    ui->hintLabel5->setText("Hint 5: ");
}

/// \brief GameWindow::setUIforNewCountry
/// Load the ui with the country flag and first hint
/// \param filepath
/// filepath to the country flag image being loaded to the ui
/// \param fact1
/// The first fact displayed as hint 1
void GameWindow::setUIforNewCountry(QString filepath, QString fact1)
{
    //set flag
    QPixmap flag(filepath);
    //emit sendPixmapForAnimation(flag);
    ui->flagImageLabel->setPixmap(flag.scaled(ui->flagImageLabel->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));

    //set fact1
    ui->hintLabel1->setText("Hint 1: " + fact1);
    ui->scrollArea->setVisible(false);
    //reset animation
    ui->flagAnimation->timer.stop();
    ui->flagAnimation->set();
}

void GameWindow::receiveCurrentGuessInfo(std::string guess, int guessNum, double distance, std::vector<QString> hints, std::string arrowDirection)
{
    //if distance == 0, maybe do something else? 0 meaning that the guess was not found in resource
    QString guessStr = QString::fromStdString(guess);
    QString distanceStr = QString::number(distance);

    //calculate roation of arrow and size of pixmap
    int angle = getRotationAngle(arrowDirection);
    QTransform rotationAngle;
    rotationAngle.rotate(angle);
    ui->currentGuess->setPlaceholderText("Guess A Country");
    int scale = 32;
    if(angle % 90== 0 ) scale = 24;
    QPixmap arrow(":/new/prefix1/arrowImage.png");
    arrow = arrow.transformed(rotationAngle);

    if(guessNum == 0)
    {
        ui->hintLabel2->setText("Hint 2: " + hints[1]);
        ui->guessLine1->setText(guessStr);
        ui->distanceLine1->setText(distanceStr + " Miles");
        ui->arrowLabel1->setPixmap(arrow.scaled(scale,scale, Qt::KeepAspectRatio,Qt::SmoothTransformation)); ///ui->arrowLabel1->size()
    }
    else if(guessNum == 1)
    {
        ui->hintLabel3->setText("Hint 3: " + hints[2]);
        ui->guessLine2->setText(guessStr);
        ui->distanceLine2->setText(distanceStr + " Miles");
        ui->arrowLabel2->setPixmap(arrow.scaled(scale,scale, Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
    else if(guessNum == 2)
    {
        ui->hintLabel4->setText("Hint 4: " + hints[3]);
        ui->guessLine3->setText(guessStr);
        ui->distanceLine3->setText(distanceStr + " Miles");
        ui->arrowLabel3->setPixmap(arrow.scaled(scale,scale, Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
    else if(guessNum == 3)
    {
        ui->hintLabel5->setText("Hint 5: " + hints[4]);
        ui->guessLine4->setText(guessStr);
        ui->distanceLine4->setText(distanceStr + " Miles");
        ui->arrowLabel4->setPixmap(arrow.scaled(scale,scale, Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
    else if(guessNum == 4)
    {
        ui->guessLine5->setText(guessStr);
        ui->distanceLine5->setText(distanceStr + " Miles");
        ui->arrowLabel5->setPixmap(arrow.scaled(scale,scale, Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
}

///\brief returns angle to rotate pixmap to point in the right direction of the country to guess
///\param string direction. "east" "southwest" etc.
int GameWindow::getRotationAngle(std::string dir){

    int angle = 0;
    if(dir =="north"){
        angle = 0;
    }
    else if(dir == "northwest"){
        angle = 45;
    }
    else if(dir == "west"){
        angle = 90;
    }
    else if(dir == "southwest"){
        angle = 135;
    }
    else if(dir == "south"){
        angle = 180;
    }
    else if(dir == "southeast"){
        angle = 225;
    }
    else if(dir == "east"){
        angle = 270;
    }
    else{ //northeast
        angle = 315;
    }

    return angle;
}

/// \brief GameWindow::winScreen
/// Display a `you win` screen when the correct country is guessed.
void GameWindow::winScreen(QString country)
{
    ui->winLabel->setVisible(true);
    ui->nextFlag->setVisible(true);
    ui->nextFlag->setEnabled(true);
    ui->topLabel->setText(country);

    ui->guessButton->setEnabled(false);
    ui->currentGuess->setEnabled(false);
}

/// \brief GameWindow::lossScreen
/// Display a `you lose` screen when the wrong country is guessed.
void GameWindow::lossScreen(QString country)
{
    ui->winLabel->setText("You Lost!");
    ui->winLabel->setVisible(true);
    ui->nextFlag->setVisible(true);
    ui->nextFlag->setEnabled(true);
    ui->topLabel->setText("Country: " + country);

    ui->guessButton->setEnabled(false);
    ui->currentGuess->setEnabled(false);

}

/// \brief GameWindow::on_nextFlag_clicked
/// Start the game again with the next flag.
void GameWindow::on_nextFlag_clicked()
{
    hideWinScreen();
    clearHintsAndGuesses();
    emit nextCountry();
}

///\brief when guess is not a country don't count guess and shake box?
void GameWindow::invalidGuessSlot()
{
    ////shake the text box because invalid country guess
    ui->currentGuess->setPlaceholderText("Invalid Guess!");
    left = false;
    shakeCount = 0;

    shakeTimer.start(50);
}

void GameWindow::shakeGuessBox(){
    if(shakeCount>=5){
        shakeTimer.stop();
        ui->currentGuess->setGeometry(340,500,481,21);
        shakeCount = 0;
        left = false;
    }
    else{
        if(left){ //if box on left
            ui->currentGuess->setGeometry(343,500,481,21);
            left = false;
        }
        else{
            ui->currentGuess->setGeometry(337,500,481,21);
            left = true;
        }
        shakeCount++;
    }

}

/// \brief GameWindow::hideWinScreen
/// Hide visibility of the win screen and make the game window visible again.
void GameWindow::hideWinScreen()
{
    ui->winLabel->setText("You Win!");
    ui->winLabel->setVisible(false);
    ui->nextFlag->setVisible(false);
    ui->nextFlag->setEnabled(false);
    ui->topLabel->setText("Guess the country!");

    ui->guessButton->setEnabled(true);
    ui->currentGuess->setEnabled(true);
    ui->currentGuess->setFocus();

    ui->flagImageLabel->setVisible(true);
    ui->flagAnimation->setVisible(false);
}


///\brief When user is typing. look at current string and give user suggestions
void GameWindow::on_currentGuess_textChanged(const QString &arg1)
{
    string input = arg1.QString::toStdString();
    emit userTypingAndNeedsSuggestions(input);


}

void GameWindow::addSuggestions(std::vector<string> suggestions)
{
    ui->scrollArea->setVisible(true);
    ui->suggList->clear();
    //put new suggestions in
    for(int i = 0; i<suggestions.size(); i++){
        QString suggestionStr = QString::fromStdString(suggestions[i]);
        QListWidgetItem *suggItem = new QListWidgetItem(suggestionStr);
        ui->suggList->addItem(suggItem);
    }

    //set height for scroll area
    int sugCount = 0;
    if(ui->suggList->count() > 3){
        sugCount = 3;
    }
    else{
        sugCount = ui->suggList->count();
    }
    int scrollBoxHeight = sugCount * 19;

    QRect sizeOfBox(340,518,481,scrollBoxHeight);
    //    ui->suggList->setGeometry(sizeOfBox);
    ui->scrollArea->setGeometry(sizeOfBox);


}

void GameWindow::on_suggList_itemClicked(QListWidgetItem *item)
{
    QString countryName = item->text();
    ui->currentGuess->setText(countryName);
    ui->currentGuess->setFocus();
}

/// \brief GameWindow::backToHomeSlot
/// Translates a button click to an emit.
void GameWindow::backToHomeSlot()
{
    emit resetGame();
    emit backToHome();
}

void GameWindow::receiveFlagAnimation(QString filepath, int event){
    QImage image(filepath);
    QImage re = image.scaledToHeight(ui->flagImageLabel->height());
    re = re.scaledToWidth(ui->flagImageLabel->width());
    ui->flagAnimation->image = re;
    ui->flagAnimation->count = 10;
    ui->flagAnimation->event = event;

    ui->flagImageLabel->setVisible(false);
    ui->flagAnimation->setVisible(true);
    ui->flagAnimation->timer.start(10);


}

void GameWindow::openHelpWindow()
{
    gameWindowHelp.show();
    this->close();
}

void GameWindow::openGameWindow()
{
    this->show();
    gameWindowHelp.close();
}
