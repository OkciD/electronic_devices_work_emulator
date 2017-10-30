#include "socketwidget.h"

SocketWidget::SocketWidget(QWidget *parent) : QFrame(parent)
{
    this->setFrameShape(QFrame::Box);
    this->setLineWidth(2);

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Foreground, QColor(200, 200, 200));
    this->setPalette(*palette);
}

void SocketWidget::updateLevelHeights_() {
    lowLevelHeight_ = 0.2 * this->height();
    highLevelHeight_ = 0.8 * this->height();
}

void SocketWidget::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);

    QPainter painter(this);

    // redraw low and high lines
    updateLevelHeights_();
    painter.setPen(QPen(Qt::gray, 1, Qt::DashLine));
    painter.drawLine(0, lowLevelHeight_, this->width(), lowLevelHeight_);
    painter.drawLine(0, highLevelHeight_, this->width(), highLevelHeight_);
}
