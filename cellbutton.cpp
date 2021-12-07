#include "cellbutton.h"

CellButton::CellButton(QWidget *parent, int cellSize) : QPushButton(parent)
{
    this->setCheckable(true);
    this->setStyleSheet("border: none; background-color: rgb(210, 210, 210); color:white; checked { background-color: rgb(0, 0, 0); }");
//    this->setText("x");
    this->setMinimumWidth(cellSize);
    this->setMinimumHeight(cellSize);
    this->setFixedSize(cellSize, cellSize);

    connect(this, &CellButton::clicked, this, &CellButton::onStateChenged);


}

void CellButton::onStateChenged()
{
//    this->setText(this->isChecked()? "+" : "-");
    if (this->isChecked())
    {
        this->setStyleSheet("border: none; color:white; background-color: rgb(0, 0, 0);");
    }
    else
        this->setStyleSheet("border: none; color:white; background-color: rgb(210, 210, 210);");
}
