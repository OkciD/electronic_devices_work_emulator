#include "deviceslistwidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "models/modelsmanager.h"
#include "devicebutton.h"

const int itemsPerRow = 3;

DevicesListWidget::DevicesListWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout_ = new QGridLayout;

    mainLayout_->addWidget(new QLabel("Выберите категорию"), 0, 0);
    mainLayout_->setObjectName("mainLayout");

    this->setLayout(mainLayout_);
}

void DevicesListWidget::showDevicesInCategory(int categoryId)
{
    QVector<models::Device> devices = models::ModelsManager::instance()
            .getDevicesInCategory(categoryId);

    clear_();
    if ( devices.length() == 0 )
    {
        mainLayout_->addWidget(new QLabel("Нет устройств"));
        return;
    }
    else
    {
        int i = 0;

        for (QVector<models::Device>::iterator iterator = devices.begin();
             iterator != devices.end();
             ++i)
        {
            for (int j = 0; (j < itemsPerRow) && (iterator != devices.end()); iterator++, ++j )
            {
                DeviceButton *newDeviceButton = new DeviceButton(*iterator);

                signalMapper_.setMapping(newDeviceButton,
                                         /*static_cast<QWidget *>(*/newDeviceButton/*)*/);
                connect(newDeviceButton, SIGNAL(clicked()), &signalMapper_, SLOT(map()));

                mainLayout_->addWidget(newDeviceButton, i, j);
            }
        }
        mainLayout_->setRowStretch(itemsPerRow, 1);
    }
}

void DevicesListWidget::clear_()
{
    // https://stackoverflow.com/questions/10716300/removing-qwidgets-from-a-qgridlayout

    mainLayout_->setRowStretch(itemsPerRow, 0);
    for (; mainLayout_->count() > 0 ;)
    {
        delete mainLayout_->itemAt(0)->widget();
    }
}

const QSignalMapper &DevicesListWidget::getSignalMapper() const
{
    return signalMapper_;
}
