#include "dockwidget.h"

#include <QFrame>

DockWidget::DockWidget(QWidget *parent) : QDockWidget(parent)
{
    QWidget *mainWidget = new QWidget;
    mainLayout_ = new QGridLayout;

    QFrame *dividingFrame = new QFrame;
    dividingFrame->setFrameShape(QFrame::VLine);
    dividingFrame->setLineWidth(1);

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Foreground, QColor(200, 200, 200));
    dividingFrame->setPalette(*palette);

    mainLayout_->addWidget(dividingFrame, 0, 1);

    mainWidget->setLayout(mainLayout_);
    QDockWidget::setWidget(mainWidget);
}

void DockWidget::setWidget(QWidget *widget)
{
    clearLayout_();
    mainLayout_->addWidget(widget, 0, 0);
}

void DockWidget::clearLayout_()
{
    if ( mainLayout_->count() > 1 )
    {
        delete mainLayout_->itemAt(1)->widget();
    }
}



