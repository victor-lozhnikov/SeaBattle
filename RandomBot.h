#ifndef SEABATTLE_RANDOMBOT_H
#define SEABATTLE_RANDOMBOT_H


#include "Gamer.h"
#include "GameView.h"

class RandomBot {
public:
    RandomBot(GameView &_gameView);
    void selectName();
    void gameProccess();

private:
    GameView gameView;
    Gamer gamer;
    Gamer bot;
};


#endif //SEABATTLE_RANDOMBOT_H
