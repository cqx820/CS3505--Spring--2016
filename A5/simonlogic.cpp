#include "simonlogic.h"
#include <cstdlib>
/**
 * @brief SimonLogic::SimonLogic
 * @Author: Yiliang Shi && Qixiang Chao
 */
SimonLogic::SimonLogic()
{
    highScore=0;
    score=0;
    playerInputCount=0;
    frequency=1000;
    srand(5232);
}

void SimonLogic::addToPattern()
{
    //Random number generator, between 0 and 1
    pattern.append(rand()%2);
}


void SimonLogic::startGame()
{
    score=0;
    playerInputCount=0;
    frequency=1000;
    pattern.clear();
    addToPattern();//Add first pattern
    addToPattern();
    emit updateScore(score);
    emit newPattern(pattern, frequency);
}

void SimonLogic::newUserInput(int input)
{
    //If user click right button, then move to next
    if(input==pattern[playerInputCount])
    {
        playerInputCount++;
        emit updateProgress((int)(playerInputCount*100/pattern.size()));
    }
    else
    {
        emit updateScore(0);
        //Else, emit the signal to indicate losing
        if(score>highScore)
            highScore=score;
        emit loss(highScore);
    }
    //Starting new round
    if(playerInputCount==pattern.size()){
        playerInputCount=0;
        score+=pattern.size()*100;
        //The flasing frequency would be faster in every new term
        if(frequency>300)
            frequency-=100;
        emit updateScore(score);

        addToPattern();
        emit newPattern(pattern,frequency);
    }

}


