#include "emulationwidget.h"

#include <QGridLayout>
#include <QLabel>

#include "socketwidget.h"

EmulationWidget::EmulationWidget(int deviceId, QWidget *parent) : QWidget(parent)
{
    device_ = models::ModelsManager::instance().getDevice(deviceId);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 20);

    QVector<models::Socket> sockets = device_.getInputSockets() + device_.getOutputSockets();

    for (QVector<models::Socket>::iterator socketsIterator = sockets.begin();
         socketsIterator != sockets.end();
         socketsIterator++)
    {
        mainLayout->addWidget(new QLabel(socketsIterator->getName()), socketsIterator - sockets.begin(), 0);
        mainLayout->addWidget(new SocketWidget(), socketsIterator - sockets.begin(), 1);
    }

    this->setLayout(mainLayout);
}
