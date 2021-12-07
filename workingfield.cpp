#include "workingfield.h"
#include "ui_workingfield.h"
#include "cellbutton.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

#include <iostream>


WorkingField::WorkingField(const int rows, const int columns, const int cellSize, QWidget *parent) :
    QWidget(parent),
    rows(rows), columns(columns), cellSize(cellSize),
    ui(new Ui::WorkingField)
{
//    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(255, 0, 0);");

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(1);
    gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(gridLayout);

    createCheckedCellsMatrixs();

    cellsMatrix = new CellButton** [rows];

    for (int xi = 0; xi < rows; ++xi) {
        cellsMatrix[xi] = new CellButton* [columns];

        for (int yi = 0; yi < columns; ++yi) {
            CellButton* cellButton = new CellButton(this, cellSize);
            connect(cellButton, &CellButton::clicked, this, &WorkingField::onCellButtonClicked);

            gridLayout->addWidget(cellButton, xi, yi);
            cellsMatrix[xi][yi] = cellButton;
        }
        gridLayout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum), xi, columns);
    }
    gridLayout->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), rows, columns);
}

void WorkingField::createCheckedCellsMatrixs()
{
    checkedCellsMatrixFromUpToDown = new int* [rows/2 + rows%2];
    for (int i = 0; i < rows/2 + rows%2; ++i) {
        checkedCellsMatrixFromUpToDown[i] = new int[columns];
        for (int j = 0; j < columns; ++j) {
            checkedCellsMatrixFromUpToDown[i][j] = 0;
        }
    }

    checkedCellsMatrixFromLeftToRight = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        checkedCellsMatrixFromLeftToRight[i] = new int[columns/2 + columns%2];
    }
}

WorkingField::~WorkingField()
{
    delete ui;
}

CellButton*** WorkingField::getCellsMatrix()
{
    return cellsMatrix;
}

void WorkingField::onCellButtonClicked()
{
    this->countCheckedCells();
    emit workingFieldChanged();
}

void WorkingField::countCheckedCells()
{
    int checkedCellCount;
    int rowCount;
    int columnCount;
    for (int yi = 0; yi < columns; ++yi) {
        checkedCellCount = 0;
        rowCount = 0;
        for (int xi = rows-1; xi >= 0; --xi) {
            if (cellsMatrix[xi][yi]->isChecked())
            {
                ++checkedCellCount;
            }
            else if (checkedCellCount > 0)
            {
                checkedCellsMatrixFromUpToDown[rowCount][yi] = checkedCellCount;
                checkedCellCount = 0;
                ++rowCount;
                std::cout << rowCount << std::endl;
            }
        }
        if (rowCount < 5)
            checkedCellsMatrixFromUpToDown[rowCount][yi] = checkedCellCount;
        else
            checkedCellsMatrixFromUpToDown[rowCount-1][yi] = checkedCellCount;
    }

    //TODO fix
    for (int xi = 0; xi < rows/2 + rows%2; ++xi) {
        for (int yi = 0; yi < columns; ++yi) {
            std::cout << checkedCellsMatrixFromUpToDown[xi][yi] << "  ";
        }
        std::cout << std::endl;
    }



}
