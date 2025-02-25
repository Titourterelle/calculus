#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <array>
#include <vector>

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    const std::vector<int>& getTables() const noexcept;
    const TimeLimit& getTimeLimit() const noexcept;

public slots:
    void startGame() noexcept;
private:
    QStackedWidget *menuStackedWidget;
    QWidget *startPage;
    Game *gamePage;

    //Start Page Widget
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

    QPushButton *startButton;

    std::array<QCheckBox*, 10> tables;
    std::vector<int> activeTables;

    TimeLimit timeLimitSelect = TimeLimit::Normal;


};
#endif // MAINWINDOW_H
