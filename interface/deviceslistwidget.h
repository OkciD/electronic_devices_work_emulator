#ifndef DEVICESLISTWIDGET_H
#define DEVICESLISTWIDGET_H

#include <QWidget>

class DevicesListWidget: public QWidget
{
    Q_OBJECT

public:
    DevicesListWidget(QWidget *parent = 0);

public slots:
    void showDevicesInCategory(int categoryId);

private:
    void clear_();
};

#endif // DEVICESLISTWIDGET_H
