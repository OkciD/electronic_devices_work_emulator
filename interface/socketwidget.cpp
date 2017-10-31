#include "socketwidget.h"
#include <QDebug>

SocketWidget::SocketWidget(QWidget *parent) : QFrame(parent)
{
    this->setFrameShape(QFrame::Box);
    this->setLineWidth(2);

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Foreground, QColor(200, 200, 200));
    this->setPalette(*palette);
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
    if (signalPoints_.empty())
    {
        signalPoints_.append(*(new QPoint(0, lowLevelHeight_)));
    }
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

    // drawing signal lines
    painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
    QVector<QPoint> linePoints;
    linePoints.append(*signalPoints_.begin());
    for (QVector<QPoint>::iterator signalPointsIterator = signalPoints_.begin() + 1;
         signalPointsIterator != signalPoints_.end();
         signalPointsIterator++)
    {
        if (signalPointsIterator->y() != (signalPointsIterator - 1)->y())
        {
            linePoints.append(*(new QPoint((signalPointsIterator - 1)->x(), signalPointsIterator->y())));
            linePoints.append(*(new QPoint(signalPointsIterator->x(), signalPointsIterator->y())));
        }
        else
        {
            linePoints.append(*signalPointsIterator);
        }
    }

    painter.drawPolyline(linePoints);
}

void SocketWidget::mousePressEvent(QMouseEvent *event)
{
    QFrame::mousePressEvent(event);

    if (event->x() <= signalPoints_.last().x())
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
            signalPoints_.append(*(new QPoint(event->x(), *levelHeightsIterator)));
            break;
        }
    }

    this->update();
}
