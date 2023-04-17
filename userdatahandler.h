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

signals:

private:
    void serializeUserDataToJSON(map<pair<string,string>, array<int, 6>> usersMap);
    void saveData(const QString &json, QString fileName);
};

#endif // USERDATAHANDLER_H
