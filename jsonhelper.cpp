#include "jsonhelper.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

JSONHelper::JSONHelper()
{

}

bool JSONHelper::writeToJson(QString fileName, std::vector<Profile> *profiles)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Error by opening Json file \n";
        return false;
    }
    QJsonArray profilesArray;
    for (Profile& profile : *profiles)
    {
        QJsonObject profileObject;
        profile.writeToJson(profileObject);
        profilesArray.append(profileObject);
    }
    QJsonObject root;
    root.insert("profiles", profilesArray);
    QJsonDocument saveDoc(root);
    file.write(saveDoc.toJson());
    return true;
}
