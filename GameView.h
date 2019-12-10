#ifndef SEABATTLE_GAMEVIEW_H
#define SEABATTLE_GAMEVIEW_H


#include "Gamer.h"

class GameView {
public:
    void clearScreen();
    void printField (const Gamer &gamer, bool enemy = false);
    void setShips (Gamer* gamer);
    void startScreen();
    bool move(Gamer* cur, Gamer* enemy);
    void printWinner (const Gamer &winner);
};


#endif //SEABATTLE_GAMEVIEW_H
