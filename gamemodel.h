/// This class stores info about the user who is logged in and handles model side of gameplay.

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <string>

using std::string;

class GameModel : public QObject
{
    Q_OBJECT
public:
    explicit GameModel(QObject *parent = nullptr);

private:
    const int allowedGuesses = 5;
    QString username;
    int gamesPlayed;  // total games this user has played
    int whereTheGamesEnded[6]; // index 0 would represent first guess correct... index 5 would be they didn't get it
    string country;
    int guessNumber;
    string guessedCountry;
    bool won;
public slots:
    void newGuessSlot(string);


signals:

};

#endif // GAMEMODEL_H
