#ifndef DATACELLSWGT_H
#define DATACELLSWGT_H

#include <QWidget>

#include "celldata.h"

class DataCellsWgt : public QWidget
{
    Q_OBJECT
public:
    explicit DataCellsWgt(const int rows, const int columns, const int cellSize, int **checkedCellsMatrix, QWidget *parent = nullptr);

public slots:
    void onWorkingFieldChanged();

private:
    const int rows;
    const int columns;
    const int cellSize;
    int **checkedCellsMatrix;
    CellData* **cellsMatrix;
};

#endif // DATACELLSWGT_H
