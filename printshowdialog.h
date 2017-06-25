#ifndef PRINTSHOWDIALOG_H
#define PRINTSHOWDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class PrintShowDialog;
}

class PrintShowDialog : public QDialog
{
    Q_OBJECT
private:
    QSettings m_settings;
public:
    PrintShowDialog(QWidget *parent = 0, QString dataToShow = "");
    ~PrintShowDialog();

private slots:
    void on_pushButton_print_clicked();

    void on_pushButton_clicked();

    void on_checkBox_customSize_clicked();

    void on_checkBox_customSize_stateChanged(int arg1);

    void on_spinBox_fontSize_valueChanged(int arg1);

    void on_pushButton_fontUnserline_clicked();

    void on_pushButton_fontBold_clicked();

    void on_pushButton_fontItalic_clicked();

    void on_textEditHtml_selectionChanged();

    void changeBtnActiveColor(QPushButton *button, bool isActive);

private:
    Ui::PrintShowDialog *ui;
};

#endif // PRINTSHOWDIALOG_H
