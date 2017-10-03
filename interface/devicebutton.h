#ifndef DEVICEBUTTON_H
#define DEVICEBUTTON_H

#include <QFrame>
#include "models/modelsmanager.h"

class DeviceButton : public QFrame
{
    Q_OBJECT

public:
    DeviceButton(const models::Device &device);
};

#endif // DEVICEBUTTON_H
