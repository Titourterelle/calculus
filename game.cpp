#include "game.h"

#include <random>

#include <QIntValidator>

#include <QDebug>

Game::Game(QWidget *parent)
    : QWidget{parent}
{
    gameLayout = new QVBoxLayout(this);

    calculLabel = new QLabel(this);
    entryEdit = new QLineEdit(this);

    gameLayout->addWidget(calculLabel);
    gameLayout->addWidget(entryEdit);

    entryEdit->setValidator(new QIntValidator(0, 999, entryEdit));

    connect(entryEdit, &QLineEdit::returnPressed, this, &Game::answerVerif);
}

void Game::initGame(const std::vector<int> &tables, const TimeLimit &timeLimit) noexcept
{
    activeTables = tables;
    timeLimitSelect = timeLimit;
    currentScore = {10, 0, 0};
    nextCalcul();
}

void Game::nextCalcul() noexcept
{
    if(currentScore.isFinished())
    {
        emit gameFinished(currentScore);
        return;
    }
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distTables(0, activeTables.size() - 1);
    static std::uniform_int_distribution<int> distGeneral(1, 10);

    int facteur1 = activeTables[distTables(gen)];
    int facteur2 = distGeneral(gen);
    goodAnswer = facteur1*facteur2;

    calculLabel->setText(QString("%1 x %2").arg(facteur1).arg(facteur2));
}

void Game::answerVerif() noexcept
{
    currentScore.calculsMade++;
    if(entryEdit->text().toInt() == goodAnswer)
    {
        //TODO : Affichage réussite
        qDebug() << "Bravo";
        currentScore.goodAnswers++;
    }
    else
    {
        //TODO : Affichage échec
        qDebug() << "Dommage";
    }
    entryEdit->clear();
    nextCalcul();
}
