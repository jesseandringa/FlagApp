/// This class stores info about the user who is logged in and handles model side of gameplay.

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <string>
using std::string;


class GameModel
{
public:
    GameModel();
    string country;
    int guessNumber;
    string guessedCountry;

};

#endif // GAMEMODEL_H
