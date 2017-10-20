#include "categorieslistwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QPalette>
#include "models/modelsmanager.h"
#include <QPushButton>

CategoriesListWidget::CategoriesListWidget(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("mainMenuWidget");

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

    mainLayout->addLayout(categoriesLayout);

    this->setLayout(mainLayout);
}

const QSignalMapper &CategoriesListWidget::getSignalMapper() const
{
    return signalMapper_;
}
