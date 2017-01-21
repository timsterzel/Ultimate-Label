#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "manualdialog.h"
#include "profile.h"
#include <QMainWindow>
#include <QMap>
#include <QSettings>
#include <QString>
#include <memory>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSettings m_settings;
    QMap<QString,Profile> m_profiles;
    ManualDialog *m_manualDialog;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_open_triggered();

    void on_actionProfiles_triggered();

    void on_actionClear_triggered();

    void on_pushButton_print_clicked();

    // Own Slot, called when a item of the horizontal header was clicked
    void on_tableHorizontalHeaderClicked(int index);

    void on_actionSettings_triggered();

    void on_actionManual_triggered();

private:
    Ui::MainWindow *ui;

    void loadProfiles();
    void loadCSVFile(QString fileName);
};

#endif // MAINWINDOW_H
