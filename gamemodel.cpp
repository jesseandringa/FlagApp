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
    roundNumber(0),
    guessedCountry(""),
    won (false)
{
    countriesNames = Country::getAllCountryNames();
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

///
/// \brief GameModel::resetRound
/// Reset game model instance variables at the start of the round
void GameModel::resetRound()
{
    won = false;
    guessedCountry = "";
    guessNumber = 0;
}

///slot to start logic to see if guess is correct
/// also to see how far guess is off
/// also to see what direction etc.
/// tells view what hint to display next, or if won or lost game
void GameModel::newGuessSlot(std::string guess)
{
    if(Country::isInvalidGuess(guess)){
        emit invalidGuess();
        return;
    }
    double conversion = 69.09;
    double distance = 0;
    string arrowDirection = "";
    /*QString*/ /*direction*/;
    //Need QString to use .toLower();
    QString guessStr = QString::fromStdString(guess);
    if (guessStr.toLower() == country.name.toLower()){
        emit sendWin();
    }
    else
    {
        if(guessNumber < 5)
        {
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

            arrowDirection = GameModel::getArrowDirection(xDistance,yDistance);

            //Supposed conversion factor from polar coord distance to miles.
            distance = distance * conversion;




            //Lose case
            if (guessNumber == 4)
            {
                cout << "game over" << endl;
            }


            if (distance == 0){

            }
            emit sendUIGuessInfo(guess, guessNumber, distance, country.facts, arrowDirection);
            guessNumber++;
        }
    }
}

/// \brief GameModel::newGameStartedSlot
/// Begin the game by loading in the country data
/// \param difficulty
/// 0 - easy
/// 1 - medium
/// 2 - hard
void GameModel::newGameStartedSlot(int difficulty)
{
    countries = Country::loadCountries(difficulty);
    country = countries[roundNumber];
    emit newCountryPicked(country.flagFilename, country.facts[guessNumber]);
}

///
/// \brief GameModel::playNextCountry
/// Iterate the game to the next country
void GameModel::playNextCountry()
{
    resetRound();
    roundNumber++;
    country = countries[roundNumber];
    emit newCountryPicked(country.flagFilename, country.facts[guessNumber]);
}

void GameModel::getSuggestionsForUserSlot(string currentText)
{
    //do somethign
    std::vector<string> suggestions;
    for (auto name :countriesNames){
        for(unsigned int i = 0; i<currentText.length(); i++){
            //convert to lowercase
            char nameChar =tolower(name[i]);
            char guessChar =tolower(currentText[i]);

            if(nameChar == guessChar){
                //if last char of guess still matches add it to vector
                if(i == currentText.length()-1){
                    suggestions.push_back(name);
                }
            } //if one char doesn't match, dont add it to vector
            else{
                break;
            }
        }
    }
    //TODO: display these
    for (auto name : suggestions){
        cout<<name<<endl;
    }


}





