#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

#include "datacellswgt.h"
#include "sqlitedbmanager.h"

#include <QGridLayout>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbManager = SqliteDBManager::getInstance();
    dbManager->connectToDataBase();

    QGridLayout* gridLayout = new QGridLayout(this);
    ui->centralwidget->setLayout(gridLayout);
    gridLayout->setSizeConstraint(QLayout::SetMinimumSize);

    const int rows = 10;
    const int columns = 15;
    const int cellSize = 20;

    workingField = new WorkingField(rows, columns, cellSize, this);
    workingField->setStyleSheet("background-color: rgb(255, 0, 0);");
    gridLayout->addWidget(workingField, 1, 1);

    DataCellsWgt* horizontalDataCells = new DataCellsWgt(rows/2 + rows%2, columns, cellSize, workingField->getHorizontalCheckedCellsMatrix(), this);
    gridLayout->addWidget(horizontalDataCells, 0, 1);

    DataCellsWgt* verticalDataCells = new DataCellsWgt(rows, columns/2 + columns%2, cellSize, workingField->getVerticalCheckedCellsMatrix(), this);
    gridLayout->addWidget(verticalDataCells, 1, 0);


    connect(workingField, &WorkingField::workingFieldChanged, horizontalDataCells, &DataCellsWgt::onWorkingFieldChanged);
    connect(workingField, &WorkingField::workingFieldChanged, verticalDataCells, &DataCellsWgt::onWorkingFieldChanged);


    QPushButton *pb = new QPushButton(this);
    gridLayout->addWidget(pb, 0, 0);
    connect(pb,&QPushButton::clicked, this,&MainWindow::saveNonogramImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveNonogramImage()
{
    qDebug() << workingField->getNonogramImage()->getMatrix();
    dbManager->save(workingField->getNonogramImage());
//    bool** matrix = workingField->getNonogramImage()->getMatrix();
//    for (int xi = 0; xi < 10; ++xi)
//    {
//        for (int yi = 0; yi < 15; ++yi)
//        {
//            std::cout << matrix[xi][yi];
//        }
//    }
}

void MainWindow::openNonogramImage()
{

}
