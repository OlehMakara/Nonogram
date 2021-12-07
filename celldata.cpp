#include "celldata.h"

CellData::CellData(QWidget *parent, int cellSize) : QLabel(parent)
{
    this->setStyleSheet("border: none; background-color: rgb(255, 255, 255); color: black;");
    this->setText("");
    this->setMinimumWidth(cellSize);
    this->setMinimumHeight(cellSize);
    this->setFixedSize(cellSize, cellSize);
}
