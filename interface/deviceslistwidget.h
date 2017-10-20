#ifndef DEVICESLISTWIDGET_H
#define DEVICESLISTWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QSignalMapper>

class DevicesListWidget: public QWidget
{
    Q_OBJECT

public:
    DevicesListWidget(QWidget *parent = 0);
    const QSignalMapper &getWidgetSignalMapper() const;
    const QSignalMapper &getDeviceSignalMapper() const;

public slots:
    void showDevicesInCategory(int categoryId);

private:
    void clear_();
    QGridLayout *mainLayout_;
    QSignalMapper widgetSignalMapper_;
    QSignalMapper deviceSignalMapper_;
};

#endif // DEVICESLISTWIDGET_H
