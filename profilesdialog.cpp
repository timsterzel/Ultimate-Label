#include "profilesdialog.h"
#include "ui_profilesdialog.h"
#include "jsonhelper.h"
#include <QDebug>

ProfilesDialog::ProfilesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfilesDialog)
{
    ui->setupUi(this);

    setOptionsEnabled(false);

    // Load profiles
    JSONHelper::readFromJson(JSONHelper::PROFILES_FILENAME, &m_profiles);
    for (const Profile &profile : m_profiles)
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
        QWidget *widget{ ui->verticalLayout_options->itemAt(i)->widget() };
        widget->setEnabled(enabled);
    }
}

void ProfilesDialog::clearOptionFields()
{
    ui->lineEdit_name->setText("");
    ui->lineEdit_separator->setText("");
    ui->plainTextEdit_template->clear();
}

QString ProfilesDialog::findUniqueName(QString name) const
{
    QString nameNew{ name };
    int cnt{ 1 };
    while(m_profiles.contains(nameNew))
    {
        nameNew = name + "(" + QString::number(cnt) + ")";
        cnt++;
    }
    return nameNew;
}

void ProfilesDialog::on_listWidget_profiles_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    // Show data of selected profile is there is one selected
    if (current)
    {
        QString key{ current->text() };
        const Profile &profile{ m_profiles.value(key) };
        ui->lineEdit_name->setText(profile.getName());
        ui->lineEdit_separator->setText(profile.getSeperator());
        ui->checkBox_containsHeader->setChecked(profile.containsHeader());
        ui->plainTextEdit_template->setPlainText(profile.getTemplateText());
    }
    else
    {
        // Nothing to show in option fields
        clearOptionFields();
    }
    setOptionsEnabled(current != nullptr);
}

// Delete selected
void ProfilesDialog::on_pushButton_delete_clicked()
{
    // Only delete if there is something selected
    if (ui->listWidget_profiles->selectedItems().count() > 0)
    {
        QString key{ ui->listWidget_profiles->currentItem()->text() };
        // Remove from container
        m_profiles.remove(key);
        int selected{ ui->listWidget_profiles->currentRow() };
        // Remove from list
        ui->listWidget_profiles->takeItem(selected);
    }
}

void ProfilesDialog::on_pushButton_new_clicked()
{
    QString defaultName{ findUniqueName("New Profile") };
    m_profiles.insert(defaultName, { defaultName, "", false, "" });
    ui->listWidget_profiles->addItem(defaultName);
    // Select new created item
    ui->listWidget_profiles->setCurrentRow(m_profiles.size() - 1);
}

void ProfilesDialog::on_lineEdit_name_editingFinished()
{
    // if nothing is selected, there is nothing to do
    if (ui->listWidget_profiles->selectedItems().count() < 1)
    {
        return;
    }
    QString key{ ui->listWidget_profiles->currentItem()->text() };
    Profile profile{ m_profiles.value(key) };
    QString nameNew{ ui->lineEdit_name->text() };
    // Only find unique name variant, when the name has changed
    if (nameNew != key)
    {
        nameNew = findUniqueName(nameNew);
    }
    profile.setName(nameNew);
    ui->listWidget_profiles->currentItem()->setText(nameNew);
    ui->lineEdit_name->setText(nameNew);

    // Remove old key value pair and insert it with the new data (because key has changed)
    m_profiles.remove(key);
    m_profiles.insert(nameNew, profile);
}

void ProfilesDialog::on_lineEdit_separator_editingFinished()
{
    // if nothing is selected, there is nothing to do
    if (ui->listWidget_profiles->selectedItems().count() < 1)
    {
        return;
    }
    QString key{ ui->listWidget_profiles->currentItem()->text() };
    Profile &profile{ m_profiles[key] };
    profile.setSeperator(ui->lineEdit_separator->text());
}

void ProfilesDialog::on_checkBox_containsHeader_stateChanged(int arg1)
{
        // if nothing is selected, there is nothing to do
        if (ui->listWidget_profiles->selectedItems().count() < 1)
        {
            return;
        }
        QString key{ ui->listWidget_profiles->currentItem()->text() };
        Profile &profile{ m_profiles[key] };
        profile.setContainsHeader(ui->checkBox_containsHeader->isChecked());
}

// Instead of the editingFinished this method is called after every change in the widget. So dont do to heavy stuff here
// and implement an other solution instead
void ProfilesDialog::on_plainTextEdit_template_textChanged()
{
    // if nothing is selected, there is nothing to do
    if (m_profiles.size() < 1)
    {
        return;
    }
    QString key{ ui->listWidget_profiles->currentItem()->text() };
    Profile &profile{ m_profiles[key] };
    profile.setTemplateText(ui->plainTextEdit_template->toPlainText());
}

void ProfilesDialog::on_buttonBox_accepted()
{
    JSONHelper::writeToJson(JSONHelper::PROFILES_FILENAME, m_profiles);
}
