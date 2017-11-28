#include "emulationwidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QSignalMapper>
#include <QDebug>

EmulationWidget::EmulationWidget(int deviceId, QWidget *parent) : QWidget(parent)
{
    device_ = models::ModelsManager::instance().getDevice(deviceId);
    chosenSocketWidget_ = nullptr;

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

// the worst code in the history of my code, maybe ever
// idk what happens below, rly
void EmulationWidget::onSignalAdded_(int clickedSocketWidgetId)
{
    if (!chosenSocketWidget_)
    {
        chosenSocketWidget_ = inputSocketsWidgets_[clickedSocketWidgetId];
    }
    int inputtedTime = inputSocketsWidgets_[clickedSocketWidgetId]->getSignalPoints().last().x();

    // updating chosenSocketWidget
    for (QVector<SocketWidget *>::iterator inputSocketsWidgetsIterator = inputSocketsWidgets_.begin();
         inputSocketsWidgetsIterator != inputSocketsWidgets_.end();
         inputSocketsWidgetsIterator++)
    {
        if ((*inputSocketsWidgetsIterator)->getTimesSignalChanges(inputtedTime) >
                chosenSocketWidget_->getTimesSignalChanges(inputtedTime))
        {
            chosenSocketWidget_ = *inputSocketsWidgetsIterator;
        }
    }

    QVector<QPoint> chosenSignalPoints = chosenSocketWidget_->getSignalPoints();
    // cutting the last signal time of chosen signal widget if necessary
    if (inputtedTime < chosenSignalPoints.last().x())
    {
        int lastSignalLevelHeight = chosenSignalPoints.last().y();
        int lol = chosenSocketWidget_->searchSignalPoint(inputtedTime);
        chosenSignalPoints.remove(lol, chosenSignalPoints.length() - lol);
        chosenSignalPoints.append(*(new QPoint(inputtedTime, lastSignalLevelHeight)));
    } else if (inputtedTime == chosenSignalPoints.last().x()) {
        QVector<int> lastSignalTimes;
        for (QVector<SocketWidget *>::iterator inputSocketsWidgetsIterator = inputSocketsWidgets_.begin();
             inputSocketsWidgetsIterator != inputSocketsWidgets_.end();
             inputSocketsWidgetsIterator++)
        {
            if ((*inputSocketsWidgetsIterator)->getSignalPoints().empty())
            {
                return;
            }
            lastSignalTimes.append((*inputSocketsWidgetsIterator)->getSignalPoints().last().x());
        }
        int theEarliestLastSignalTime = *lastSignalTimes.begin();
        for (QVector<int>::iterator lastSignalTimesIterator = lastSignalTimes.begin();
             lastSignalTimesIterator != lastSignalTimes.end();
             lastSignalTimesIterator++)
        {
            if (*lastSignalTimesIterator < theEarliestLastSignalTime)
            {
                theEarliestLastSignalTime = *lastSignalTimesIterator;
            }
        }

        if (chosenSignalPoints.length() - 2 > chosenSocketWidget_->getLastCalculatedSignalIndex() &&
                theEarliestLastSignalTime < inputtedTime)
        {
            return;
        }

        int lastSignalLevelHeight = chosenSignalPoints.last().y();
        chosenSignalPoints.pop_back();
        chosenSignalPoints.append(*(new QPoint(theEarliestLastSignalTime, lastSignalLevelHeight)));
    }

    // signal calculation and drawing
    for (QVector<QPoint>::const_iterator signalPointsIterator = chosenSignalPoints.begin() +
         chosenSocketWidget_->getLastCalculatedSignalIndex() + 1;
         signalPointsIterator != chosenSignalPoints.end();
         signalPointsIterator++)
    {
        for (QVector<SocketWidget *>::iterator inputSocketsWidgetsIterator = inputSocketsWidgets_.begin();
             inputSocketsWidgetsIterator != inputSocketsWidgets_.end();
             inputSocketsWidgetsIterator++)
        {
            if ((*inputSocketsWidgetsIterator)->getSignalPoints().empty())
            {
                return;
            }

            (*inputSocketsWidgetsIterator)->getSocket()->
                    setCurrentCondition((*inputSocketsWidgetsIterator)->getSignalState(signalPointsIterator->x()));
            (*inputSocketsWidgetsIterator)->updateLastCalculatedSignalIndex(signalPointsIterator->x());
        }
        device_.calculateOutputSignal();
        outputSocketWidgets_[0]->drawSignal(signalPointsIterator->x(),
                                            outputSocketWidgets_[0]->getSocket()->getCurrentCondition());
    }
}
