#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <logic/databasemanager.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *navigationWidget = new QWidget();
    QVBoxLayout *navigationLayout = new QVBoxLayout;
    navigationWidget->setLayout(navigationLayout);
    navigationLayout->addStretch();

    DatabaseManager databaseManager;
    QVector<QString> categories = databaseManager.getCategories();
    for ( QVector<QString>::iterator iterator = categories.begin();
          iterator != categories.end();
          iterator++)
    {
        navigationLayout->addWidget(new QPushButton(*iterator));
    }
    navigationLayout->addStretch();

    this->setCentralWidget(navigationWidget);
    this->setWindowTitle("Система эмуляции работы электронных устройств");
    this->setMinimumSize(640, 480);
    this->setObjectName("mainWindow");
}

MainWindow::~MainWindow()
{

}
