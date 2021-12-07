#ifndef DATACELLSWGT_H
#define DATACELLSWGT_H

#include <QWidget>

class DataCellsWgt : public QWidget
{
    Q_OBJECT
public:
    explicit DataCellsWgt(const int rows, const int columns, const int cellSize, QWidget *parent = nullptr);

public slots:
    void onWorkingFieldChanged();

private:
    const int rows;
    const int columns;
    const int cellSize;
};

#endif // DATACELLSWGT_H
