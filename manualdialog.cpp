#include "manualdialog.h"
#include "ui_manualdialog.h"

ManualDialog::ManualDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Manual"));
    // Load manual from resource
    ui->textBrowser_manual->setSource(QUrl("qrc:/manual.html"));

}

ManualDialog::~ManualDialog()
{
    delete ui;
}
