#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("About"));

    QPixmap pixmap(":/logo.png");
    ui->label_logo->setPixmap(pixmap);

}

AboutDialog::~AboutDialog()
{
    delete ui;
}
