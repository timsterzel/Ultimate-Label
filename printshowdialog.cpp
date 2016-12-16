#include "printshowdialog.h"
#include "ui_printshowdialog.h"
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

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

void PrintShowDialog::on_pushButton_print_clicked()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle("Print Document");
    dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    QPainter painter;
    painter.begin(&printer);
    double scaleX = printer.pageRect().width() / (double) (ui->textEditHtml->width());
    double scaleY = printer.pageRect().height() / (double) (ui->textEditHtml->height());
    double scale = qMin(scaleX, scaleY);
    painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
                      printer.paperRect().y() + printer.pageRect().height()/2);
    painter.scale(scale, scale);
    painter.translate(-width() / 2, -height() / 2);
    ui->textEditHtml->render(&painter);
}
