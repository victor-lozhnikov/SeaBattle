#ifndef SEABATTLE_GAMEVIEW_H
#define SEABATTLE_GAMEVIEW_H


#include "Gamer.h"

class GameView {
public:
    void clearScreen();
    void printField (const Gamer &gamer, bool enemy = false);
    void setShips (Gamer gamer);
    void startScreen();
};


#endif //SEABATTLE_GAMEVIEW_H
