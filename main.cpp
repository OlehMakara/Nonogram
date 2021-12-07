#include "mainwindow.h"

#include "cellbutton.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    CellButton cell;
//    cell.show();

    return a.exec();
}
