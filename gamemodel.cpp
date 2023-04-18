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

///slot to start logic to see if guess is correct
/// also to see how far guess is off
/// also to see what direction etc.
/// tells view what hint to display next, or if won or lost game
void GameModel::newGuessSlot(std::string guess)
{
    double distance = 0;
    QString direction;
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

        double xDistance = guessedCountry.longitude - country.longitude;
        double yDistance = guessedCountry.latitude - country.latitude;
        //Want to think about this somemore, and how we want to do our directions, prob set boundries on what we qualify as southwest vs south or west.
        //i.e. if the difference between y<10polar points then maybe just call it west instead of southwest.
        if (xDistance > 0){
            //left
        }
        else if (xDistance <= 0){
            //right
        }
        if(yDistance > 0){
            //down
        }
        else if (yDistance <= 0){
            //up
        }
        //Supposed conversion factor from polar coord distance to miles.
        distance = distance * 69.09;



        //Lose case
        if (guessNumber == 4){
            cout << "game over" << endl;
        }
    }
    //will also pass in direction string when implemented
    emit sendUIGuessInfo(guess, guessNumber, distance);
    guessNumber++;
}

/// \brief signupCheck
/// Tries to sign up a new user.  If something goes wrong an appropriate emit will occur.
/// \param username
/// \param password
/// \param passwordCheck
void GameModel::signupAttempt(QString user, QString pass, QString passCheck)
{
    string username = user.toStdString();
    string password = pass.toStdString();
    string passwordCheck = passCheck.toStdString();

    if(username.length() == 0 || password.length() == 0 || passwordCheck.length() == 0)
    {
        emit signupFailNotAllFields();
    }
    else if(password != passwordCheck)
    {
        emit signupFailPasswordMismatch();
    }
    else
    {
        currentUser.first = username;
        currentUser.second = password;

        auto iter = usersData.find(currentUser);
        //The user exists
        if(iter != usersData.end())
        {
            emit signupFailUserExists();
        }
        else
        {
            usersData[currentUser] = {0,0,0,0,0,0};
            emit signupSuccess();
        }
    }
}

/// \brief GameModel::loginAttempt
/// Implimentation to see if a user log in attempt is successful.
/// It will tell the main window when it knows.
/// \param user
/// \param pass
void GameModel::loginAttempt(QString user, QString pass)
{
    if(user.length() == 0 || pass.length() == 0)
    {
        emit loginFailedNotAllFields();
    }
    else
    {
        currentUser.first = user.toStdString();
        currentUser.second = pass.toStdString();

        auto iter = usersData.find(currentUser);
        //The user does not exists
        if(iter == usersData.end())
        {
            emit loginFailedDNE();
        }
        else
        {
            emit loginSuccessful();
        }
    }
}

void GameModel::newGameStartedSlot(int difficulty)
{
    countries = Country::loadCountries(difficulty);
    country = countries[0];
    emit newCountryPicked(country.flagFilename, country.facts[0]);
}





