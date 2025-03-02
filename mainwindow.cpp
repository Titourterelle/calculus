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
    scoreLabel->setObjectName("score");

    correctionWidget = new QWidget(scorePage);
    correctionLayout = new QGridLayout(correctionWidget);
    correctionLayout->setSpacing(100);

    scoreButtonsWidget = new QWidget(scorePage);
    replayLayout = new QHBoxLayout(scoreButtonsWidget);
    replayLayout->setSpacing(100);

    replayButton = new QPushButton("REJOUER", scoreButtonsWidget);
    menuButton = new QPushButton("MENU", scoreButtonsWidget);
    replayButton->setMinimumSize(700, 80);
    menuButton->setMinimumSize(700, 80);

    replayLayout->addWidget(replayButton);
    replayLayout->addWidget(menuButton);

    scoreLayout->addWidget(scoreLabel, 0, Qt::AlignCenter);
    scoreLayout->addWidget(correctionWidget, 0, Qt::AlignCenter);
    scoreLayout->addWidget(scoreButtonsWidget, 0, Qt::AlignBottom);

    //Menu
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);

    connect(gamePage, &Game::gameFinished, this, &MainWindow::onGameFinished);

    connect(replayButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(menuButton, &QPushButton::clicked, this, [this](){menuStackedWidget->setCurrentIndex(0);});

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

    while (correctionLayout->count() > 0)
    {
        QWidget *widget = correctionLayout->itemAt(0)->widget();
        if (widget) {
            correctionLayout->removeWidget(widget);
            delete widget;
        }
    }
}

void MainWindow::onGameFinished(const Score &finalScore, const std::map<std::string, bool> &calculs) noexcept
{
    scoreLabel->setText(QString("%1 / %2").arg(finalScore.goodAnswers).arg(finalScore.calculsMade));

    int i = 0;
    for(const auto &[calcul, success] : calculs)
    {
        QLabel *calculLabel = new QLabel(QString::fromStdString(calcul), correctionWidget);
        calculLabel->setObjectName("correction");
        calculLabel->setStyleSheet(success ? "color: #2F8D46;" : "color: #D62828;");
        correctionLayout->addWidget(calculLabel, i/5, i%5);
        ++i;
    }
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
