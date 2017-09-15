#include "categorieslistwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QPalette>
#include "models/modelsmanager.h"
#include <QPushButton>

CategoriesListWidget::CategoriesListWidget(QWidget *parent) : QDockWidget(parent)
{
    this->setObjectName("mainMenuWidget");

    QWidget *mainWidget = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *categoriesLayout = new QVBoxLayout;

    categoriesLayout->addStretch();
    QVector<models::Category> categories = models::ModelsManager::instance().getCategories();
    for ( QVector<models::Category>::iterator iterator = categories.begin();
          iterator != categories.end();
          iterator++ )
    {
        QPushButton *newButton = new QPushButton(iterator->getName());

        signalMapper_.setMapping(newButton, iterator->getId());
        connect(newButton, SIGNAL(clicked()), &signalMapper_, SLOT(map()));

        categoriesLayout->addWidget(newButton);
    }
    categoriesLayout->addStretch();

    QFrame *dividingFrame = new QFrame;
    dividingFrame->setFrameShape(QFrame::VLine);
    dividingFrame->setLineWidth(1);

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Foreground, QColor(200, 200, 200));
    dividingFrame->setPalette(*palette);

    mainLayout->addLayout(categoriesLayout);
    mainLayout->addWidget(dividingFrame);

    mainWidget->setLayout(mainLayout);
    this->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->setWidget(mainWidget);
}

const QSignalMapper &CategoriesListWidget::getSignalMapper() const
{
    return signalMapper_;
}
