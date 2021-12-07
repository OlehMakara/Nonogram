#ifndef DATACELL_H
#define DATACELL_H

#include <QLabel>

class CellData : public QLabel
{
    Q_OBJECT
public:
    CellData(QWidget *parent = nullptr, int cellSize = 40);;
};

#endif // DATACELL_H
