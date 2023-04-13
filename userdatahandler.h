/// This header represents a class that handles saving and loading user game stats.
/// Stats are local to each machine and will not be stored within the github repo.

#ifndef USERDATAHANDLER_H
#define USERDATAHANDLER_H

#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <iostream>
#include <QString>
#include <QObject>

class UserDataHandler : public QObject
{
    Q_OBJECT
public:
    explicit UserDataHandler(QObject *parent = nullptr);

signals:

};

#endif // USERDATAHANDLER_H
