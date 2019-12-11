#ifndef SEABATTLE_GAMEVIEW_H
#define SEABATTLE_GAMEVIEW_H

#include "Gamer.h"

class GameView {
public:
    static void clearScreen();
    static void printField (const Gamer &gamer, bool enemy = false, int cur_x = -1, int cur_y = -1);
    static void printWinner (Gamer &gamer1, Gamer &gamer2, int count);
    static void printHelp();
};


#endif //SEABATTLE_GAMEVIEW_H
