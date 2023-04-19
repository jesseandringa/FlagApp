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
#include <cstdlib>

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
    int roundNumber;
    string guessedCountry;
    std::vector<Country> countries;
    bool won;
    static string getArrowDirection(double xDirection, double yDirection);
    void resetRound();


public slots:
    void newGuessSlot(std::string guess);
    void newGameStartedSlot(int difficulty);
    void playNextCountry();


signals:
    void sendUIGuessInfo(std::string guess, int guessNum, double distance, std::vector<QString> hints);
    void newCountryPicked(QString filepath, QString fact1);
    void sendWin();
};

#endif // GAMEMODEL_H
