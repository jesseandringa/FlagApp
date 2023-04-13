/// The country class stores the game data for a specific country.
/// The game data (country name, flag, and facts) are stored in the resourses folder.
/// A static method in this class can be used to make Country objects from the resource files
/// associated with the difficulty chosen at the start of the game.

#include "country.h"

Country::Country(QString name, QString flagFilename, std::vector<QString> facts) :
    name(name),
    flagFilename(flagFilename),
    facts(facts)
{
    shuffleFacts();
}

/// \brief Country::shuffleFacts
/// Shuffles the ordering of the countries facts vector
void Country::shuffleFacts()
{
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(facts.begin(), facts.end(), rng);
}

/// \brief Country::loadCountries
/// Static method used to read Country objects from the fact .json files.
/// \param difficulty
/// Game difficulty:
///     0 = easy
///     1 = medium
///     2 = hard
/// \return
/// A vector of Country objects
std::vector<Country> Country::loadCountries(int difficulty)
{
    // Select the fact filename associated with the chosen difficulty
    QString filename;
    QString flagFilenamePrefix;
    switch (difficulty) {
    case 0:
        filename = ":/facts/easy_facts.json";
        flagFilenamePrefix = ":/flags/FlagImages/";
        break;
    case 1:
        filename = ":/facts/medium_facts.json";
        flagFilenamePrefix = ":/flags/FlagImagesMedium/";
        break;
    case 2:
        filename = ":/facts/hard_facts.json";
        flagFilenamePrefix = ":/flags/FlagImagesHard/";
        break;
    }

    // Parse the chosen json
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonData = file.readAll();
    file.close();

    // Parse JSON data
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonObject obj = doc.object();

    // Iterate over countries and facts
    std::vector<Country> countryVector;
    for (const QString& countryName : obj.keys()) {
        QJsonObject countryObj = obj.value(countryName).toObject();
        QJsonValue factsVal = countryObj.value("facts");

        // Convert QJsonArray to std::vector<QString>
        QJsonArray factsArray = factsVal.toArray();
        std::vector<QString> factsVector;
        for (int i = 0; i < factsArray.size(); i++) {
            QJsonValue factVal = factsArray.at(i);
            if (factVal.isString()) {
                QString fact = factVal.toString();
                factsVector.push_back(fact);
            }
        }

        // Create country object with parsed data
        QString flagFilename = flagFilenamePrefix + countryName + ".jpg";
        Country country(countryName, flagFilename, factsVector);
        countryVector.push_back(country);
    }
    shuffleCountries(countryVector);
    return countryVector;
}

/// \brief Country::shuffleCountries
/// Static function used to shuffle a vector of countries
/// \param countryVector
/// std vector of Countries passed by reference
void Country::shuffleCountries(std::vector<Country> &countryVector)
{
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(countryVector.begin(), countryVector.end(), rng);
}
