#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jsonhelper.h"
#include "printshowdialog.h"
#include "profilesdialog.h"
#include "settingsdialog.h"
#include "settings.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_settings{ Settings::SETTINGS_FILENAME, QSettings::IniFormat }
    , m_manualDialog{ nullptr }
    , m_aboutDialog{ nullptr }
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Ultimate Label"));
    setWindowIcon(QIcon(":/logo.png"));
    //ui->tableWidget_data->setRowCount(0);
    //ui->tableWidget_data->setColumnCount(0);
    ui->tableWidget_data->horizontalHeader()->setStretchLastSection(true);
    // Select only one row and when the whole one
    ui->tableWidget_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_data->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableWidget_data->hide();
    //ui->comboBox_profiles->hide();
    //ui->pushButton_print->hide();
    loadProfiles();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_open_triggered()
{
    // load start path
    QString startPath{ m_settings.value(Settings::SETTINGS_FILE_START_PATH, "").toString() };
    QString fileName{ "" };
    // When startpath was set in options, open dialog with this start path
    if (startPath != "")
    {
        fileName = QFileDialog::getOpenFileName(this, tr("Open"), startPath);
    }
    // Else use default path
    else
    {
        fileName = QFileDialog::getOpenFileName(this, tr("Open"));
    }
    loadCSVFile(fileName);
}

void MainWindow::loadProfiles()
{
    ui->comboBox_profiles->clear();
    m_profiles.clear();
    JSONHelper::readFromJson(JSONHelper::PROFILES_FILENAME, &m_profiles);
    for (const Profile &profile : m_profiles)
    {
        ui->comboBox_profiles->addItem(profile.getName());        
    }
}

void MainWindow::loadCSVFile(QString fileName)
{
    // Load options from selected profile, if there is no profile
    // use default values
    QString seperator{ "," };
    QString codec{ "UTF-8" };
    bool containsHeader{ false };
    if (ui->comboBox_profiles->count() > 0)
    {
        QString key{ ui->comboBox_profiles->currentText() };
        const Profile &profile{ m_profiles[key] };
        seperator = profile.getSeperator();
        codec = profile.getCodec();
        containsHeader = profile.containsHeader();
    }

    QFile file{ fileName };
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error by opening file \n";
        return;
    }
    QTextStream in{ &file };

    //QTextCodec textCodec(codec);
    in.setCodec(QTextCodec::codecForName(codec.toUtf8()));
    // True when table was empty by starting in this method
    bool wasTableEmpty{ ui->tableWidget_data->rowCount() < 1 };
    // When we start we are always in first row
    bool isFirstRow{ true };
    int row{ 0 };
    while(!in.atEnd())
    {
        QStringList loadedData;        
        // Split line by separator and store data
        loadedData << in.readLine().split(seperator);
        // When table was empty we have to create the columns first
        if (isFirstRow && wasTableEmpty)
        {
            for (int i{ 0 }; i < loadedData.size(); i++)
            {
                ui->tableWidget_data->insertColumn(i);
            }
            if (containsHeader)
            {
                // No data is in table yet and csv file has header, so we show the header
                ui->tableWidget_data->setHorizontalHeaderLabels(loadedData);
            }
        }
        // Load table data
        if (!isFirstRow || !containsHeader)
        {
            ui->tableWidget_data->insertRow(row);
            // Show in TableWidget
            int column{ 0 };
            for (QString s : loadedData)
            {
                QTableWidgetItem *item{ new QTableWidgetItem(s) };
                ui->tableWidget_data->setItem(row, column, item);
                column++;
            }
            row++;
        }
        isFirstRow = false;
    }

    // Show needed widget with loaded data
    ui->tableWidget_data->show();
    ui->comboBox_profiles->show();
    ui->pushButton_print->show();
    // Call slot when the horizontal header was clicked
    connect(ui->tableWidget_data->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_tableHorizontalHeaderClicked(int)));
}

void MainWindow::on_actionProfiles_triggered()
{
    ProfilesDialog dialog;
    dialog.setModal(true);
    dialog.exec();
    // Reload profiles, because data has perhaps changed
    loadProfiles();
}

void MainWindow::on_actionClear_triggered()
{
    ui->tableWidget_data->clear();
    ui->tableWidget_data->setRowCount(0);
    ui->tableWidget_data->setColumnCount(0);

    // Hide widgets which are not needed without loaded data
    ui->tableWidget_data->hide();
    ui->pushButton_print->hide();
}

void MainWindow::on_pushButton_print_clicked()
{
    // Print csv data
    if (ui->tabWidget->currentIndex() == 0)
    {
        // Only print when there is a row selected and a profile is selected
        if (ui->tableWidget_data->selectedItems().size() < 1)
        {
            QMessageBox::information(this, "Nope", "Please select a row to print");
            return;
        }
        if (ui->comboBox_profiles->count() < 1)
        {
            QMessageBox::information(this, "Nope", "Please select a profile for printing");
            return;
        }
        QString key{ ui->comboBox_profiles->currentText() };

        QString tempText{ m_profiles[key].getTemplateText() };
        // Replace placeholders which column data
        for (int i{ 0 }; i < ui->tableWidget_data->columnCount(); i++)
        {
            QString data{ ui->tableWidget_data->selectedItems().at(i)->text() };
            // Placeholder has the form $(column)
            tempText.replace("$(" + QString::number(i + 1) + ")", data);
        }
        // Show dialog which show the data for printing
        PrintShowDialog dialog{ nullptr, tempText };
        dialog.setModal(true);
        dialog.exec();
    }
    // Print data of text edit in label tab
    else if (ui->tabWidget->currentIndex() == 1)
    {
        QString printText{ ui->textEdit_label->toHtml() };
        PrintShowDialog dialog{ nullptr, printText };
        dialog.setModal(true);
        dialog.exec();
    }
}

void MainWindow::on_tableHorizontalHeaderClicked(int index)
{
    //qDebug() << "tableColumnHeaderClicked i: " << index << "\n";
    // Sort data
    ui->tableWidget_data->sortItems(index, Qt::AscendingOrder);
}



void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_actionManual_triggered()
{
    if (!m_manualDialog) {
        m_manualDialog = new ManualDialog(this);
        m_manualDialog->setModal(false);
    }
    m_manualDialog->show();
}

void MainWindow::on_actionAbout_triggered()
{
    if (!m_aboutDialog) {
        m_aboutDialog = new AboutDialog(this);
        m_aboutDialog->setModal(false);
    }
    m_aboutDialog->show();
}
