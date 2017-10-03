#ifndef DEVICESLISTWIDGET_H
#define DEVICESLISTWIDGET_H

#include <QWidget>
#include <QGridLayout>

class DevicesListWidget: public QWidget
{
    Q_OBJECT

public:
    DevicesListWidget(QWidget *parent = 0);

public slots:
    void showDevicesInCategory(int categoryId);

private:
    void clear_();
    QGridLayout *mainLayout_;
};

#endif // DEVICESLISTWIDGET_H
