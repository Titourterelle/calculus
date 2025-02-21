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
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>

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

    //Start Page Widget
    QVBoxLayout *startLayout = new QVBoxLayout(startPage);

    QLabel *difficultyLabel = new QLabel("Tables Activées", startPage);

    QWidget *difficultyWidget = new QWidget(startPage);
    QGridLayout *difficultyLayout = new QGridLayout(difficultyWidget);

    std::array<QCheckBox*, 10> tables;

    QLabel *timeLabel = new QLabel("Limite de Temps", startPage);

    QWidget *timeWidget = new QWidget(startPage);
    QHBoxLayout *timeLayout = new QHBoxLayout(timeWidget);

    //QButtonGroup *timeGroup = new QButtonGroup(timeWidget);
    QRadioButton *longTime = new QRadioButton("Long", timeWidget);
    QRadioButton *normalTime = new QRadioButton("Normal", timeWidget);
    QRadioButton *shortTime = new QRadioButton("Court", timeWidget);
    QRadioButton *noTime = new QRadioButton("Sans", timeWidget);

    QPushButton *startButton = new QPushButton(startPage);

    //Game Page Widget
    QVBoxLayout *gameLayout = new QVBoxLayout(gamePage);

    QLabel *calculLabel = new QLabel(gamePage);
    QLineEdit *entryEdit = new QLineEdit(gamePage);
};
#endif // MAINWINDOW_H
