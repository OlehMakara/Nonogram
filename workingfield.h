#ifndef WORKINGFIELD_H
#define WORKINGFIELD_H

#include <QWidget>

#include "nonogramimage.h"

class CellButton;

namespace Ui {
class WorkingField;
}

class WorkingField : public QWidget
{
    Q_OBJECT

public:
    explicit WorkingField(const int rowsOfNonogram, const int columnsOfNonogram, const int cellSize, QWidget *parent = nullptr);
    ~WorkingField();
//    CellButton* **getCellsMatrix();

    int** getHorizontalCheckedCellsMatrix();
    int** getVerticalCheckedCellsMatrix();
    NonogramImage* getNonogramImage();


signals:
    void workingFieldChanged();

private slots:
    void onCellButtonClicked();
    void determineCheckedCells();

private:
    void createCheckedCellsMatrixs();
    void determineCheckedCellsMatrixFromUpToDown();
    void determineCheckedCellsMatrixFromLeftToRight();
    void printCheckedCellsMatrices();


private:
    const int rowsOfNonogram;
    const int columnsOfNonogram;
    const int cellSize;
    const int rowsOfCheckedCellsMatrix;
    const int columnsOfCheckedCellsMatrix;
    CellButton* **cellsMatrix;
    int **checkedCellsMatrixFromUpToDown;
    int **checkedCellsMatrixFromLeftToRight;
    Ui::WorkingField *ui;
};

#endif // WORKINGFIELD_H
