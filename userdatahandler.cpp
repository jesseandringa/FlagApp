/// This class will handle saving and loading user game stats.
/// Stats are local to each machine and will not be stored within the github repo.

#include "userdatahandler.h"

UserDataHandler::UserDataHandler(QObject *parent)
    : QObject{parent}, totalGames(0), totalWinPercentage(0),losePercentage(0)
{
    for (int i = 0; i<5; i++){
        winPercentagePerGuess[i] = 0;
    }
}

