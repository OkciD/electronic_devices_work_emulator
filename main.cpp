#include "interface/mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QFile styleFile;

    styleFile.setFileName(":/qss/styles.css");
    styleFile.open(QFile::ReadOnly);
    QString qssString = styleFile.readAll();
    styleFile.close();

    a.setStyleSheet(qssString);

    return a.exec();
}
