#ifndef SEABATTLE_RANDOMPLAY_H
#define SEABATTLE_RANDOMPLAY_H


#include "Gamer.h"
#include "GameView.h"

class RandomPlay {
public:
    RandomPlay(GameView &_gameView);
    void selectName();
    void gameProccess();

private:
    GameView gameView;
    Gamer gamer;
    Gamer bot;
};


#endif //SEABATTLE_RANDOMPLAY_H
