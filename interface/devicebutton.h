#ifndef DEVICEBUTTON_H
#define DEVICEBUTTON_H

#include <QFrame>
#include <QMouseEvent>
#include "models/modelsmanager.h"

class DeviceButton : public QFrame
{
    Q_OBJECT

public:
    DeviceButton(const models::Device &device);

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();
};

#endif // DEVICEBUTTON_H
