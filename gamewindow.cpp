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

    ui->winLabel->setVisible(false);
    ui->winLabel->setEnabled(false);
    ui->nextFlag->setVisible(false);
    ui->nextFlag->setEnabled(false);



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


///\brief SLOT when user guesses country
/// sees if text is in it
///sends signal to model with text
void GameWindow::on_currentGuess_returnPressed()
{
    userGuessed();
}

void GameWindow::on_guessButton_clicked()
{
    userGuessed();
}

void GameWindow::userGuessed(){
    QString currentGuess ="";
    if(ui->currentGuess->text()!=""){
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
    ui->flagImageLabel->setPixmap(flag.scaled(ui->flagImageLabel->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));

    //set fact1
    ui->hintLabel1->setText("Hint 1: " + fact1);
    ui->scrollArea->setVisible(false);
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
        ui->arrowLabel1->setText(arrowDir);
    }
    else if(guessNum == 1)
    {
        ui->hintLabel3->setText("Hint 3: " + hints[2]);
        ui->guessLine2->setText(guessStr);
        ui->distanceLine2->setText(distanceStr + " Miles");
        ui->arrowLabel2->setText(arrowDir);
    }
    else if(guessNum == 2)
    {
        ui->hintLabel4->setText("Hint 4: " + hints[3]);
        ui->guessLine3->setText(guessStr);
        ui->distanceLine3->setText(distanceStr + " Miles");
        ui->arrowLabel3->setText(arrowDir);
    }
    else if(guessNum == 3)
    {
        ui->hintLabel5->setText("Hint 5: " + hints[4]);
        ui->guessLine4->setText(guessStr);
        ui->distanceLine4->setText(distanceStr + " Miles");
        ui->arrowLabel4->setText(arrowDir);
    }
    else if(guessNum == 4)
    {
        ui->guessLine5->setText(guessStr);
        ui->distanceLine5->setText(distanceStr + " Miles");
        ui->arrowLabel5->setText(arrowDir);
    }
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

/// \brief GameWindow::winScreen
/// Display a `you win` screen when the correct country is guessed.
void GameWindow::lossScreen(QString country)
{
    ui->winLabel->setText("You Lost!");
    ui->winLabel->setVisible(true);
    ui->nextFlag->setVisible(true);
    ui->nextFlag->setEnabled(true);
    ui->topLabel->setText(country);

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

    QRect sizeOfBox(369,169,481,scrollBoxHeight);
//    ui->suggList->setGeometry(sizeOfBox);
    ui->scrollArea->setGeometry(sizeOfBox);


}




void GameWindow::on_suggList_itemClicked(QListWidgetItem *item)
{
    QString countryName = item->text();
    ui->currentGuess->setText(countryName);
    ui->currentGuess->setFocus();
}

