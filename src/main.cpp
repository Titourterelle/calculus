#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QFile file(":/assets/style.qss");
    if (file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        a.setStyleSheet(stream.readAll());
        file.close();
    }

    MainWindow w;
    w.show();
    return a.exec();
}
