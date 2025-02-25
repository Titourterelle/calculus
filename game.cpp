#include "game.h"

#include <random>

#include <QIntValidator>

Game::Game(QWidget *parent)
    : QWidget{parent}
{
    gameLayout = new QVBoxLayout(this);

    calculLabel = new QLabel(this);
    entryEdit = new QLineEdit(this);

    gameLayout->addWidget(calculLabel);
    gameLayout->addWidget(entryEdit);

    entryEdit->setValidator(new QIntValidator(0, 999, entryEdit));
}

void Game::initSettings(const std::vector<int> &tables, const TimeLimit &timeLimit) noexcept
{
    activeTables = tables;
    timeLimitSelect = timeLimit;
}

void Game::nextCalcul() noexcept
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> distGeneral(1, 10);
    std::uniform_int_distribution<int> distTables(0, activeTables.size() - 1);

    int facteur1 = distTables(gen);
    int facteur2 = distGeneral(gen);
    goodAnswer = facteur1*facteur2;
}
