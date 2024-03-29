/// This class handles model side of gameplay.
/// /// Written By: name'); DROP TABLE teams;-- ?

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
#include <cctype>

using std::string;

class GameModel : public QObject
{
    Q_OBJECT
public:
    explicit GameModel(QObject *parent = nullptr);

private:
    const int allowedGuesses = 5;
    //These three below should be selected on startup of game, they are compared to for checking the users guess! not implemented fully:
    Country country;
    float xCoordCountry;
    float yCoordCountry;
    int guessNumber;
    int roundNumber;
    string guessedCountry;
    std::vector<Country> countries;
    bool won;
    std::vector<string> countriesNames;
    static string getArrowDirection(double xDirection, double yDirection);



public slots:
    void newGuessSlot(std::string guess);
    void newGameStartedSlot(int difficulty);
    void playNextCountry();
    void getSuggestionsForUserSlot(string currentText);
    void resetRound();


signals:
    void sendUIGuessInfo(std::string guess, int guessNum, double distance, std::vector<QString> hints, std::string arrowDir);
    void newCountryPicked(QString filepath, QString fact1);
    void sendWin(QString country);
    void sendLoss(QString country);
    void invalidGuess();
    void countryFinished(int finishPosition);
    void newSuggestions(std::vector<string> suggs);
    void backToMain();
    void sendFlagAnimation(QString flagfilepath, int event);

};

#endif // GAMEMODEL_H
