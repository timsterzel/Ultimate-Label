#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget_data->setColumnCount(6);
    ui->tableWidget_data->setRowCount(3);
    ui->tableWidget_data->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_data->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_ffnen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"));
    qDebug() << "FileName: " << fileName;
    loadCSVFile(fileName);
}

void MainWindow::loadCSVFile(QString fileName)
{
    ui->tableWidget_data->clear();
    ui->tableWidget_data->setRowCount(0);
    ui->tableWidget_data->setColumnCount(0);

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error by opening file \n";
        return;
    }
    QTextStream in(&file);

    //in.setCodec("UTF-8");
    // Use Latin1 to show german chars
    in.setCodec("Latin1");
    //QStringList loadedData;
    int row = 0;
    while(!in.atEnd())
    {
        ui->tableWidget_data->insertRow(row);
        QStringList loadedData;
        // Split line by separator and store data
        loadedData << in.readLine().split(";");
        // Show in TableWidget
        int column = 0;
        for (QString s : loadedData)
        {
            // If row is 0 we are in the first round of the loop, so we have to add the columns
            if (row == 0)
            {
                ui->tableWidget_data->insertColumn(column);
            }
            QTableWidgetItem *item = new QTableWidgetItem(s);
            ui->tableWidget_data->setItem(row, column, item);
            column++;
        }
        row++;
    }
    // Show TableWidget with loaded data
    ui->tableWidget_data->show();

}
