#include "deviceslistwidget.h"

#include <QHBoxLayout>
#include <QLabel>

DevicesListWidget::DevicesListWidget()
{
    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addWidget(new QLabel("Устройства в категории"));
    mainLayout->addStretch();

    this->setLayout(mainLayout);
}
