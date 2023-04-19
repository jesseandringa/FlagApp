/// This class stores info about the user who is logged in and handles model side of gameplay.

#include "gamemodel.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;

GameModel::GameModel(QObject *parent)
    : QObject{parent},
      gamesPlayed(0),
      country(),
      guessNumber(0),
      guessedCountry(""),
      won (false)
{
}

string GameModel::getArrowDirection(double xDistance, double yDistance)
{
    string xDir = "";
    string yDir = "";
    int ratio = 2;
    string arrowDir = "";

    //what directions is the correct country
    if(xDistance > 0){
        xDir = "west";
    }
    else{
        xDir = "east";
    }
    if(yDistance > 0){
        yDir = "south";
    }
    else{
        yDir = "north";
    }

    //is the ration great enough to have a "southwest" etc or is it just "south"
    if(abs(xDistance) >= abs(yDistance)){
            //if ratio isn't met
        if(abs(xDistance/ratio) > abs(yDistance)){
            arrowDir = xDir;
        }
        else{
            arrowDir = yDir + xDir;
        }
    }
    else{
        if(abs(yDistance/ratio) > abs(xDistance)){
            arrowDir = yDir;
        }
        else{
            arrowDir = yDir + xDir;
        }
    }

    return arrowDir;
}

///slot to start logic to see if guess is correct
/// also to see how far guess is off
/// also to see what direction etc.
/// tells view what hint to display next, or if won or lost game
void GameModel::newGuessSlot(std::string guess)
{
    double conversion = 69.09;
    double distance = 0;
    /*QString*/ /*direction*/;
    //Need QString to use .toLower();
    QString guessStr = QString::fromStdString(guess);
//    QString countryStr = QString::fromStdString(country);
    if (guessStr.toLower() == country.name.toLower()){
        //win

    }
    else {

        Country guessedCountry = Country::loadCountryNameAndLocation(guessStr);
        //if current country hasn't gotten x,y coords yet
        if(country.longitude == 0 && country.latitude == 0){
            Country temp = Country::loadCountryNameAndLocation(country.name);
            country.longitude = temp.longitude;
            country.latitude = temp.latitude;
        }
        distance = std::sqrt(std::pow((guessedCountry.longitude - country.longitude), 2) + std::pow((guessedCountry.latitude - country.latitude), 2));

        double xDistance = (guessedCountry.longitude - country.longitude)*conversion;
        double yDistance = (guessedCountry.latitude - country.latitude)*conversion;
        //Want to think about this somemore, and how we want to do our directions, prob set boundries on what we qualify as southwest vs south or west.
        //i.e. if the difference between y<10polar points then maybe just call it west instead of southwest.

        string arrowDirection = GameModel::getArrowDirection(xDistance,yDistance);

        //Supposed conversion factor from polar coord distance to miles.
        distance = distance * conversion;




        //Lose case
        if (guessNumber == 4){
            cout << "game over" << endl;
        }
    }
    //will also pass in direction string when implemented
    emit sendUIGuessInfo(guess, guessNumber, distance);
    guessNumber++;
}

void GameModel::newGameStartedSlot(int difficulty)
{
    countries = Country::loadCountries(difficulty);
    country = countries[0];
    emit newCountryPicked(country.flagFilename, country.facts[0]);
}





