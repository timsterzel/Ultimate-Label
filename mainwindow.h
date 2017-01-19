#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "profile.h"
#include <QMainWindow>
#include <QMap>
#include <QString>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMap<QString,Profile> m_profiles;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_ffnen_triggered();

    void on_actionProfiles_triggered();

    void on_actionClear_triggered();

    void on_pushButton_print_clicked();

    // Own Slot, called when a item of the horizontal header was clicked
    void on_tableHorizontalHeaderClicked(int index);



    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;

    void loadProfiles();
    void loadCSVFile(QString fileName);
};

#endif // MAINWINDOW_H
