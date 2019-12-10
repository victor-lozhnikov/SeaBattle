#ifndef SEABATTLE_GAMEVIEW_H
#define SEABATTLE_GAMEVIEW_H

#include "Gamer.h"

class GameView {
public:
    void clearScreen();
    void printField (const Gamer &gamer, bool enemy = false, int cur_x = -1, int cur_y = -1);
    void setShips (Gamer &gamer);
    void startScreen();
    bool move(Gamer &cur, Gamer &enemy);
    bool randomMove(Gamer &cur, Gamer &enemy);
    bool smartMove (Gamer &cur, Gamer &enemy);
    bool printWinner (const Gamer &winner, const Gamer &loser);
};


#endif //SEABATTLE_GAMEVIEW_H
