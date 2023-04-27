/// The country class stores the game data for a specific country.
/// The game data (country name, flag, and facts) are stored in the resourses folder.
/// A static method in this class can be used to make Country objects from the resource files
/// associated with the difficulty chosen at the start of the game.
/// Written By: name'); DROP TABLE teams;-- ?

#ifndef COUNTRY_H
#define COUNTRY_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>
#include <algorithm>
#include <random>
#include <vector>
#include <QTextStream>

using std::string;

class Country
{
public:
    QString name;
    QString flagFilename;
    std::vector<QString> facts;
    double longitude;
    double latitude;

    Country(QString name, QString flagFilename, std::vector<QString> facts);
    Country(QString name, double lon, double lat);
    Country();


    void shuffleFacts();

    static std::vector<Country> loadCountries(int difficulty);
    static void shuffleCountries(std::vector<Country>& countryVector);
    static Country loadCountryNameAndLocation(QString name);
    static bool isInvalidGuess(std::string guess);
    static std::vector<string> getAllCountryNames();
    static std::vector<Country> loadAllCountries();


};

#endif // COUNTRY_H
