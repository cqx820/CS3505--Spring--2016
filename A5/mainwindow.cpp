#include <QTimer>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simonlogic.h"
#include <QSound>
/**
 * @brief MainWindow::MainWindow
 * @param parent
 * @Author: Yiliang Shi && Qixiang Chao
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Connection building
    connect(ui->startButton, &QPushButton::clicked ,&game, &SimonLogic::startGame );
    connect(&game, &SimonLogic::newPattern, this, &MainWindow::newComputerRound );
    connect(&game, &SimonLogic::newPattern, this, &MainWindow::showPattern );
    connect(this, &MainWindow::newInput,&game, &SimonLogic::newUserInput);
    connect(&game, &SimonLogic::updateScore, this, &MainWindow::updateScore );
    connect(&game, &SimonLogic::updateProgress, this, &MainWindow::updateProgress );
    connect(&game, &SimonLogic::loss, this, &MainWindow::gameOver);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_redButton_clicked()
{
    ui->redButton->setStyleSheet("background-color: red");
    QTimer::singleShot(50, this,[&](){ui->redButton->setStyleSheet("background-color: transparent; border: 1px solid gray");
                                        ui->blueButton->setStyleSheet("background-color: transparent; border: 1px solid gray");});
    emit newInput(0);
    QSound::play(":/E.wav");
}

void MainWindow::on_blueButton_clicked()
{
    ui->blueButton->setStyleSheet("background-color: blue");
    QTimer::singleShot(100, this,[&](){ui->redButton->setStyleSheet("background-color: transparent; border: 1px solid gray");
                                        ui->blueButton->setStyleSheet("background-color: transparent; border: 1px solid gray");});
    emit newInput(1);
    QSound::play(":/G.wav");
}

void MainWindow::on_startButton_clicked()
{
    ui->startButton->setText("Restart");
    ui->turnLable->setText("Computer");
}

void MainWindow::gameOver(int highScore)
{
    QMessageBox msgBox;
    QString text = "Your highest score is: " + QString::number(highScore);
    msgBox.setText("Game over - you lose!\n" + text);
    msgBox.exec();
    newComputerRound();
    ui->startButton->setText("Start");
    ui->progressBar->setFormat(QString::number(0) +"%");
}
void MainWindow::showPattern(QList<int> list,int frequency)
{
    ui->progressBar->setFormat(QString::number(0) +"%");
    int wait=frequency;
    //Reading pattern and show on GUI
    for(int i=0;i<list.size();i++)
    {
        if(list[i]==0)
            QTimer::singleShot(wait, this, [&](){ui->redButton->setStyleSheet("background-color: red");
                                                    QSound::play(":/E.wav");});
        else
            QTimer::singleShot(wait, this, [&](){ui->blueButton->setStyleSheet("background-color: blue");
                                                     QSound::play(":/G.wav");});
        wait+=frequency;
        QTimer::singleShot(wait, this,[&](){ui->redButton->setStyleSheet("background-color: transparent; border: 1px solid gray");
                                            ui->blueButton->setStyleSheet("background-color: transparent; border: 1px solid gray");});
        wait+=frequency;
    }
    QTimer::singleShot(wait, this,SLOT(newUserRound()));
}



void MainWindow::updateProgress(int progress)
{
    ui->progressBar->setValue(progress);
    ui->progressBar->setFormat(QString::number(progress)+"%");
}

void MainWindow::newComputerRound()
{
    ui->progressBar->setValue(0);
    ui->blueButton->setEnabled(false);
    ui->redButton->setEnabled(false);
    ui->turnLable->setText("Computer");
}

void MainWindow::newUserRound()
{
    ui->blueButton->setEnabled(true);
    ui->redButton->setEnabled(true);
    ui->turnLable->setText("User");
}

void MainWindow::reset()
{
    ui->scoreLable->setText("Score: 0");
    ui->redButton->setStyleSheet("background-color: transparent; border: 2px solid black");
    ui->blueButton->setStyleSheet("background-color: transparent; border: 2px solid black");
    ui->startButton->setText("Restart");
    newComputerRound();
}

void MainWindow::updateScore(int score)
{
    QString text = "Score: "+QString::number(score);
    this->currentScore = score;
    ui->scoreLable->setText(text);
}
