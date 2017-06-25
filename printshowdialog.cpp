#include "printshowdialog.h"
#include "ui_printshowdialog.h"
#include "settings.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include "printmanager.h"

PrintShowDialog::PrintShowDialog(QWidget *parent, QString dataToShow)
    : QDialog(parent)
    , m_settings(Settings::SETTINGS_FILENAME, QSettings::IniFormat)
    , ui(new Ui::PrintShowDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Print"));
    setWindowIcon(QIcon(":/logo.png"));

    ui->spinBox_fontSize->setMinimum(1);
    ui->spinBox_fontSize->setValue(12);
    ui->textEditHtml->setFontPointSize(12);

    ui->textEditHtml->insertHtml(dataToShow);
    ui->spinBox_customWidth->setEnabled(false);
    ui->spinBox_customHeight->setEnabled(false);

    int customWidth{ m_settings.value(Settings::SETTINGS_CUSTOM_WIDTH, "0").toInt() };
    int customHeight{ m_settings.value(Settings::SETTINGS_CUSTOM_HEIGHT, "0").toInt() };
    ui->spinBox_customWidth->setValue(customWidth);
    ui->spinBox_customHeight->setValue(customHeight);

    ui->checkBox_customSize->setChecked(true);
}

PrintShowDialog::~PrintShowDialog()
{
    delete ui;
}

