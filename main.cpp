#include "mainwindow.h"
#include <QApplication>
// Debug
#include "jsonhelper.h"
#include <QDebug>
#include <vector>
#include "profile.h"

int main(int argc, char *argv[])
{
    std::vector<Profile> profiles;
    /*
    for (int i = 0; i < 6; i++)
    {
        profiles.push_back({ "Profile " + QString::number(i), ";", "<html></html>" });
    }
    JSONHelper::writeToJson("test.json", &profiles);
    */
    profiles.clear();
    JSONHelper::readFromJson("test.json", &profiles);
    for (Profile profile : profiles)
    {
        qDebug() << "Profile: " << profile.getName() << " " << profile.getSeperator() << " " << profile.getTemplateText() << "\n";

    }


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
