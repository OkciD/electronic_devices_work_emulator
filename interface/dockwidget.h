#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>
#include <QGridLayout>

class DockWidget : public QDockWidget
{
public:
    DockWidget(QWidget *parent = 0);
    void setWidget(QWidget *widget);

private:
    void clearLayout_();
    QGridLayout *mainLayout_;
};

#endif // DOCKWIDGET_H
