#include "mainwindow.h"

#include <QToolTip>
#include <QEvent>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    menuStackedWidget = new QStackedWidget(this);
    startPage = new QWidget(menuStackedWidget);
    gamePage = new Game(menuStackedWidget);
    scorePage = new QWidget(menuStackedWidget);

    //Start Page
    startLayout = new QVBoxLayout(startPage);

    difficultyLabel = new QLabel("TABLES ACTIVÉES", startPage);
    difficultyLabel->setObjectName("title");

    difficultyWidget = new QWidget(startPage);
    difficultyLayout = new QGridLayout(difficultyWidget);
    difficultyLayout->setHorizontalSpacing(200);
    difficultyLayout->setVerticalSpacing(50);

    for(auto i = 0; i < 10; ++i)
    {
        tables[i] = new QCheckBox(QString("Table de %1").arg(i+1), difficultyWidget);
        difficultyLayout->addWidget(tables[i], i/5, i%5);
        tables[i]->setChecked(true);
    }

    timeLabel = new QLabel("LIMITE DE TEMPS", startPage);
    timeLabel->setObjectName("title");

    timeWidget = new QWidget(startPage);
    timeLayout = new QHBoxLayout(timeWidget);
    timeLayout->setSpacing(100);

    timeGroup = new QButtonGroup(timeWidget);
    noTime = new QRadioButton("Sans", timeWidget);
    shortTime = new QRadioButton("Court", timeWidget);
    normalTime = new QRadioButton("Normal", timeWidget);
    longTime = new QRadioButton("Long", timeWidget);

    noTime->installEventFilter(this);
    shortTime->installEventFilter(this);
    normalTime->installEventFilter(this);
    longTime->installEventFilter(this);

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
    startButton->setText("JOUER");
    startButton->setMinimumSize(1000, 80);

    startLayout->addWidget(difficultyLabel, 0, Qt::AlignHCenter);
    startLayout->addWidget(difficultyWidget, 0, Qt::AlignHCenter);
    startLayout->addWidget(timeLabel, 0, Qt::AlignHCenter);
    startLayout->addWidget(timeWidget, 0, Qt::AlignHCenter);
    startLayout->addWidget(startButton, 0, Qt::AlignCenter);

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

void MainWindow::onGameFinished(Score finalScore) noexcept
{
    scoreLabel->setText(QString("%1 / %2").arg(finalScore.goodAnswers).arg(finalScore.calculsMade));
    menuStackedWidget->setCurrentIndex(2);
}

void MainWindow::showToolTip(QString text) noexcept
{
    QToolTip::showText(QCursor::pos(), text);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter)
    {
        if(watched == noTime)
        {
            showToolTip("Illimité");
        }
        else if(watched == shortTime)
        {
            showToolTip("10 secondes");
        }
        else if(watched == normalTime)
        {
            showToolTip("15 secondes");
        }
        else if(watched == longTime)
        {
            showToolTip("20 secondes");
        }
    }
    if (event->type() == QEvent::Leave)
    {
        QToolTip::hideText();
    }
    return QMainWindow::eventFilter(watched, event);
}
