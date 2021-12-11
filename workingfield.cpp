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
    rowsOfNonogram(rows), columnsOfNonogram(columns), cellSize(cellSize),
    rowsOfCheckedCellsMatrix(rows/2 + rows%2), columnsOfCheckedCellsMatrix(columns/2 + columns%2),
    ui(new Ui::WorkingField)
{
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
    checkedCellsMatrixFromUpToDown = new int* [rowsOfCheckedCellsMatrix];
    for (int i = 0; i < rowsOfCheckedCellsMatrix; ++i) {
        checkedCellsMatrixFromUpToDown[i] = new int[columnsOfNonogram];
    }

    checkedCellsMatrixFromLeftToRight = new int* [rowsOfNonogram];
    for (int i = 0; i < rowsOfNonogram; ++i) {
        checkedCellsMatrixFromLeftToRight[i] = new int[columnsOfCheckedCellsMatrix];
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

int **WorkingField::getHorizontalCheckedCellsMatrix()
{
    return checkedCellsMatrixFromUpToDown;
}

int** WorkingField::getVerticalCheckedCellsMatrix()
{
    return checkedCellsMatrixFromLeftToRight;
}

void WorkingField::onCellButtonClicked()
{
    this->determineCheckedCells();
    emit workingFieldChanged();
}

void WorkingField::determineCheckedCells()
{
    this->determineCheckedCellsMatrixFromUpToDown();
    this->determineCheckedCellsMatrixFromLeftToRight();
#ifdef QT_DEBUG
    this->printCheckedCellsMatrices();
#endif
}


void WorkingField::determineCheckedCellsMatrixFromUpToDown()
{
    int checkedCellCount;
    int rowCount;

    for (int yi = 0; yi < columnsOfNonogram; ++yi) {
        checkedCellCount = 0;
        rowCount = rowsOfCheckedCellsMatrix-1;
        for (int xi = rowsOfNonogram-1; xi >= 0; --xi) {
            if (cellsMatrix[xi][yi]->isChecked())
            {
                ++checkedCellCount;
            }
            else
            {
                checkedCellsMatrixFromUpToDown[rowCount][yi] = checkedCellCount;
                if (checkedCellCount > 0)
                {
                    --rowCount;
                    checkedCellCount = 0;
                }
            }
        }

        for (int i = rowCount; i >= 0; --i) {
            checkedCellsMatrixFromUpToDown[i][yi] = 0;
        }

        if (rowCount >= 0)
            checkedCellsMatrixFromUpToDown[rowCount][yi] = checkedCellCount;
    }
}


void WorkingField::determineCheckedCellsMatrixFromLeftToRight()
{
    int checkedCellCount;
    int columnCount;

    for (int xi = 0; xi < rowsOfNonogram; ++xi) {
        checkedCellCount = 0;
        columnCount = columnsOfCheckedCellsMatrix-1;
        for (int yi = columnsOfNonogram-1; yi >= 0; --yi) {
            if (cellsMatrix[xi][yi]->isChecked())
            {
                ++checkedCellCount;
            }
            else
            {
                if (checkedCellCount > 0)
                {
                    checkedCellsMatrixFromLeftToRight[xi][columnCount] = checkedCellCount;
                    --columnCount;
                    checkedCellCount = 0;
                    std::cout << columnCount << std::endl;
                }
            }
        }

        for (int i = columnCount; i >= 0; --i) {
            checkedCellsMatrixFromLeftToRight[xi][i] = 0;
        }

        if (columnCount >= 0)
            checkedCellsMatrixFromLeftToRight[xi][columnCount] = checkedCellCount;
    }
}


void WorkingField::printCheckedCellsMatrices()
{
    for (int xi = 0; xi < rowsOfCheckedCellsMatrix; ++xi) {
        for (int yi = 0; yi < columnsOfNonogram; ++yi) {
            std::cout << checkedCellsMatrixFromUpToDown[xi][yi] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "-------------------------------------------" << std::endl;
    for (int xi = 0; xi < rowsOfNonogram; ++xi) {
        for (int yi = 0; yi < columnsOfCheckedCellsMatrix; ++yi) {
            std::cout << checkedCellsMatrixFromLeftToRight[xi][yi] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "||||||||||||||||||||||||||||||||||||||||||" << std::endl;

}
