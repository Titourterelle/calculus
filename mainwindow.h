#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <array>

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QRadioButton>
//#include <QButtonGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QStackedWidget *menuStackedWidget = new QStackedWidget(this);
    QWidget *startPage = new QWidget(menuStackedWidget);
    QWidget *gamePage = new QWidget(menuStackedWidget);

    QHBoxLayout *startLayout = new QHBoxLayout(startPage);

    QWidget *difficultyWidget = new QWidget(startPage);
    QVBoxLayout *difficultyLayout = new QVBoxLayout(difficultyWidget);

    std::array<QCheckBox*, 10> tables;

    QWidget *timeWidget = new QWidget(startPage);
    QVBoxLayout *timeLayout = new QVBoxLayout(timeWidget);

    //QButtonGroup *timeGroup = new QButtonGroup(timeWidget);
    QRadioButton *longTime = new QRadioButton("Long", timeWidget);
    QRadioButton *normalTime = new QRadioButton("Normal", timeWidget);
    QRadioButton *shortTime = new QRadioButton("Court", timeWidget);
    QRadioButton *noTime = new QRadioButton("Sans", timeWidget);

    QPushButton *startButton = new QPushButton(startPage);
};
#endif // MAINWINDOW_H
