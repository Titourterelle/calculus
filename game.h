#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include <vector>

#include "timeLimit.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = nullptr);
    void initSettings(const std::vector<int> &tables, const TimeLimit &timeLimit) noexcept;
signals:
private:
    void nextCalcul() noexcept;

    QVBoxLayout *gameLayout;

    QLabel *calculLabel;
    QLineEdit *entryEdit;

    int goodAnswer;
    std::vector<int> activeTables;
    TimeLimit timeLimitSelect;
};

#endif // GAME_H
