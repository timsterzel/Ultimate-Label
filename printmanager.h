#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

#include <QString>

class QTextDocument;
class QWidget;

class PrintManager
{
public:
    static bool print(QWidget *parent, QString windowTitle, QTextDocument *document,
                      bool customSize = false, int customWidth = 0,
                      int customHeight = 0);
};

#endif // PRINTMANAGER_H
