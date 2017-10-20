#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "categorieslistwidget.h"
#include "deviceslistwidget.h"
#include "dockwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    DockWidget *dockWidget_;
    CategoriesListWidget *categoriesListWidget_;
    DevicesListWidget *devicesListWidget_;

private slots:
     void changeToEmulationScreen_(QWidget *clickedDeviceButton);
};

#endif // MAINWINDOW_H
