#include "mainwindow.h"
#include <QCheckBox>
#include <QIntValidator>
#include <QPushButton>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);

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

    timeGroup->addButton(noTime, 0);
    timeGroup->addButton(shortTime, 1);
    timeGroup->addButton(normalTime, 2);
    timeGroup->addButton(longTime, 3);

    timeLayout->addWidget(noTime);
    timeLayout->addWidget(shortTime);
    timeLayout->addWidget(normalTime);
    timeLayout->addWidget(longTime);

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

void MainWindow::startGame()
{
    bool oneIsChecked = false;
    activeTables.clear();
    for(auto i = 0; i < tables.size(); ++i)
    {
        if(tables[i]->isChecked())
        {
            oneIsChecked = true;
            activeTables.insert(i+1);
        }
    }

    int id = timeGroup->checkedId();
    if(oneIsChecked && id != -1)
    {
        timeLimitSelect = static_cast<time>(id);
        menuStackedWidget->setCurrentIndex(1);
    }
}
