#ifndef SEABATTLE_SMARTPLAY_H
#define SEABATTLE_SMARTPLAY_H


#include "GameView.h"

class SmartPlay {
public:
    SmartPlay(GameView &_gameView);
    void selectName();
    void gameProccess();

private:
    GameView gameView;
    Gamer gamer;
    Gamer bot;
};


#endif //SEABATTLE_SMARTPLAY_H
