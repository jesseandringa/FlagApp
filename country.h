
#ifndef COUNTRY_H
#define COUNTRY_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>
#include <vector>

class Country
{
public:
    QString name;
    QString flagFilename;
    std::vector<QString> facts;

    Country(QString name, std::vector<QString> facts);
    static std::vector<Country> loadCountries(int difficulty);
};

#endif // COUNTRY_H
