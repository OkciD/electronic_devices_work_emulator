#ifndef SOCKETWIDGET_H
#define SOCKETWIDGET_H

#include <QFrame>
#include <QPainter>
#include <QMouseEvent>
#include <models/socket.h>

class SocketWidget : public QFrame
{
    Q_OBJECT
public:
    explicit SocketWidget(models::Socket * const socket, QWidget *parent = nullptr);
    models::Socket *getSocket() const;
    const QVector<QPoint> &getSignalPoints() const;
    const QString getSignalState(int time);
    int getTimesSignalChanges(int time);

signals:
    void signalAdded();

public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    int highLevelHeight_;
    int lowLevelHeight_;
    QVector<QPoint> signalPoints_;
    models::Socket *socket_;
    int lastCalculatedSignalIndex;

    void updateLevelHeights_();
};

#endif // SOCKETWIDGET_H
