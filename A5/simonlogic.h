#ifndef SIMONLOGIC_H
#define SIMONLOGIC_H
#include <QObject>
#include <QList>
/**
 * @brief The SimonLogic class
 * @Author: Yiliang Shi && Qixiang Chao
 */
class SimonLogic : public QObject
{
    Q_OBJECT
private:
    int score;
    int highScore;
    int playerInputCount;
    //List contains the random generated patterns
    QList<int> pattern;
    //The frequency of button flash
    int frequency;
    void addToPattern();
public:
    SimonLogic();
public slots:
    void startGame();
    void newUserInput(int input);
signals:
    void loss(int highScore);
    void newPattern(QList<int> list,int frequency);
    void updateScore(int score);
    //Progress bar signals
    void updateProgress(int percent);
};

#endif // SIMONLOGIC_H
