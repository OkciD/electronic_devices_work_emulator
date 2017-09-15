#include "deviceslistwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "models/modelsmanager.h"

DevicesListWidget::DevicesListWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(new QLabel("Выберите категорию"));
    mainLayout->setObjectName("mainLayout");

    this->setLayout(mainLayout);
}

void DevicesListWidget::showDevicesInCategory(int categoryId)
{
    clear_();

    QVector<models::Device> devices = models::ModelsManager::instance().getDevicesInCategory(categoryId);

    for ( QVector<models::Device>::iterator iterator = devices.begin();
          iterator != devices.end();
          iterator++ )
    {
        this->layout()->addWidget(new QLabel(iterator->getFullName()));
    }
}

void DevicesListWidget::clear_()
{
    QWidget *widget = nullptr;
    QLayout *layout = this->layout();

    for (; (layout->count() > 0) && (widget = layout->itemAt(0)->widget()) ;)
    {
        delete widget;
    }
}
