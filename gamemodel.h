/// This class stores info about the user who is logged in and handles model side of gameplay.

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QString>


class GameModel
{
public:
    GameModel();

private:
    QString username;
    int gamesPlayed;  // total games this user has played
    int whereTheGamesEnded[6]; // index 0 would represent first guess correct... index 5 would be they didn't get it
};

#endif // GAMEMODEL_H
