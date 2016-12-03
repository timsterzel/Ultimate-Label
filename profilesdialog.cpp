#include "profilesdialog.h"
#include "ui_profilesdialog.h"
#include "jsonhelper.h"

ProfilesDialog::ProfilesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfilesDialog)
{
    ui->setupUi(this);

    setOptionsEnabled(false);

    // Load profiles
    JSONHelper::readFromJson(JSONHelper::PROFILES_FILENAME, &m_profiles);
    for (Profile profile : m_profiles)
    {
        ui->listWidget_profiles->addItem(profile.getName());
    }
    // Select first row
    if (m_profiles.size() > 0)
    {
        ui->listWidget_profiles->setCurrentRow(0);
        //setOptionsEnabled(true);
    }
    //ui->listWidget_profiles
    // listWidget_profiles
}

ProfilesDialog::~ProfilesDialog()
{
    delete ui;
}

void ProfilesDialog::setOptionsEnabled(bool enabled)
{
    for (int i = 0; i < ui->verticalLayout_options->count(); i++)
    {
        QWidget *widget = ui->verticalLayout_options->itemAt(i)->widget();
        widget->setEnabled(enabled);
    }
}

void ProfilesDialog::clearOptionFields()
{
    ui->lineEdit_name->setText("");
    ui->lineEdit_separator->setText("");
    ui->plainTextEdit_template->setPlainText("");
}

void ProfilesDialog::on_listWidget_profiles_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    setOptionsEnabled(m_profiles.size() > 0);
    // Show data of selected profile is there is one selected
    if (m_profiles.size() > 0)
    {
        QString key = current->text();
        const Profile &profile = m_profiles.value(key);
        ui->lineEdit_name->setText(profile.getName());
        ui->lineEdit_separator->setText(profile.getSeperator());
        ui->plainTextEdit_template->setPlainText(profile.getTemplateText());
    }
    else
    {
        // Nothing to show in option fields
        clearOptionFields();
    }
}

// Delete selected
void ProfilesDialog::on_pushButton_delete_clicked()
{
    // Only delete if there is something selected
    if (ui->listWidget_profiles->selectedItems().count() > 0)
    {
        QString key = ui->listWidget_profiles->currentItem()->text();
        // Remove from container
        m_profiles.remove(key);
        int selected = ui->listWidget_profiles->currentRow();
        // Remove from list
        ui->listWidget_profiles->takeItem(selected);
    }
}
