#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <array>
#include <vector>
#include <map>
#include <string>

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>

#include "game.h"
#include "timeLimit.h"
#include "score.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    const std::vector<int>& getTables() const noexcept;
    const TimeLimit& getTimeLimit() const noexcept;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void startGame() noexcept;
    void onGameFinished(const Score &finalScore, const std::map<std::string, bool> &calculs) noexcept;
private:
    void showToolTip(QString text) noexcept;

    QStackedWidget *menuStackedWidget;
    QWidget *menuPage;
    QWidget *startPage;
    Game *gamePage;
    QWidget *scorePage;

    //Menu Page
    QVBoxLayout *menuLayout;

    QLabel *titleLabel; // A REMPLACER PAR UN LOGO (si possible)
    QPushButton *startPageButton;
    QPushButton *quitButton;

    //Start Page
    QVBoxLayout *startLayout;

    QLabel *difficultyLabel;

    QWidget *difficultyWidget;
    QGridLayout *difficultyLayout;

    QLabel *timeLabel;

    QWidget *timeWidget;
    QHBoxLayout *timeLayout;

    QButtonGroup *timeGroup;
    QRadioButton *longTime;
    QRadioButton *normalTime;
    QRadioButton *shortTime;
    QRadioButton *noTime;

    QWidget *playButtonsWidget;
    QHBoxLayout *playButtonsLayout;
    QPushButton *playButton;
    QPushButton *returnMenuButton;

    std::array<QCheckBox*, 10> tables;
    std::vector<int> activeTables;

    TimeLimit timeLimitSelect = TimeLimit::Normal;

    //Score Page
    QVBoxLayout *scoreLayout;

    QLabel *scoreLabel;

    QWidget *correctionWidget;
    QGridLayout *correctionLayout;

    QWidget *scoreButtonsWidget;
    QHBoxLayout *replayLayout;
    QPushButton *replayButton;
    QPushButton *menuButton;

};
#endif // MAINWINDOW_H
