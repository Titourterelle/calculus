#include "game.h"

#include <random>

#include <QIntValidator>

#include <QDebug>

Game::Game(QWidget *parent)
    : QWidget{parent}
{
    gameLayout = new QVBoxLayout(this);
    gameLayout->setContentsMargins(50, 100, 50, 50);

    countdownLabel = new QLabel(this);

    calculLabel = new QLabel(this);
    calculLabel->setObjectName("calcul");

    entryEdit = new QLineEdit(this);
    entryEdit->setMinimumSize(1000, 50);
    entryEdit->setAlignment(Qt::AlignCenter);
    entryEdit->setContentsMargins(0,0,0,50);

    gameLayout->addWidget(countdownLabel, 0, Qt::AlignCenter);
    gameLayout->addWidget(calculLabel, 1, Qt::AlignCenter);
    gameLayout->addWidget(entryEdit, 0, Qt::AlignCenter);

    entryEdit->setValidator(new QIntValidator(0, 999, entryEdit));

    questionTimer = new QTimer(this);

    // Effets Sonores de réponse
    correctAnswer = new QSoundEffect(this);
    correctAnswer->setSource(QUrl::fromLocalFile(":/assets/sounds/correct-answer.wav"));

    wrongAnswer = new QSoundEffect(this);
    wrongAnswer->setSource(QUrl::fromLocalFile(":/assets/sounds/wrong-answer.wav"));


    connect(entryEdit, &QLineEdit::returnPressed, this, &Game::answerVerif);
    connect(questionTimer, &QTimer::timeout, this, &Game::updateTimer);
}

void Game::initGame(const std::vector<int> &tables, const TimeLimit &timeLimit) noexcept
{
    activeTables = tables;
    timeLimitSelect = timeLimit;

    calculs.clear();

    countdownLabel->show();
    switch (timeLimitSelect)
    {
    case TimeLimit::Low:
        timeLimitInSecond = 10;
        break;
    case TimeLimit::Normal:
        timeLimitInSecond = 15;
        break;
    case TimeLimit::High:
        timeLimitInSecond = 20;
        break;
    default:
        timeLimitInSecond = 0;
        countdownLabel->hide();
        break;
    }

    currentScore = {10, 0, 0};
    nextCalcul();
}

void Game::nextCalcul() noexcept
{
    if(currentScore.isFinished())
    {
        emit gameFinished(currentScore, calculs);
        return;
    }
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distTables(0, activeTables.size() - 1);
    static std::uniform_int_distribution<int> distGeneral(1, 10);

    do
    {
        int facteur1 = activeTables[distTables(gen)];
        int facteur2 = distGeneral(gen);
        goodAnswer = facteur1*facteur2;
        calculLabel->setText(QString("%1 x %2").arg(facteur1).arg(facteur2));
        currentCalcul = std::to_string(facteur1) + " x " + std::to_string(facteur2) + " = " + std::to_string(goodAnswer);
    } while (calculs.find(currentCalcul) != calculs.end());

    remainingTimeInSecond = timeLimitInSecond;
    if(remainingTimeInSecond != 0)
    {
        questionTimer->start(1000);
        countdownLabel->setText(QString::number(remainingTimeInSecond));
    }
}

void Game::answerVerif() noexcept
{
    questionTimer->stop();
    currentScore.calculsMade++;
    if(entryEdit->text().toInt() == goodAnswer)
    {
        correctAnswer->play();
        currentScore.goodAnswers++;
        calculs[currentCalcul] = true;
    }
    else
    {
        wrongAnswer->play();
        calculs[currentCalcul] = false;
    }
    entryEdit->clear();
    nextCalcul();
}

void Game::updateTimer() noexcept
{
    remainingTimeInSecond--;
    countdownLabel->setText(QString::number(remainingTimeInSecond));

    if(remainingTimeInSecond == 0)
    {
        answerVerif();
    }
}
