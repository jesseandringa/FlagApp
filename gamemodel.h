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
    std::pair<string,string> currentUser;
    int gamesPlayed;  // total games this user has played
    //These three below should be selected on startup of game, they are compared to for checking the users guess! not implemented fully:
    Country country;
    float xCoordCountry;
    float yCoordCountry;
    int guessNumber;
    string guessedCountry;
    std::vector<Country> countries;
    bool won;
    std::map<std::pair<string,string>, std::array<int, 6>> usersData;

public slots:
    void newGuessSlot(std::string guess);
    void signupAttempt(QString user, QString pass, QString passCheck);
    void loginAttempt(QString user, QString pass);
    void newGameStartedSlot(int difficulty);


signals:
    void sendUIGuessInfo(std::string guess, int guessNum, double distance);
    void signupFailNotAllFields();
    void signupFailUserExists();
    void signupFailPasswordMismatch();
    void signupSuccess();
    void loginFailedNotAllFields();
    void loginFailedDNE();
    void loginSuccessful();
};

#endif // GAMEMODEL_H
