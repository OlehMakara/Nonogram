#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>

class CellButton : public QPushButton
{
    Q_OBJECT
public:
    CellButton(QWidget *parent = nullptr, int cellSize = 40);

private slots:
    void onStateChenged();

};

#endif // CELLBUTTON_H
