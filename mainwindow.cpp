#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QHBoxLayout *navigationLayout = new QHBoxLayout;
    QPushButton *sampleButton = new QPushButton("Здесь могли бы быть кнопки с выбором устройств");

    sampleButton->setObjectName("mainMenuButton");

    navigationLayout->addWidget(sampleButton);

    QWidget *navigationWidget = new QWidget();
    navigationWidget->setLayout(navigationLayout);

    this->setCentralWidget(navigationWidget);
    this->setWindowTitle("Система эмуляции работы электронных устройств");
    this->setMinimumSize(640, 480);
}

MainWindow::~MainWindow()
{

}
