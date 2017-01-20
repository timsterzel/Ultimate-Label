#ifndef PROFILESDIALOG_H
#define PROFILESDIALOG_H
#include "profile.h"
#include <QDialog>
#include <QListWidgetItem>
#include <QMap>
#include <QString>


namespace Ui {
class ProfilesDialog;
}

class ProfilesDialog : public QDialog
{
    Q_OBJECT
private:
       Ui::ProfilesDialog *ui;
       QMap<QString,Profile> m_profiles;
public:
    explicit ProfilesDialog(QWidget *parent = 0);
    ~ProfilesDialog();

private slots:
       void on_listWidget_profiles_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

       void on_pushButton_delete_clicked();

       void on_pushButton_new_clicked();

       void on_lineEdit_name_editingFinished();

       void on_lineEdit_separator_editingFinished();

       void on_checkBox_containsHeader_stateChanged(int arg1);

       void on_plainTextEdit_template_textChanged();

       void on_buttonBox_accepted();       

private:
    // Set all option widgets to enabled or not enabled
    void setOptionsEnabled(bool enabled);
    // Clear all fields of options so there are empty
    void clearOptionFields();
    // Change the overgiven name so that its unique
    QString findUniqueName(QString name) const;


};

#endif // PROFILESDIALOG_H
