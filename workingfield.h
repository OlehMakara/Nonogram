#ifndef WORKINGFIELD_H
#define WORKINGFIELD_H

#include <QWidget>

class CellButton;

namespace Ui {
class WorkingField;
}

class WorkingField : public QWidget
{
    Q_OBJECT

public:
    explicit WorkingField(const int rows, const int columns, const int cellSize, QWidget *parent = nullptr);
    ~WorkingField();
    CellButton* **getCellsMatrix();

signals:
    void workingFieldChanged();

private slots:
    void onCellButtonClicked();
    void countCheckedCells();
    void createCheckedCellsMatrixs();

private:
    const int rows;
    const int columns;
    const int cellSize;
    CellButton* **cellsMatrix;
    int **checkedCellsMatrixFromUpToDown;
    int **checkedCellsMatrixFromLeftToRight;
    Ui::WorkingField *ui;
};

#endif // WORKINGFIELD_H
