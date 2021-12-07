#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "workingfield.h"
#include "datacellswgt.h"

#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout* gridLayout = new QGridLayout(this);
    ui->centralwidget->setLayout(gridLayout);
    gridLayout->setSizeConstraint(QLayout::SetMinimumSize);


    const int rows = 10;
    const int columns = 15;
    const int cellSize = 20;

    DataCellsWgt* horizontalDataCells = new DataCellsWgt(rows/2 + rows%2, columns, cellSize, this);
    gridLayout->addWidget(horizontalDataCells, 0, 1);

    DataCellsWgt* verticalDataCells = new DataCellsWgt(rows, columns/2 + columns%2, cellSize, this);
    gridLayout->addWidget(verticalDataCells, 1, 0);

    WorkingField* workingField = new WorkingField(rows, columns, cellSize, this);
    workingField->setStyleSheet("background-color: rgb(255, 0, 0);");
    gridLayout->addWidget(workingField, 1, 1);

    connect(workingField, &WorkingField::workingFieldChanged, horizontalDataCells, &DataCellsWgt::onWorkingFieldChanged);
    connect(workingField, &WorkingField::workingFieldChanged, verticalDataCells, &DataCellsWgt::onWorkingFieldChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

