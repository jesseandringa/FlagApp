/// This class will handle saving and loading user game stats.
/// Stats are local to each machine and will not be stored within the github repo.

#include "userdatahandler.h"

UserDataHandler::UserDataHandler(QObject *parent)
    : QObject{parent}
{
}

/// \brief UserDataHandler::serializeUserDataToJSON
/// Serializes the local user data to json and saves it in the localUserData.txt in resources.
/// \param usersMap
void UserDataHandler::serializeUserDataToJSON(map<pair<string,string>, array<int, 6>> usersMap)
{
    QJsonObject users;

    int userNum = 0;
    for(auto user = usersMap.begin(); user != usersMap.end(); user++)
    {
        QJsonObject tempUser;
        tempUser["username"] = QString::fromStdString(user->first.first);
        tempUser["password"] = QString::fromStdString(user->first.second);

        //QString temp = "{";
        QJsonArray tempArr;
        for(int i = 0; i < 6; i++)
        {
            tempArr.append(user->second[i]);
            //temp += QString::number(user->second[i]);
            //temp += ", ";
        }
        //temp += QString::number(user->second[5]);
        //temp += "}";
        tempUser["stats"] = tempArr;

        users[QString::number(userNum++)] = tempUser;
    }

    QJsonDocument doc(users);
    QString json = doc.toJson();

    saveData(json);
}

/// \brief userDataHandler::saveData
/// Opens the file with filename and write to it and then close the file
/// in output cout not opening correctly error if filenmae doesnt work;
/// \param json
/// \param fileName
void UserDataHandler::saveData(const QString &json)
{
    QFile file(USER_DATA_PATH);
    if (!file.open(QIODevice::WriteOnly))
    {
        std::cout << "not opening correctly" << std::endl;
    }
    QTextStream out(&file);
    out << json;
    file.close();
}

void UserDataHandler::deserializeJsonToUsersMap()
{
    map<pair<string,string>, array<int, 6>> temp;

    QFile file(USER_DATA_PATH);
    //read file in if it is readable
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString json = in.readAll(); // read text from file
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
        QJsonObject usersObject = doc.object();

        for(QJsonValueRef userRef : usersObject)
        {
            QJsonObject user = userRef.toObject();
            QString username = user.value("username").toString();
            QString password = user.value("password").toString();
            QJsonArray stats = user.value("stats").toArray();

            std::array<int, 6> tempArray;
            for(int i = 0; i < 6; i++)
            {
                tempArray[i] = stats[i].toInt();
            }
            temp[std::make_pair(username.toStdString(), password.toStdString())] = tempArray;
        }
    }

    emit userMapDeserialized(temp);
}
