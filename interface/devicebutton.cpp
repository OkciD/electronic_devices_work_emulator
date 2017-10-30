#include "devicebutton.h"

#include <QVBoxLayout>
#include <QLabel>

DeviceButton::DeviceButton(const models::Device &device, QWidget *parent) : QFrame(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(device.getImage());
    mainLayout->addWidget(imageLabel);

    mainLayout->addWidget(new QLabel(device.getFullName()));
    mainLayout->addWidget(new QLabel(device.getShortName()));

    mainLayout->setAlignment(Qt::AlignCenter);

    this->setLayout(mainLayout);

    this->setFrameShape(QFrame::Box);
    this->setLineWidth(1);

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Foreground, QColor(200, 200, 200));
    this->setPalette(*palette);
}

void DeviceButton::hideFrame()
{
    this->setFrameShape(QFrame::NoFrame);
}

void DeviceButton::mousePressEvent(QMouseEvent *event)
{
    QFrame::mousePressEvent(event);

    emit clicked();
}
