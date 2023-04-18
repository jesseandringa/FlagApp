/// This class stores info about the user who is logged in and handles model side of gameplay.

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <cmath>
#include <string>
#include <map>
#include "country.h"

using std::string;

class GameModel : public QObject
{
    Q_OBJECT
public:
    explicit GameModel(QObject *parent = nullptr);

private:
    const int allowedGuesses = 5;
    int gamesPlayed;  // total games this user has played
    //These three below should be selected on startup of game, they are compared to for checking the users guess! not implemented fully:
    Country country;
    float xCoordCountry;
    float yCoordCountry;
    int guessNumber;
    string guessedCountry;
    std::vector<Country> countries;
    bool won;

public slots:
    void newGuessSlot(std::string guess);
    void newGameStartedSlot(int difficulty);


signals:
    void sendUIGuessInfo(std::string guess, int guessNum, double distance);
    void newCountryPicked(QString filepath, QString fact1);
};

#endif // GAMEMODEL_H
