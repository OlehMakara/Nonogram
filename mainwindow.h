#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "workingfield.h"
#include "idbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openNonogramImage();
    void saveNonogramImage();

private:
    IDBManager *dbManager;
    WorkingField* workingField;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
