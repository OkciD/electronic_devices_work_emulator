#include "mainwindow.h"
#include "categorieslistwidget.h"
#include "deviceslistwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->addDockWidget(Qt::LeftDockWidgetArea, (new CategoriesListWidget));
    this->setCentralWidget((new DevicesListWidget));
    this->setWindowTitle("Система эмуляции работы электронных устройств");
    this->setMinimumSize(640, 480);
}

MainWindow::~MainWindow()
{

}
