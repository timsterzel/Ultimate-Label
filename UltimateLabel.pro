#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T12:05:55
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UltimateLabel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    profilesdialog.cpp \
    jsonhelper.cpp \
    profile.cpp \
    printshowdialog.cpp \
    settingsdialog.cpp \
    manualdialog.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    profilesdialog.h \
    jsonhelper.h \
    profile.h \
    printshowdialog.h \
    settingsdialog.h \
    settings.h \
    manualdialog.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    profilesdialog.ui \
    printshowdialog.ui \
    settingsdialog.ui \
    manualdialog.ui \
    aboutdialog.ui
# Add Console for debugging purposes
CONFIG += console

TRANSLATIONS = ultimatelabel_lang_de.ts

RESOURCES = languages.qrc \
    general.qrc
