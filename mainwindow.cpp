#include "mainwindow.h"
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    showFullScreen();
    setCentralWidget(menuStackedWidget);

    startLayout->addWidget(difficultyWidget);
    startLayout->addWidget(timeWidget);
    startLayout->addWidget(startButton);

    for(auto i = 0; i < 10; ++i)
    {
        tables[i] = new QCheckBox(QString("Table de %1").arg(i+1), difficultyWidget);
        difficultyLayout->addWidget(tables[i]);
        tables[i]->setChecked(true);
    }

    /*timeGroup->addButton(longTime);
    timeGroup->addButton(normalTime);
    timeGroup->addButton(shortTime);
    timeGroup->addButton(noTime);*/

    timeLayout->addWidget(longTime);
    timeLayout->addWidget(normalTime);
    timeLayout->addWidget(shortTime);
    timeLayout->addWidget(noTime);

    normalTime->setChecked(true);

    startButton->setText("Jouer");

    menuStackedWidget->addWidget(startPage);
    menuStackedWidget->addWidget(gamePage);


}

MainWindow::~MainWindow() {}
