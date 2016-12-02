#ifndef PROFILESDIALOG_H
#define PROFILESDIALOG_H

#include <QDialog>

namespace Ui {
class ProfilesDialog;
}

class ProfilesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfilesDialog(QWidget *parent = 0);
    ~ProfilesDialog();

private:
    Ui::ProfilesDialog *ui;
};

#endif // PROFILESDIALOG_H
