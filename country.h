
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


    void shuffleFacts();

    static std::vector<Country> loadCountries(int difficulty);
    static void shuffleCountries(std::vector<Country>& countryVector);
    static Country loadCountryNameAndLocation(QString name);
};

#endif // COUNTRY_H
