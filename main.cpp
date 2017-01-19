#include "mainwindow.h"
#include <QApplication>
#include "jsonhelper.h"
#include <QDebug>
#include <QTranslator>
#include "profile.h"

#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    // load language file from resource
    translator.load(":/ultimatelabel_lang_" + QLocale::system().name());
    a.installTranslator(&translator);
    /*
    QSettings settings("test.ini", QSettings::IniFormat);
    settings.setValue("Test", 3);
    */

    MainWindow w;
    w.show();

    return a.exec();
}
