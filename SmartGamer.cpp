#include <iostream>
#include "SmartGamer.h"
#include "GameView.h"

SmartGamer::SmartGamer(int _order):
        Gamer(_order){}

void SmartGamer::selectName() {
    setName("Умный компьютер");
}

void SmartGamer::setShips() {
    smartSetShips();
}

bool SmartGamer::move(Gamer &enemy) {
    GameView::clearScreen();
    std::cout << "Ходит игрок " << getOrder() << " (" << getName() << ")\n\n";
    int x, y;
    bool shotRes = enemy.smartMove(&x, &y);
    GameView::printField(enemy, true, x, y);
    std::cout << "\nНажмите ENTER\n";
    std::cin.get();
    return shotRes;
}