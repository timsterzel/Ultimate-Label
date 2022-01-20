#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settings.h"
#include <QIcon>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , m_settings(Settings::SETTINGS_FILENAME, QSettings::IniFormat)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);    
    setWindowTitle(tr("Settings"));
    setWindowIcon(QIcon(":/logo.png"));
    QString profilesStartPath{ m_settings.value(Settings::SETTINGS_FILE_START_PATH, "").toString() };
    int customWidth{ m_settings.value(Settings::SETTINGS_CUSTOM_WIDTH, "0").toInt() };
    int customHeight{ m_settings.value(Settings::SETTINGS_CUSTOM_HEIGHT, "0").toInt() };
    ui->lineEdit_startPath->setText(profilesStartPath);
    ui->spinBox_customWidth->setValue(customWidth);
    ui->spinBox_customHeight->setValue(customHeight);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    m_settings.setValue(Settings::SETTINGS_FILE_START_PATH, ui->lineEdit_startPath->text());
    m_settings.setValue(Settings::SETTINGS_CUSTOM_WIDTH, ui->spinBox_customWidth->value());
    m_settings.setValue(Settings::SETTINGS_CUSTOM_HEIGHT, ui->spinBox_customHeight->value());
}
