#include "datacellswgt.h"

#include "celldata.h"
#include "workingfield.h"
#include "cellbutton.h"

#include <QGridLayout>

DataCellsWgt::DataCellsWgt(const int rows, const int columns, const int cellSize, QWidget *parent) : QWidget(parent),
    rows(rows), columns(columns), cellSize(cellSize)
{
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(1);
    gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(gridLayout);

//    const int x = 10;
//    const int y = 10;
//    int cellSize = 20;

    CellData* cellsMatrix [rows][columns];

    for (int xi = 0; xi < rows; ++xi) {
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
//    WorkingField* workingField = qobject_cast<WorkingField*>(sender());
//    if (workingField != nullptr)
//    {
//        auto cellMatrix = workingField->getCellsMatrix();
//        for (auto vector : cellMatrix) {
//            for (auto cell : vector) {

//            }
//        }
//    }
}
