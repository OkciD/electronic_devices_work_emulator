#ifndef SOCKETWIDGET_H
#define SOCKETWIDGET_H

#include <QFrame>
#include <QPainter>

class SocketWidget : public QFrame
{
    Q_OBJECT
public:
    explicit SocketWidget(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);

private:
    int lowLevelHeight_;
    int highLevelHeight_;
    QVector<QPair<int, int>> signalPoints_;

    void updateLevelHeights_();
};

#endif // SOCKETWIDGET_H
