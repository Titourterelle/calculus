#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>

#include <vector>
#include <map>
#include <string>

#include "timeLimit.h"
#include "score.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = nullptr);
    void initGame(const std::vector<int> &tables, const TimeLimit &timeLimit) noexcept;
signals:
    void gameFinished(const Score &finalScore, const std::map<std::string, bool> &calculs);
private slots:
    void answerVerif() noexcept;
private:
    void nextCalcul() noexcept;

    QVBoxLayout *gameLayout;

    QLabel *calculLabel;
    QLineEdit *entryEdit;

    int goodAnswer;
    Score currentScore;
    std::map<std::string, bool> calculs;
    std::string currentCalcul;
    std::vector<int> activeTables;

    QTimer *questionTimer;
    TimeLimit timeLimitSelect;
    int timeInSecond;
};

#endif // GAME_H
