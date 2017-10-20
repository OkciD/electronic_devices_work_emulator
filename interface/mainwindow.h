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
    const QSize mainMenuSize_ = QSize(640, 480);
    const QSize emulationScreenSize_ = QSize(1024, 768);

private slots:
     void changeDockWidget_(QWidget *clickedDeviceButton);
     void showEmulationScreen_(int deviceId);
};

#endif // MAINWINDOW_H
