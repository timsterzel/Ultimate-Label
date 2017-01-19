#include "mainwindow.h"
#include <QApplication>
#include "jsonhelper.h"
#include <QDebug>
#include <QTranslator>
#include "profile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    // load language file from resource
    translator.load(":/ultimatelabel_lang_" + QLocale::system().name());
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
