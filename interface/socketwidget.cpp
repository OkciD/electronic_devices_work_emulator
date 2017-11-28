#include "socketwidget.h"
#include <QDebug>

SocketWidget::SocketWidget(models::Socket * const socket, QWidget *parent) :
    QFrame(parent), socket_(socket), lastCalculatedSignalIndex_(0)
{
    this->setFrameShape(QFrame::Box);
    this->setLineWidth(2);

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Foreground, QColor(200, 200, 200));
    this->setPalette(*palette);
}

models::Socket *SocketWidget::getSocket() const
{
    return socket_;
}

const QVector<QPoint> &SocketWidget::getSignalPoints() const
{
    return signalPoints_;
}

size_t SocketWidget::searchSignalPoint(const int &time)
{
    size_t firstIndex = lastCalculatedSignalIndex_, lastIndex = signalPoints_.length() - 1, middleIndex = 0;

    for (; lastIndex - firstIndex > 1 ;)
    {
        middleIndex = (firstIndex + lastIndex) / 2;

        if ( time <= signalPoints_[middleIndex].x() )
        {
            lastIndex = middleIndex;
        }
        else
        {
            firstIndex = middleIndex;
        }
    }

    return lastIndex;
}

const QString SocketWidget::getSignalState(int time)
{
    size_t nearestSignalsIndex = searchSignalPoint(time);

    return (signalPoints_[nearestSignalsIndex].y() == lowLevelHeight_) ? "0" : "1";
}

int SocketWidget::getTimesSignalChanges(int time)
{
    if (signalPoints_.empty())
    {
        return 0;
    }

    size_t nearestSignalsIndex = searchSignalPoint(time);
    int result = 0;

    QVector<QPoint>::iterator begin = signalPoints_.begin() + lastCalculatedSignalIndex_ + 1;
    for (QVector<QPoint>::iterator signalPointsIterator = begin;
         (signalPointsIterator < signalPoints_.end()) &&
         (signalPointsIterator - begin < nearestSignalsIndex);
         signalPointsIterator++)
    {
        if ((signalPointsIterator - 1)->y() != signalPointsIterator->y())
        {
            result++;
        }
    }

    return result;
}

int SocketWidget::getLastCalculatedSignalIndex() const
{
    return lastCalculatedSignalIndex_;
}

void SocketWidget::updateLastCalculatedSignalIndex(int time)
{
    lastCalculatedSignalIndex_ = searchSignalPoint(time) - 1;
}

void SocketWidget::drawSignal(int time, QString signalLevel)
{
    if (signalPoints_.empty())
    {
        signalPoints_.append(*(new QPoint(0, (signalLevel == "1") ? highLevelHeight_ : lowLevelHeight_)));
    }
    signalPoints_.append(*(new QPoint(time, (signalLevel == "1") ? highLevelHeight_ : lowLevelHeight_)));
    update();
}

void SocketWidget::updateLevelHeights_()
{
    highLevelHeight_ = 0.2 * this->height();
    lowLevelHeight_ = 0.8 * this->height();
}

void SocketWidget::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);

    updateLevelHeights_();
}

void SocketWidget::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);

    // redraw low and high lines
    updateLevelHeights_();
    painter.setPen(QPen(Qt::gray, 1, Qt::DashLine));
    painter.drawLine(0, highLevelHeight_, this->width(), highLevelHeight_);
    painter.drawLine(0, lowLevelHeight_, this->width(), lowLevelHeight_);

    if (signalPoints_.empty())
    {
        return;
    }

    // preparing vectors of points for drawing vertical signal time lines and signal level lines
    QVector<QPoint> signalLevelLinePoints;
    QVector<QPoint> signalTimeLinePoints;
    signalLevelLinePoints.append(*signalPoints_.begin());
    for (QVector<QPoint>::iterator signalPointsIterator = signalPoints_.begin() + 1;
         signalPointsIterator != signalPoints_.end();
         signalPointsIterator++)
    {
        signalTimeLinePoints.append(*(new QPoint(signalPointsIterator->x(), 0)));
        signalTimeLinePoints.append(*(new QPoint(signalPointsIterator->x(), this->height())));

        if (signalPointsIterator->y() != (signalPointsIterator - 1)->y())
        {
            signalLevelLinePoints.append(*(new QPoint((signalPointsIterator - 1)->x(), signalPointsIterator->y())));
            signalLevelLinePoints.append(*(new QPoint(signalPointsIterator->x(), signalPointsIterator->y())));
        }
        else
        {
            signalLevelLinePoints.append(*signalPointsIterator);
        }
    }
    // drawing them
    painter.setPen(QPen(Qt::red, 1, Qt::DashDotDotLine));
    painter.drawLines(signalTimeLinePoints);
    painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
    painter.drawPolyline(signalLevelLinePoints);
}

void SocketWidget::mousePressEvent(QMouseEvent *event)
{
    QFrame::mousePressEvent(event);

    if (!signalPoints_.empty() && event->x() <= signalPoints_.last().x())
    {
        return;
    }

    QVector<int> levelHeights = {highLevelHeight_, lowLevelHeight_};
    int clickAreaWidth = 0.1 * this->height();

    for (QVector<int>::iterator levelHeightsIterator = levelHeights.begin();
         levelHeightsIterator != levelHeights.end();
         levelHeightsIterator++)
    {
        if ((event->y() >= *levelHeightsIterator - clickAreaWidth) &&
                (event->y() <= *levelHeightsIterator + clickAreaWidth))
        {
            if (signalPoints_.empty())
            {
                signalPoints_.append(*(new QPoint(0, *levelHeightsIterator)));
            }
            signalPoints_.append(*(new QPoint(event->x(), *levelHeightsIterator)));
            break;
        }
    }

    this->update();

    emit(signalAdded());
}
