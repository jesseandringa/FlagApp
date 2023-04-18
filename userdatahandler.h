/// This header represents a class that handles saving and loading user game stats.
/// Stats are local to each machine and will not be stored within the github repo.

#ifndef USERDATAHANDLER_H
#define USERDATAHANDLER_H

#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include<QIODevice>
#include <iostream>
#include <QString>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QDir>
#include <map>

using std::map;
using std::string;
using std::pair;
using std::array;

class UserDataHandler : public QObject
{
    Q_OBJECT
public:

    explicit UserDataHandler(QObject *parent = nullptr);

public slots:
    void signupAttempt(QString user, QString pass, QString passCheck);
    void loginAttempt(QString user, QString pass);
signals:
    void userMapDeserialized(map<pair<string,string>, array<int, 6>> usersData);

    void signupFailNotAllFields();
    void signupFailUserExists();
    void signupFailPasswordMismatch();
    void signupSuccess();

    void loginFailedNotAllFields();
    void loginFailedDNE();
    void loginSuccessful();

private:
    QString USER_DATA_PATH;
    std::pair<string,string> currentUser;
    std::map<std::pair<string,string>, std::array<int, 6>> usersData;

    void serializeUserDataToJSON();
    void saveData(QJsonDocument* doc);
    void deserializeJsonToUsersMap();
};

#endif // USERDATAHANDLER_H
