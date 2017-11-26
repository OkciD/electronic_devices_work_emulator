#include "emulationwidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QSignalMapper>
#include <QDebug>

EmulationWidget::EmulationWidget(int deviceId, QWidget *parent) : QWidget(parent)
{
    device_ = models::ModelsManager::instance().getDevice(deviceId);
    choosenSocketWidget_ = nullptr;

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 20);

    int rowsInGrid = 0;
    QVector<QVector<models::Socket *>> ioSockets = {device_.getSockets(models::SocketType::INPUT),
                                                  device_.getSockets(models::SocketType::OUTPUT)};
    QVector<QVector<SocketWidget *> *> socketWidgets = {&inputSocketsWidgets_, &outputSocketWidgets_};
    QSignalMapper *signalMapper = new QSignalMapper;

    for (QVector<QVector<models::Socket *>>::iterator ioSocketsIterator = ioSockets.begin();
         ioSocketsIterator != ioSockets.end();
         ioSocketsIterator++)
    {
        for (QVector<models::Socket *>::iterator socketsIterator = ioSocketsIterator->begin();
             socketsIterator != ioSocketsIterator->end();
             socketsIterator++, rowsInGrid++)
        {
            mainLayout->addWidget(new QLabel((*socketsIterator)->getName()), rowsInGrid, 0);

            SocketWidget *newSocketWidget =  new SocketWidget(*socketsIterator);
            signalMapper->setMapping(newSocketWidget, rowsInGrid);
            connect(newSocketWidget, SIGNAL(signalAdded()), signalMapper, SLOT(map()));
            socketWidgets[ioSocketsIterator - ioSockets.begin()]->append(newSocketWidget);
            if ((*socketsIterator)->getType() == "out")
            {
                newSocketWidget->setDisabled(true);
            }
            mainLayout->addWidget(newSocketWidget, rowsInGrid, 1);
        }
    }

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(onSignalAdded_(int)));
    this->setLayout(mainLayout);
}

void EmulationWidget::onSignalAdded_(int clickedSocketWidgetId)
{
    qDebug() << inputSocketsWidgets_[clickedSocketWidgetId]->getSocket()->getName();
}
