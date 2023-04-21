/// This class will handle saving and loading user game stats.
/// Stats are local to each machine and will not be stored within the github repo.
/// The implimentation for logging in and signing up also exists within this class;
/// in addition there is a slot that is used to update user stats from gameplay.
/// Written By:

#include "userdatahandler.h"

/// \brief UserDataHandler::UserDataHandler
/// Constructor
/// Establishes a relative path to store local data and deserializes any data
/// that may already exist.
/// \param parent
UserDataHandler::UserDataHandler(QObject *parent)
    : QObject{parent}
{
    QString temp = QDir::currentPath();
    QDir relativePath(temp);
    USER_DATA_PATH = relativePath.filePath("localUserData.txt");

    deserializeJsonToUsersMap();
}

/// \brief UserDataHandler::serializeUserDataToJSON
/// Serializes the local user data to json and saves it in the localUserData.txt.
/// \param usersMap
void UserDataHandler::serializeUserDataToJSON()
{
    QJsonObject users; //one object with all the users

    int userNum = 0;
    for(auto user = usersData.begin(); user != usersData.end(); user++)
    {
        QJsonObject tempUser;

        QJsonArray tempArr; //stats
        for(int i = 0; i < 6; i++)
        {
            tempArr.append(user->second[i]);
        }

        tempUser["stats"] = tempArr;
        tempUser["username"] = user->first.first;
        tempUser["password"] = user->first.second;

        //each "user" in "users" is labeled with userNum.
        users[QString::number(userNum++)] = tempUser;
    }

    QJsonDocument doc(users);
    saveData(&doc);
}

/// \brief userDataHandler::saveData
/// Opens the file with filename and write to it and then close the file
/// in output cout not opening correctly error if filenmae doesnt work;
/// \param json
/// \param fileName
void UserDataHandler::saveData(QJsonDocument* doc)
{
    QFile file(USER_DATA_PATH);
    if (file.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        QString temp = doc->toJson();
        out << temp;
        file.close();
    }
    else
    {
        std::cout << "not opening correctly" << std::endl;
    }
}

/// \brief UserDataHandler::deserializeJsonToUsersMap
/// Deserializes the custom JSON for user data into a map.
void UserDataHandler::deserializeJsonToUsersMap()
{
    QFile file(USER_DATA_PATH);
    //read file in if it is readable
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString json = in.readAll(); // read text from file
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
        QJsonObject usersObject = doc.object();

        for(QJsonValueRef userRef : usersObject) //userRef is one user
        {
            //Extracting data from individual user
            QJsonObject user = userRef.toObject();
            QString username = user.value("username").toString();
            QString password = user.value("password").toString();
            QJsonArray stats = user.value("stats").toArray();

            std::array<int, 6> tempArray;
            for(int i = 0; i < 6; i++)
            {
                tempArray[i] = stats[i].toInt();
            }
            //add key value pair to the usersData map.
            usersData[std::make_pair(username, password)] = tempArray;
        }
    }
}

/// \brief UserDataHandler::signupCheck
/// Tries to sign up a new user.  If something goes wrong an appropriate emit will occur.
/// \param username
/// \param password
/// \param passwordCheck
void UserDataHandler::signupAttempt(QString username, QString password, QString passwordCheck)
{
    //Empty field
    if(username.length() == 0 || password.length() == 0 || passwordCheck.length() == 0)
    {
        emit signupFailNotAllFields();
    }
    //Password verification failed
    else if(password != passwordCheck)
    {
        emit signupFailPasswordMismatch();
    }
    //Space detected
    else if(username.contains(" ") || password.contains(" "))
    {
        emit signupFailSpacesDetected();
    }
    else
    {
        currentUser.first = username;
        currentUser.second = password;

        //The user exists
        auto iter = usersData.find(currentUser);
        if(iter != usersData.end())
        {
            emit signupFailUserExists();
        }
        //Successful Signup
        else
        {
            usersData[currentUser] = {0,0,0,0,0,0};
            serializeUserDataToJSON();
            emit signupSuccess();
        }
    }
}

/// \brief UserDataHandler::loginAttempt
/// Implimentation to see if a user log in attempt is successful.
/// It will tell the main window when it knows.
/// \param username
/// \param password
void UserDataHandler::loginAttempt(QString username, QString password)
{
    //Empty field
    if(username.length() == 0 || password.length() == 0)
    {
        emit loginFailedNotAllFields();
    }
    else
    {
        currentUser.first = username;
        currentUser.second = password;

        //The user does not exists
        auto iter = usersData.find(currentUser);
        if(iter == usersData.end())
        {
            emit loginFailedDNE();
        }
        //Successful Login
        else
        {
            emit loginSuccessful();
        }
    }
}

/// \brief UserDataHandler::statsRequest
void UserDataHandler::statsRequest()
{
    emit sendStats(usersData[currentUser]);
}

/// \brief UserDataHandler::firstGuessCorrect
void UserDataHandler::countryFinished(int finishPosition)
{
    std::cout<<finishPosition<<std::endl;
    usersData[currentUser][finishPosition]++;
    serializeUserDataToJSON();
}

