#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "simonlogic.h"

/**
 * Author: Yiliang Shi && Qixiang Chao
 */
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_redButton_clicked();

    void on_blueButton_clicked();

    void on_startButton_clicked();

    void newUserRound();
    


public slots:
    void gameOver(int highScore);
    void showPattern(QList<int> list, int frequency);
    void updateScore(int score);
    void updateProgress(int progress);

signals:
    void newInput(int input);

private:
    Ui::MainWindow *ui;
    SimonLogic game;
    void reset();
    void newComputerRound();
    int currentScore;

};

#endif // MAINWINDOW_H
