#include "mainwindow.h"
#include "devicebutton.h"
#include "emulationwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    dockWidget_ = new DockWidget;
    categoriesListWidget_ = new CategoriesListWidget;
    devicesListWidget_ = new DevicesListWidget;

    connect(&categoriesListWidget_->getSignalMapper(), SIGNAL(mapped(int)),
            devicesListWidget_, SLOT(showDevicesInCategory(int)));
    connect(&devicesListWidget_->getWidgetSignalMapper(), SIGNAL(mapped(QWidget*)),
            this, SLOT(changeDockWidget_(QWidget *)));
    connect(&devicesListWidget_->getDeviceSignalMapper(), SIGNAL(mapped(int)),
            this, SLOT(showEmulationScreen_(int)));

    dockWidget_->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockWidget_->setWidget(categoriesListWidget_);
    this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_);
    this->setCentralWidget(devicesListWidget_);

    this->setWindowTitle("Система эмуляции работы электронных устройств");
    this->setMinimumSize(mainMenuSize_);
    this->setMaximumSize(mainMenuSize_);
}

void MainWindow::changeDockWidget_(QWidget *clickedDeviceButton)
{
    DeviceButton *deviceButton = static_cast<DeviceButton *>(clickedDeviceButton);
    deviceButton->hideFrame();
    dockWidget_->setWidget(deviceButton);
}

void MainWindow::showEmulationScreen_(int deviceId)
{
//    delete this->centralWidget();
    this->setCentralWidget(new EmulationWidget(deviceId));
}

MainWindow::~MainWindow()
{
    delete categoriesListWidget_;
    delete devicesListWidget_;
    delete dockWidget_;
}
