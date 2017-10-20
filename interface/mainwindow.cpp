#include "mainwindow.h"
#include "devicebutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    dockWidget_ = new DockWidget;
    categoriesListWidget_ = new CategoriesListWidget;
    devicesListWidget_ = new DevicesListWidget;

    connect(&categoriesListWidget_->getSignalMapper(), SIGNAL(mapped(int)),
            devicesListWidget_, SLOT(showDevicesInCategory(int)));
    connect(&devicesListWidget_->getSignalMapper(), SIGNAL(mapped(QWidget*)),
            this, SLOT(changeToEmulationScreen_(QWidget *)));

    dockWidget_->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockWidget_->setWidget(categoriesListWidget_);

    this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_);
    this->setCentralWidget(devicesListWidget_);
    this->setWindowTitle("Система эмуляции работы электронных устройств");
    this->setMinimumSize(640, 480);
    this->setMaximumSize(640, 480);
}

void MainWindow::changeToEmulationScreen_(QWidget *clickedDeviceButton)
{
    DeviceButton *deviceButton = static_cast<DeviceButton *>(clickedDeviceButton);
    deviceButton->hideFrame();
    dockWidget_->setWidget(deviceButton);
}

MainWindow::~MainWindow()
{
    delete categoriesListWidget_;
    delete devicesListWidget_;
    delete dockWidget_;
}
