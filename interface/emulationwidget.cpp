#include "emulationwidget.h"

#include <QVBoxLayout>
#include <QLabel>

EmulationWidget::EmulationWidget(int deviceId, QWidget *parent) : QWidget(parent)
{
    device_ = models::ModelsManager::instance().getDevice(deviceId);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel(device_.getFullName()));

    this->setLayout(mainLayout);
}
