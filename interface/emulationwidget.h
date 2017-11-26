#ifndef EMULATIONWIDGET_H
#define EMULATIONWIDGET_H

#include <QWidget>
#include "models/modelsmanager.h"
#include "socketwidget.h"

class EmulationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmulationWidget(int deviceId, QWidget *parent = nullptr);

private:
    models::Device device_;
    QVector<SocketWidget *> inputSocketsWidgets_, outputSocketWidgets_;
    SocketWidget *choosenSocketWidget_;

signals:

private slots:
    void onSignalAdded_(int clickedSocketWidgetId);
};

#endif // EMULATIONWIDGET_H
