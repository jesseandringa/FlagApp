/// This class stores info about the user who is logged in and handles model side of gameplay.

#include "gamemodel.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;

GameModel::GameModel(QObject *parent)
    : QObject{parent},
      gamesPlayed(0),
      country(""),
      guessNumber(0),
      guessedCountry(""),
      won (false)
{
    for(int i = 0; i< allowedGuesses + 1; i++){
        whereTheGamesEnded[i] = 0;
    }

    usersData[std::make_pair("user", "pass")] = {0,0,0,0,0,0};
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
    QString countryStr = QString::fromStdString(country);
    if (guessStr.toLower() == countryStr.toLower()){
        //win

    }
    else {
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

                double xDistance = xCoordinateGuess - xCoordCountry;
                double yDistance = yCoordinateGuess - yCoordCountry;
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

            }
        }
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








