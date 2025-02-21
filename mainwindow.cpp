#include "mainwindow.h"
#include <QCheckBox>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    showFullScreen();
    setCentralWidget(menuStackedWidget);

    //Start Page
    startLayout->addWidget(difficultyLabel);
    startLayout->addWidget(difficultyWidget);
    startLayout->addWidget(timeLabel);
    startLayout->addWidget(timeWidget);
    startLayout->addWidget(startButton);

    for(auto i = 0; i < 10; ++i)
    {
        tables[i] = new QCheckBox(QString("Table de %1").arg(i+1), difficultyWidget);
        difficultyLayout->addWidget(tables[i], i/5, i%5);
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

    //Game Page
    gameLayout->addWidget(calculLabel);
    gameLayout->addWidget(entryEdit);

    entryEdit->setValidator(new QIntValidator(0, 999, entryEdit));

    //Menu
    menuStackedWidget->addWidget(startPage);
    menuStackedWidget->addWidget(gamePage);

    menuStackedWidget->setCurrentIndex(0);


}

MainWindow::~MainWindow() {}
