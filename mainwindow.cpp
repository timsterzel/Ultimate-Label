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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_settings{ Settings::SETTINGS_FILENAME, QSettings::IniFormat }
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->tableWidget_data->setRowCount(0);
    //ui->tableWidget_data->setColumnCount(0);
    ui->tableWidget_data->horizontalHeader()->setStretchLastSection(true);
    // Select only one row and when the whole one
    ui->tableWidget_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_data->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableWidget_data->hide();
    //ui->comboBox_profiles->hide();
    ui->pushButton_print->hide();
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
    bool containsHeader{ false };
    if (ui->comboBox_profiles->count() > 0)
    {
        QString key{ ui->comboBox_profiles->currentText() };
        const Profile &profile{ m_profiles[key] };
        seperator = profile.getSeperator();
        containsHeader = profile.containsHeader();
    }

    QFile file{ fileName };
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error by opening file \n";
        return;
    }
    QTextStream in{ &file };

    //in.setCodec("UTF-8");
    // Use Latin1 to show german chars
    in.setCodec("Latin1");

    int row{ 0 };
    while(!in.atEnd())
    {
        ui->tableWidget_data->insertRow(row);
        QStringList loadedData;
        // Split line by separator and store data
        loadedData << in.readLine().split(seperator);
        // Show in TableWidget
        int column{ 0 };
        for (QString s : loadedData)
        {
            // Add the columns when there are not already created
            if (ui->tableWidget_data->columnCount() < loadedData.size())
            {
                ui->tableWidget_data->insertColumn(column);
            }
            QTableWidgetItem *item{ new QTableWidgetItem(s) };
            ui->tableWidget_data->setItem(row, column, item);
            column++;
        }
        row++;
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


