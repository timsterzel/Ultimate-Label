#include "printshowdialog.h"
#include "ui_printshowdialog.h"
#include "settings.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

PrintShowDialog::PrintShowDialog(QWidget *parent, QString dataToShow)
    : QDialog(parent)
    , m_settings(Settings::SETTINGS_FILENAME, QSettings::IniFormat)
    , ui(new Ui::PrintShowDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Print"));
    ui->textEditHtml->insertHtml(dataToShow);
    ui->spinBox_customWidth->setEnabled(false);
    ui->spinBox_customHeight->setEnabled(false);

    int customWidth{ m_settings.value(Settings::SETTINGS_CUSTOM_WIDTH, "0").toInt() };
    int customHeight{ m_settings.value(Settings::SETTINGS_CUSTOM_HEIGHT, "0").toInt() };
    ui->spinBox_customWidth->setValue(customWidth);
    ui->spinBox_customHeight->setValue(customHeight);

    ui->checkBox_defaultSize->setChecked(true);
}

PrintShowDialog::~PrintShowDialog()
{
    delete ui;
}

void PrintShowDialog::on_pushButton_print_clicked()
{
    // Let user select printer and set options
    QPrinter printer;
    QPrintDialog dialog{ &printer, this };
    dialog.setWindowTitle("Print Document");
    dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if (dialog.exec() != QDialog::Accepted)
    {
        qDebug() << "Error by opening Printer dialog\n";
        QMessageBox::information(this, tr("Error by opening printer"), tr("Cannot print file"));
        return;
    }
    //printer.setPaperSize(QSizeF(62, 29), QPrinter::Millimeter);
    // Use custom size when option is set
    if (ui->checkBox_defaultSize->isChecked())
    {
        int customWidth{ ui->spinBox_customWidth->value() };
        int customHeight{ ui->spinBox_customHeight->value() };
        printer.setPaperSize(QSizeF(customWidth, customHeight), QPrinter::Millimeter);
    }
    QTextDocument *doc{ ui->textEditHtml->document() };
    // Scale painter so the documents content fits perfect
    double scaleX{ printer.pageRect().width() / (double) (doc->size().width()) };
    double scaleY{ printer.pageRect().height() / (double) (doc->size().height()) };
    double scale{ qMin(scaleX, scaleY) };
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

void PrintShowDialog::on_pushButton_clicked()
{
    QString fileName{ QFileDialog::getSaveFileName(this, tr("Save to"), "unnamed.html") };
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Error by saving file: " << fileName << "\n";
        QMessageBox::information(this, tr("Error by saving file"), tr("Cannot save file"));
        return;
    }
    QTextStream out(&file);
    out << ui->textEditHtml->toHtml();
    file.close();
}

void PrintShowDialog::on_checkBox_defaultSize_clicked()
{

}

void PrintShowDialog::on_checkBox_defaultSize_stateChanged(int state)
{
    qDebug() << "CHanged \n";
    ui->spinBox_customWidth->setEnabled(state);
    ui->spinBox_customHeight->setEnabled(state);
}
