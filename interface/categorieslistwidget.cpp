#include "categorieslistwidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <models/modelsmanager.h>

CategoriesListWidget::CategoriesListWidget(QWidget *parent) : QDockWidget(parent)
{
    this->setObjectName("mainMenuWidget");

    QWidget *mainWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addStretch();
    QVector<models::Category> categories = models::ModelsManager::instance().getCategories();
    for ( QVector<models::Category>::iterator iterator = categories.begin();
          iterator != categories.end();
          iterator++ )
    {
        mainLayout->addWidget(new QPushButton(iterator->getName()));
    }
    mainLayout->addStretch();

    mainWidget->setLayout(mainLayout);
    this->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->setWidget(mainWidget);
}
