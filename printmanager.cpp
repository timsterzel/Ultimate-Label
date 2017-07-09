#include "printmanager.h"
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>

bool PrintManager::print(QWidget *parent, QString windowTitle, QTextDocument *document, bool customSize, int customWidth, int customHeight, int copies)
{
    QPrinter printer;
    QPrintDialog dialog{ &printer, parent };
    dialog.setWindowTitle(windowTitle);
    dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if (dialog.exec() != QDialog::Accepted)
    {
        qDebug() << "Error by opening Printer dialog\n";
        return false;
    }
    //printer.setPaperSize(QSizeF(62, 29), QPrinter::Millimeter);
    // Use custom size when option is set
    if (customSize)
    {
        printer.setPaperSize(QSizeF(customWidth, customHeight), QPrinter::Millimeter);
    }
    // Scale painter so the documents content fits perfect
    double scaleX{ printer.pageRect().width() / (double) (document->size().width()) };
    double scaleY{ printer.pageRect().height() / (double) (document->size().height()) };
    double scale{ qMin(scaleX, scaleY) };
    QPainter painter;
    painter.begin(&printer);
    painter.scale(scale, scale);
    // Print. Here we print as much copies, which are specified in "copies" parameter
    for (int i{ 0 }; i < copies; i++)
    {
        document->drawContents(&painter);
    }
    return true;
}
