#include "printshowdialog.h"
#include "ui_printshowdialog.h"
#include <QDebug>
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
    // Let user select printer and set options
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle("Print Document");
    dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if (dialog.exec() != QDialog::Accepted)
    {
        qDebug() << "Error by opening Printer dialog\n";
        return;
    }
    //printer.setPaperSize(QSizeF(62, 29), QPrinter::Millimeter);
    QTextDocument *doc = ui->textEditHtml->document();
    // Scale painter so the documents content fits perfect
    double scaleX = printer.pageRect().width() / (double) (doc->size().width());
    double scaleY = printer.pageRect().height() / (double) (doc->size().height());
    double scale = qMin(scaleX, scaleY);
    QPainter painter;
    painter.begin(&printer);
    painter.scale(scale, scale);
    // Print
    doc->drawContents(&painter);


    //ui->textEditHtml->print(&printer);

    /*
    QPrinter printer2(QPrinter::HighResolution);
    printer2.setPaperSize(QSizeF(62, 29), QPrinter::Millimeter);
    printer2.fullPage();
    printer2.setOutputFormat(QPrinter::PdfFormat);
    printer2.setOutputFileName("output.pdf");
    */

    /*
    QPainter painter;
    painter.begin(&printer);
    ui->textEditHtml->render(&painter);
    */

}
