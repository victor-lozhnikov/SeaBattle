#ifndef SEABATTLE_GAMEPLAY_H
#define SEABATTLE_GAMEPLAY_H


#include "Gamer.h"
#include "GameView.h"

class GamePlay {
public:
    GamePlay(int gamer1_type, int gamer2_type, int _count);
    void startGame();
private:
    Gamer* gamer1;
    Gamer* gamer2;
    int count;
};


#endif //SEABATTLE_GAMEPLAY_H
