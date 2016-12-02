#ifndef PROFILESDIALOG_H
#define PROFILESDIALOG_H
#include "profile.h"
#include <QDialog>
#include <vector>


namespace Ui {
class ProfilesDialog;
}

class ProfilesDialog : public QDialog
{
    Q_OBJECT
private:
       std::vector<Profile> m_profiles;
public:
    explicit ProfilesDialog(QWidget *parent = 0);
    ~ProfilesDialog();

private:
    Ui::ProfilesDialog *ui;
};

#endif // PROFILESDIALOG_H
