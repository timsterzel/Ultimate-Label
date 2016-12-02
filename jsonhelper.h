#ifndef JSONHELPER_H
#define JSONHELPER_H
#include "profile.h"
#include <QString>
#include <vector>

class JSONHelper
{
private:
    // Identifier for Json objects
    static const QString JSON_PROFILES;
public:
    static const QString PROFILES_FILENAME;
public:

    JSONHelper();

    static bool writeToJson(QString fileName, std::vector<Profile> *profiles);
    static bool readFromJson(QString fileName, std::vector<Profile> *profiles);
};

#endif // JSONHELPER_H
