#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QHBoxLayout *navigationLayout = new QHBoxLayout;
    QPushButton *chooseButton = new QPushButton("Выбор устройства"), *guideButton = new QPushButton("Учебник");

    chooseButton->setObjectName("mainMenuButton");
    guideButton->setObjectName("mainMenuButton");

    navigationLayout->addWidget(chooseButton);
    navigationLayout->addWidget(guideButton);

    QWidget *navigationWidget = new QWidget();
    navigationWidget->setLayout(navigationLayout);

    this->setCentralWidget(navigationWidget);
    this->setWindowTitle("Система эмуляции работы электронных устройств");
    this->setMinimumSize(640, 480);
}

MainWindow::~MainWindow()
{

}
