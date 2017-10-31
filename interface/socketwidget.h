#ifndef SOCKETWIDGET_H
#define SOCKETWIDGET_H

#include <QFrame>
#include <QPainter>
#include <QMouseEvent>

class SocketWidget : public QFrame
{
    Q_OBJECT
public:
    explicit SocketWidget(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    int highLevelHeight_;
    int lowLevelHeight_;
    QVector<QPoint> signalPoints_;

    void updateLevelHeights_();
};

#endif // SOCKETWIDGET_H
