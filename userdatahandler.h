/// This header represents a class that handles saving and loading user game stats.
/// Stats are local to each machine and will not be stored within the github repo.
/// This class also handles logic for signing up as a user and logging in as a user.
/// Written By: name'); DROP TABLE teams;-- ?

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
using std::pair;
using std::array;

class UserDataHandler : public QObject
{
    Q_OBJECT
public:

    explicit UserDataHandler(QObject *parent = nullptr);

public slots:
    void signupAttempt(QString username, QString password, QString passwordCheck);
    void loginAttempt(QString user, QString pass);

    void statsRequest();

    void countryFinished(int finishPosition);

signals:
    void userMapDeserialized(map<pair<QString,QString>, array<int, 6>> usersData);

    void signupFailNotAllFields();
    void signupFailUserExists();
    void signupFailPasswordMismatch();
    void signupFailSpacesDetected();
    void signupSuccess();

    void loginFailedNotAllFields();
    void loginFailedDNE();
    void loginSuccessful();

    void sendStats(array<int, 6>);

private:
    QString USER_DATA_PATH;
    std::pair<QString,QString> currentUser;
    std::map<std::pair<QString,QString>, std::array<int, 6>> usersData;

    void serializeUserDataToJSON();
    void saveData(QJsonDocument* doc);
    void deserializeJsonToUsersMap();

};

#endif // USERDATAHANDLER_H
