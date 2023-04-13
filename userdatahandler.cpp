/// This class will handle saving and loading user game stats.
/// Stats are local to each machine and will not be stored within the github repo.

#include "userdatahandler.h"
#include <vector>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <iostream>


userDataHandler::userDataHandler()
{

}
