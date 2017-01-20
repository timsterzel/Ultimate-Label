#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settings.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , m_settings(Settings::SETTINGS_FILENAME, QSettings::IniFormat)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);    

    QString profilesStartPath{ m_settings.value(Settings::SETTINGS_FILE_START_PATH, "").toString() };
    ui->lineEdit_startPath->setText(profilesStartPath);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    m_settings.setValue(Settings::SETTINGS_FILE_START_PATH, ui->lineEdit_startPath->text());
}
