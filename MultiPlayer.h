#ifndef SEABATTLE_MULTIPLAYER_H
#define SEABATTLE_MULTIPLAYER_H

#include "Gamer.h"
#include "GameView.h"

class MultiPlayer {
public:
    explicit MultiPlayer(GameView &_gameView);
    void gameProccess();
    void selectNames();

private:
    GameView gameView;
    Gamer gamer1;
    Gamer gamer2;
};


#endif //SEABATTLE_MULTIPLAYER_H
