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
void GameModel::newGuessSlot(std::string guess)
{
    double distance = 0;
    //Need QString to use .toLower();
    QString guessStr = QString::fromStdString(guess);
    QString countryStr = QString::fromStdString(country);
    if (guessStr.toLower() == countryStr.toLower()){
        //win
    } else {
        //Below is reading from file to see if they were wrong, what country they might have guessed and how far:
        QFile file(":/distanceData/country_latitude_and_longitude.csv");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            //Convert guess to same type, so can use tolower not sure if this is ideal..
            QByteArray guessArray(guess.c_str(), guess.length());

            if(line.toLower().contains(guessArray.toLower())){

                QStringList fields = QString(line).split(",");
                float xCoordinateGuess = fields[1].toFloat();
                float yCoordinateGuess = fields[2].toFloat();
                distance = std::sqrt(std::pow((xCoordinateGuess - xCoordCountry), 2) + std::pow((yCoordinateGuess - yCoordCountry), 2));
                //Supposed conversion factor from polar coord distance to miles.
                distance = distance * 69.09;

            }
        }
    }

    emit sendUIGuessNumAndStr(guess, guessNumber, distance);
    guessNumber++;
}
