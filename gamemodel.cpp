/// This class stores info about the user who is logged in and handles model side of gameplay.

#include "gamemodel.h"
#include <iostream>
using std::cout;
using std::endl;

GameModel::GameModel(QObject *parent)
    : QObject{parent},
    username(""),
    gamesPlayed(0),
    country(""),
    guessNumber(0),
    guessedCountry(""),
    won (false)
{
    for(int i = 0; i< allowedGuesses + 1; i++){
        whereTheGamesEnded[i] = 0;
    }
}

///slot to start logic to see if guess is correct
/// also to see how far guess is off
/// also to see what direction etc.
/// tells view what hint to display next, or if won or lost game
void GameModel::newGuessSlot(string)
{
    cout<<"not implemented"<<endl;
}
