#ifndef CATEGORIESLISTWIDGET_H
#define CATEGORIESLISTWIDGET_H

#include <QDockWidget>
#include <QSignalMapper>


class CategoriesListWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit CategoriesListWidget(QWidget *parent = nullptr);
    const QSignalMapper &getSignalMapper() const;

private:
    QSignalMapper signalMapper_;

signals:

public slots:
};

#endif // CATEGORIESLISTWIDGET_H
