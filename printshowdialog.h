#ifndef PRINTSHOWDIALOG_H
#define PRINTSHOWDIALOG_H

#include <QDialog>

namespace Ui {
class PrintShowDialog;
}

class PrintShowDialog : public QDialog
{
    Q_OBJECT

public:
    PrintShowDialog(QWidget *parent = 0, QString dataToShow = "");
    ~PrintShowDialog();

private slots:
    void on_pushButton_print_clicked();

    void on_pushButton_clicked();

private:
    Ui::PrintShowDialog *ui;
};

#endif // PRINTSHOWDIALOG_H
