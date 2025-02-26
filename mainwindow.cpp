#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    menuStackedWidget = new QStackedWidget(this);
    startPage = new QWidget(menuStackedWidget);
    gamePage = new Game(menuStackedWidget);
    scorePage = new QWidget(menuStackedWidget);

    //Start Page
    startLayout = new QVBoxLayout(startPage);

    difficultyLabel = new QLabel("Tables Activées", startPage);

    difficultyWidget = new QWidget(startPage);
    difficultyLayout = new QGridLayout(difficultyWidget);

    for(auto i = 0; i < 10; ++i)
    {
        tables[i] = new QCheckBox(QString("Table de %1").arg(i+1), difficultyWidget);
        difficultyLayout->addWidget(tables[i], i/5, i%5);
        tables[i]->setChecked(true);
    }

    timeLabel = new QLabel("Limite de Temps", startPage);

    timeWidget = new QWidget(startPage);
    timeLayout = new QHBoxLayout(timeWidget);

    timeGroup = new QButtonGroup(timeWidget);
    longTime = new QRadioButton("Long", timeWidget);
    normalTime = new QRadioButton("Normal", timeWidget);
    shortTime = new QRadioButton("Court", timeWidget);
    noTime = new QRadioButton("Sans", timeWidget);

    timeGroup->addButton(noTime, 0);
    timeGroup->addButton(shortTime, 1);
    timeGroup->addButton(normalTime, 2);
    timeGroup->addButton(longTime, 3);

    normalTime->setChecked(true);

    timeLayout->addWidget(noTime);
    timeLayout->addWidget(shortTime);
    timeLayout->addWidget(normalTime);
    timeLayout->addWidget(longTime);

    startButton = new QPushButton(startPage);
    startButton->setText("Jouer");

    startLayout->addWidget(difficultyLabel);
    startLayout->addWidget(difficultyWidget);
    startLayout->addWidget(timeLabel);
    startLayout->addWidget(timeWidget);
    startLayout->addWidget(startButton);

    //Score Page
    scoreLayout = new QVBoxLayout(scorePage);
    scoreLabel = new QLabel(scorePage);

    scoreLayout->addWidget(scoreLabel);

    //Menu
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(gamePage, &Game::gameFinished, this, &MainWindow::onGameFinished);

    showFullScreen();
    setCentralWidget(menuStackedWidget);

    menuStackedWidget->addWidget(startPage);
    menuStackedWidget->addWidget(gamePage);
    menuStackedWidget->addWidget(scorePage);

    menuStackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow() {}

const std::vector<int>& MainWindow::getTables() const noexcept
{
    return activeTables;
}

const TimeLimit& MainWindow::getTimeLimit() const noexcept
{
    return timeLimitSelect;
}

void MainWindow::startGame() noexcept
{
    activeTables.clear();
    for(auto i = 0; i < tables.size(); ++i)
    {
        if(tables[i]->isChecked())
        {
            activeTables.push_back(i+1);
        }
    }

    int id = timeGroup->checkedId();
    if(activeTables.size() != 0 && id != -1)
    {
        timeLimitSelect = static_cast<TimeLimit>(id);
        gamePage->initGame(getTables(), getTimeLimit());
        menuStackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::onGameFinished(Score finalScore)
{
    scoreLabel->setText(QString("%1 / %2").arg(finalScore.goodAnswers).arg(finalScore.calculsMade));
    menuStackedWidget->setCurrentIndex(2);
}
