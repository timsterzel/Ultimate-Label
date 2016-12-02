#include "mainwindow.h"
#include <QApplication>
// Debug
#include "jsonhelper.h"
#include <vector>
#include "profile.h"

int main(int argc, char *argv[])
{
    std::vector<Profile> profiles;
    for (int i = 0; i < 6; i++)
    {
        profiles.push_back({ "Profile " + QString::number(i), ";", "<html></html>" });
    }
    JSONHelper::writeToJson("test.json", &profiles);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
