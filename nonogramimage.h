#ifndef NONOGRAMIMAGE_H
#define NONOGRAMIMAGE_H

#include <QString>
#include <QBitArray>

class NonogramImage
{
public:
    NonogramImage(int id, QString name, int rowsAmount, int columnsAmount, QBitArray matrix);
    ~NonogramImage();
    int getId();
    QString getName();
    int getRowsAmount();
    int getColumnsAmount();
    QBitArray getMatrix();

private:
    int id;
    QString name;
    int rowsAmount;
    int columnsAmount;
    QBitArray matrix;
};

#endif // NONOGRAMIMAGE_H
