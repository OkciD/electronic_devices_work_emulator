#ifndef EMULATIONWIDGET_H
#define EMULATIONWIDGET_H

#include <QWidget>
#include "models/modelsmanager.h"

class EmulationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmulationWidget(int deviceId, QWidget *parent = nullptr);

private:
    models::Device device_;

signals:

public slots:
};

#endif // EMULATIONWIDGET_H
