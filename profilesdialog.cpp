#include "profilesdialog.h"
#include "ui_profilesdialog.h"
#include "jsonhelper.h"

ProfilesDialog::ProfilesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfilesDialog)
{
    ui->setupUi(this);
    // Load profiles
    JSONHelper::readFromJson(JSONHelper::PROFILES_FILENAME, &m_profiles);
    for (Profile profile : m_profiles)
    {
        ui->listWidget_profiles->addItem(profile.getName());
    }
    //ui->listWidget_profiles
    // listWidget_profiles
}

ProfilesDialog::~ProfilesDialog()
{
    delete ui;
}