void PrintShowDialog::on_pushButton_print_clicked()
{
    QTextDocument *doc{ ui->textEditHtml->document() };
    bool customSize{ false };
    int customWidth{ 0 };
    int customHeight{ 0 };
    if (ui->checkBox_customSize->isChecked())
    {
        customSize = true;
        customWidth = ui->spinBox_customWidth->value();
        customHeight = ui->spinBox_customHeight->value();
    }

    if (!PrintManager::print(this, tr("Print Document"), doc, customSize, customWidth, customHeight))
    {
        QMessageBox::information(this, tr("Error by opening printer"), tr("Cannot print file"));
    }
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

void PrintShowDialog::on_checkBox_customSize_clicked()
{

}

void PrintShowDialog::on_checkBox_customSize_stateChanged(int state)
{
    ui->spinBox_customWidth->setEnabled(state);
    ui->spinBox_customHeight->setEnabled(state);
}

void PrintShowDialog::on_spinBox_fontSize_valueChanged(int arg1)
{
    /*
    QTextEdit *textEdit{ ui->textEditHtml };
    QTextCursor cursor{ textEdit->textCursor() };
    if (cursor.hasSelection())
    {
        // Set selection to new font size
        QTextCharFormat format;
        format.setFontPointSize(arg1);
        cursor.mergeCharFormat(format);
    }
    else
    {
        // Make new text to new font size
        textEdit->setFontPointSize(arg1);
    }
    textEdit->setFocus();
    */
}

void PrintShowDialog::on_pushButton_fontUnserline_clicked()
{
    QTextEdit *textEdit{ ui->textEditHtml };
    QTextCursor cursor{ textEdit->textCursor() };
    bool isUnderlined{ false };
    // setFontUnderline
    if (cursor.hasSelection())
    {
        // Make selection underlined / not underlined
        isUnderlined = cursor.charFormat().fontUnderline();
        QTextCharFormat format;
        format.setFontUnderline(!isUnderlined);
        cursor.mergeCharFormat(format);
    }
    else
    {
        // Make new text underlined / not underlined
        isUnderlined = textEdit->fontUnderline();
        textEdit->setFontUnderline(!isUnderlined);
    }
    QPushButton *btn{ ui->pushButton_fontUnserline };
    changeBtnActiveColor(btn, !isUnderlined);
    textEdit->setFocus();
}

void PrintShowDialog::on_pushButton_fontBold_clicked()
{
    QTextEdit *textEdit{ ui->textEditHtml };
    QTextCursor cursor{ textEdit->textCursor() };
    bool isBold{ false };
    if (cursor.hasSelection())
    {
        // Make selection bold or unbold
        isBold = cursor.charFormat().fontWeight() == QFont::Weight::Bold;
        QTextCharFormat format;
        format.setFontWeight(isBold ? QFont::Weight::Normal : QFont::Weight::Bold);
        cursor.mergeCharFormat(format);
    }
    else
    {
        // Make new text bold / not bold
        isBold = textEdit->fontWeight() == QFont::Weight::Bold;
        textEdit->setFontWeight(isBold ? QFont::Weight::Normal : QFont::Weight::Bold);
    }
    QPushButton *btn{ ui->pushButton_fontBold };
    changeBtnActiveColor(btn, !isBold);
    textEdit->setFocus();
}

void PrintShowDialog::on_pushButton_fontItalic_clicked()
{
    QTextEdit *textEdit{ ui->textEditHtml };
    QTextCursor cursor{ textEdit->textCursor() };
    bool isItalic{ false };
    // setFontUnderline
    if (cursor.hasSelection())
    {
        // Make selection italic / not italic
        isItalic = cursor.charFormat().fontItalic();
        QTextCharFormat format;
        format.setFontItalic(!isItalic);
        cursor.mergeCharFormat(format);
    }
    else
    {
        // Make new text italic / not italic
        isItalic = textEdit->fontItalic();
        textEdit->setFontItalic(!isItalic);
    }
    QPushButton *btn{ ui->pushButton_fontItalic };
    changeBtnActiveColor(btn, !isItalic);
    textEdit->setFocus();
}

void PrintShowDialog::on_textEditHtml_selectionChanged()
{
    QTextEdit *textEdit{ ui->textEditHtml };
    QTextCursor cursor{ textEdit->textCursor() };
    bool isBtnUnderlineActive{ false };
    bool isBtnBoldActive{ false };
    bool isBtnItalicActive{ false };

    if (cursor.hasSelection())
    {
        isBtnUnderlineActive = cursor.charFormat().fontUnderline();
        isBtnBoldActive = cursor.charFormat().fontWeight() == QFont::Weight::Bold;
        isBtnItalicActive = cursor.charFormat().fontItalic();
    }
    else
    {
        isBtnUnderlineActive = textEdit->fontUnderline();
        isBtnBoldActive = textEdit->fontWeight() == QFont::Weight::Bold;
        isBtnItalicActive = textEdit->fontItalic();
    }
    QPushButton *btnUnderline{ ui->pushButton_fontUnserline };
    QPushButton *btnBold{ ui->pushButton_fontBold };
    QPushButton *btnItalic{ ui->pushButton_fontItalic };

    changeBtnActiveColor(btnUnderline, isBtnUnderlineActive);
    changeBtnActiveColor(btnBold, isBtnBoldActive);
    changeBtnActiveColor(btnItalic, isBtnItalicActive);
}

void PrintShowDialog::changeBtnActiveColor(QPushButton *button, bool isActive)
{
    QColor colorActive{ 0, 128, 0 };
    QColor colorInActive{ Qt::white };
    QPalette pal;
    if (isActive)
    {
        pal.setColor(QPalette::Button, colorActive);
    }
    else
    {
        pal.setColor(QPalette::Button, colorInActive);
    }
    button->setPalette(pal);
}
/*
void PrintShowDialog::changeSpinBoxValueWithoutTriggeringSignal(QSpinBox *spinBox, int value)
{
    bool oldState{ spinBox->blockSignals(true) };
    spinBox->setValue(value);
    spinBox->blockSignals(oldState);
}
*/

void PrintShowDialog::on_textEditHtml_cursorPositionChanged()
{
    if (ui->textEditHtml->toPlainText() == "")
    {
        ui->textEditHtml->setFontPointSize(ui->spinBox_fontSize->value());
    }
}

void PrintShowDialog::on_spinBox_fontSize_editingFinished()
{
    int fontSize{ ui->spinBox_fontSize->value() };
    QTextEdit *textEdit{ ui->textEditHtml };
    QTextCursor cursor{ textEdit->textCursor() };
    if (cursor.hasSelection())
    {
        // Set selection to new font size
        QTextCharFormat format;
        format.setFontPointSize(fontSize);
        cursor.mergeCharFormat(format);
    }
    else
    {
        // Make new text to new font size
        textEdit->setFontPointSize(fontSize);
    }
    textEdit->setFocus();
}
