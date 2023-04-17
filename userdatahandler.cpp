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

        QString temp = "{";
        for(int i = 0; i < 5; i++)
        {
            temp += QString::number(user->second[i]);
            temp += ", ";
        }
        temp += QString::number(user->second[5]);
        temp += "}";
        tempUser["stats"] = temp;

        users[QString::number(userNum++)] = tempUser;
    }

    QJsonDocument doc(users);
    QString json = doc.toJson();
    QString path = ":/resources/localUserData/localUserData.txt";

    saveData(json, path);
}

/// \brief userDataHandler::saveData
/// Opens the file with filename and write to it and then close the file
/// in output cout not opening correctly error if filenmae doesnt work;
/// \param json
/// \param fileName
void UserDataHandler::saveData(const QString &json, QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        std::cout << "not opening correctly" << std::endl;
    }
    QTextStream out(&file);
    out << json;
    file.close();
}
