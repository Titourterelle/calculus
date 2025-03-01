#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QFile file(":/assets/style.qss");
    if (file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        a.setStyleSheet(stream.readAll());
        file.close();
    } else {
        qDebug() << "Erreur : Impossible d'ouvrir style.qss";
    }

    MainWindow w;
    w.show();
    return a.exec();
}
