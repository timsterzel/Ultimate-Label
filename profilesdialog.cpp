#include "profilesdialog.h"
#include "ui_profilesdialog.h"

ProfilesDialog::ProfilesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfilesDialog)
{
    ui->setupUi(this);
}

ProfilesDialog::~ProfilesDialog()
{
    delete ui;
}
