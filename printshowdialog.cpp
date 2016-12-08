#include "printshowdialog.h"
#include "ui_printshowdialog.h"

PrintShowDialog::PrintShowDialog(QWidget *parent, QString dataToShow) :
    QDialog(parent),
    ui(new Ui::PrintShowDialog)
{
    ui->setupUi(this);

    ui->textEditHtml->insertHtml(dataToShow);
}

PrintShowDialog::~PrintShowDialog()
{
    delete ui;
}
