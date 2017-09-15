#include "mainwindow.h"
#include "categorieslistwidget.h"
#include "deviceslistwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    CategoriesListWidget *categoriesListWidget = new CategoriesListWidget;
    DevicesListWidget *devicesListWidget = new DevicesListWidget;

    connect(&categoriesListWidget->getSignalMapper(), SIGNAL(mapped(int)), devicesListWidget, SLOT(showDevicesInCategory(int)));

    this->addDockWidget(Qt::LeftDockWidgetArea, categoriesListWidget);
    this->setCentralWidget(devicesListWidget);
    this->setWindowTitle("Система эмуляции работы электронных устройств");
    this->setMinimumSize(640, 480);
}

MainWindow::~MainWindow()
{

}
