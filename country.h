
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

using std::string;

class Country
{
public:
    QString name;
    QString flagFilename;
    std::vector<QString> facts;

    Country(QString name, QString flagFilename, std::vector<QString> facts);
    void shuffleFacts();
    static std::vector<Country> loadCountries(int difficulty);
    static void shuffleCountries(std::vector<Country>& countryVector);
};

#endif // COUNTRY_H
