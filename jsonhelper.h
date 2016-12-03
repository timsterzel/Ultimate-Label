#ifndef JSONHELPER_H
#define JSONHELPER_H
#include "profile.h"
#include <QString>
#include <QMap>

class JSONHelper
{
private:
    // Identifier for Json objects
    static const QString JSON_PROFILES;
public:
    static const QString PROFILES_FILENAME;
public:

    JSONHelper();

    static bool writeToJson(QString fileName, QMap<QString, Profile> *profiles);
    static bool readFromJson(QString fileName, QMap<QString, Profile> *profiles);
};

#endif // JSONHELPER_H
