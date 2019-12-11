#include "GamePlay.h"
#include "ConsoleGamer.h"
#include "SmartGamer.h"
#include "RandomGamer.h"

GamePlay::GamePlay(int gamer1_type, int gamer2_type, int _count) {
    count = _count;
    switch (gamer1_type) {
        case 1:
            gamer1 = new ConsoleGamer(1);
            break;
        case 2:
            gamer1 = new RandomGamer(1);
            break;
        case 3:
            gamer1 = new SmartGamer(1);
            break;
        default:
            gamer1 = new ConsoleGamer(1);
            break;
    }
    switch (gamer2_type) {
        case 1:
            gamer2 = new ConsoleGamer(2);
            break;
        case 2:
            gamer2 = new RandomGamer(2);
            break;
        case 3:
            gamer2 = new SmartGamer(2);
            break;
        default:
            gamer2 = new ConsoleGamer(2);
            break;
    }
}

void GamePlay::startGame() {
    gamer1->selectName();
    gamer2->selectName();
    while (count--) {
        gamer1->setShips();
        gamer2->setShips();
        bool firstPlayerMove = true;
        Gamer *cur;
        Gamer *enemy;
        while (!gamer1->isKilled() && !gamer2->isKilled()) {
            if (firstPlayerMove) {
                cur = gamer1;
                enemy = gamer2;
            } else {
                cur = gamer2;
                enemy = gamer1;
            }

            firstPlayerMove ^= !cur->move(*enemy);
        }

        GameView::printWinner(*gamer1, *gamer2, count);

        /*if (!gamer1->isKilled()) {
            gamer1->addWin();
            GameView::printWinner(*gamer1, *gamer2, count);
        }
        else {
            gamer2->addWin();
            GameView::printWinner(*gamer2, *gamer1, count);
        }*/
        gamer1->removeAll();
        gamer2->removeAll();
    }
}