/// The country class stores the game data for a specific country.
/// The game data (country name, flag, and facts) are stored in the resourses folder.
/// A static method in this class can be used to make Country objects from the resource files
/// associated with the difficulty chosen at the start of the game.
/// Written By: name'); DROP TABLE teams;-- ?

#include "country.h"

/// \brief Country::Country
/// Constructor for a Country object
/// \param name
/// Name of the country
/// \param flagFilename
/// File path to the countries flag image
/// \param facts
/// Vector of five facts about the country
Country::Country(QString name, QString flagFilename, std::vector<QString> facts) :
    name(name),
    flagFilename(flagFilename),
    facts(facts),
    longitude(0),
    latitude(0)
{
    shuffleFacts();
}

/// \brief Country::Country
/// Constructor to load about coordinates from each country
/// \param name of country
/// \param longitude
/// \param latitude
Country::Country(QString name, double lon, double lat):
    name(name),
    flagFilename(""),
    longitude(lon),
    latitude(lat)
{

}

/// \brief Country::Country
/// Default constructor.
Country::Country():
    name(""),
    flagFilename(""),
    facts(),
    longitude(0),
    latitude(0)
{

}

/// \brief Country::shuffleFacts
/// Shuffles the ordering of the countries facts vector
void Country::shuffleFacts()
{
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(facts.begin(), facts.end(), rng);
}

/// \brief Country::loadAllCountries
/// Loads all the countrys names, flag file, and facts from a JSON.
/// \return
/// A vector of Country objects
std::vector<Country> Country::loadAllCountries()
{
   QString filename = ":/facts/easy_facts.json";
    QString flagFilenamePrefix = ":/flags/FlagImages/";
    std::vector<Country> countryVector;
    int totalFiles = 3;

    while (totalFiles != 0){

        if (totalFiles == 2){
            filename = ":/facts/medium_facts.json";
            flagFilenamePrefix = ":/flags/FlagImagesMedium/";
        }

        if (totalFiles == 1){
            filename = ":/facts/hard_facts.json";
            flagFilenamePrefix = ":/flags/FlagImagesHard/";
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
        totalFiles--;
    }
    return countryVector;
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

///\brief searches .csv file for country name to get long and lat data
/// \param : name of country to find
/// \returns Country with name and long and lat data.
Country Country::loadCountryNameAndLocation(QString name)
{
    QString filename = ":/distanceData/country_latitude_and_longitude.csv";
    bool exists = false;
    // Parse the chosen csv
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    std::vector<QString> fileData;
    QTextStream in(&file);
    QString line = "";

    //find country in  file
    while(!in.atEnd()){
        line = in.readLine();
        QList countryData = line.split(",");
        int x = QString::compare(countryData[3],name, Qt::CaseInsensitive);
        if(x == 0){
            exists = true;
            break;
        }
    }
    file.close();
    //parse countries data and return it
    QList countryData = line.split(",");
    double longi = countryData[2].toDouble();
    double lat = countryData[1].toDouble();
    Country country(name,longi,lat);

    //return country if found
    if(exists){
        return country;
    }
    //return empty country if not found
    else{
        Country noCountry("",0,0);
        return noCountry;
    }

}

/// \brief Country::isInvalidGuess
/// \param guess
/// \return
/// True if the user entered any text, false if empty guess
bool Country::isInvalidGuess(string guess)
{
    QString quessStr = QString::fromStdString(guess);
    Country blankCountry = loadCountryNameAndLocation(quessStr);

    //if the country has name
    if(blankCountry.name.length() > 0){
        return false;
    }
    else{
        return true;
    }
}

/// \brief Country::getAllCountryNames
/// Reads the country names from a JSON file and stores them in a vector.
/// \return
/// Vector of country names.
std::vector<string> Country::getAllCountryNames()
{
    QString filename = ":/distanceData/country_latitude_and_longitude.csv";
    std::vector<string> countries;
    // Parse the chosen csv
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    std::vector<QString> fileData;
    QTextStream in(&file);
    QString line = "";

    //find country in  file
    while(!in.atEnd()){
        line = in.readLine();
        QList countryData = line.split(",");
        string countryName = countryData[3].toStdString();
        if (countryName != "country"){
            countries.push_back(countryName);
        }

    }
    file.close();

    return countries;
}
