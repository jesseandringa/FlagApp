/// This class stores info about the user who is logged in and handles model side of gameplay.

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <cmath>
#include <string>

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
    int whereTheGamesEnded[6]; // index 0 would represent first guess correct... index 5 would be they didn't get it
    //These three below should be selected on startup of game, they are compared to for checking the users guess! not implemented fully:
    string country = "";
    float xCoordCountry;
    float yCoordCountry;
    int guessNumber;
    string guessedCountry;
    bool won;
    std::map<std::pair<string,string>, int[6]> userData;

public slots:
    void newGuessSlot(std::string guess);
    void signupAttempt(QString user, QString pass, QString passCheck);


signals:
    void sendUIGuessInfo(std::string guess, int guessNum, double distance);
    void signupFailNotAllFields();
    void signupFailUserExists();
    void signupFailPasswordMismatch();
    void signupSuccess();
};

#endif // GAMEMODEL_H
