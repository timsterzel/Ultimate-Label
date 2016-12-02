#ifndef JSONHELPER_H
#define JSONHELPER_H
#include "profile.h"
#include <QString>
#include <vector>

class JSONHelper
{
public:
    JSONHelper();

    static bool writeToJson(QString fileName, std::vector<Profile> *profiles);
};

#endif // JSONHELPER_H
