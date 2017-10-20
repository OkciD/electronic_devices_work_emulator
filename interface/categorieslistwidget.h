#ifndef CATEGORIESLISTWIDGET_H
#define CATEGORIESLISTWIDGET_H

#include <QWidget>
#include <QSignalMapper>

class CategoriesListWidget : public QWidget
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
