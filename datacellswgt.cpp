#include "datacellswgt.h"

#include "workingfield.h"
#include "cellbutton.h"

#include <QGridLayout>

DataCellsWgt::DataCellsWgt(const int rows, const int columns, const int cellSize, int **checkedCellsMatrix, QWidget *parent) : QWidget(parent),
    rows(rows), columns(columns), cellSize(cellSize), checkedCellsMatrix(checkedCellsMatrix)
{
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(1);
    gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(gridLayout);

    cellsMatrix = new CellData** [rows];
    for (int xi = 0; xi < rows; ++xi) {
        cellsMatrix[xi] = new CellData* [columns];
        for (int yi = 0; yi < columns; ++yi) {
            CellData* celldata = new CellData(this, cellSize);
            gridLayout->addWidget(celldata, xi, yi);
            cellsMatrix[xi][yi] = celldata;
        }
        gridLayout->addItem(new QSpacerItem(1, cellSize, QSizePolicy::Expanding, QSizePolicy::Minimum), xi, columns);
    }
    gridLayout->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), rows, columns);

}

void DataCellsWgt::onWorkingFieldChanged()
{
    for (int xi = 0; xi < rows; ++xi) {
        for (int yi = 0; yi < columns; ++yi) {
            if (checkedCellsMatrix[xi][yi] > 0)
                cellsMatrix[xi][yi]->setText(QString::number(checkedCellsMatrix[xi][yi]));
            else
                cellsMatrix[xi][yi]->setText("");
        }
    }
}
