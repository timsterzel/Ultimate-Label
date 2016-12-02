#ifndef JSONHELPER_H
#define JSONHELPER_H
#include <QString>
#include <vector>

class JSONHelper
{
public:
    JSONHelper();

    static void writeAsJson(QString fileName);
};

#endif // JSONHELPER_H
