#include "nonogramimage.h"



NonogramImage::NonogramImage(int id, QString name, int rowsAmount, int columnsAmount, QBitArray matrix) :
    id(id), name(name), rowsAmount (rowsAmount), columnsAmount(columnsAmount), matrix(matrix)
{}

NonogramImage::~NonogramImage()
{

}

int NonogramImage::getId()
{
    return id;
}

QString NonogramImage::getName()
{
    return name;
}

int NonogramImage::getRowsAmount()
{
    return rowsAmount;
}

int NonogramImage::getColumnsAmount()
{
    return columnsAmount;
}

QBitArray NonogramImage::getMatrix()
{

    return matrix;
}
