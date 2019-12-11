#include <iostream>
#include "RandomGamer.h"
#include "GameView.h"

RandomGamer::RandomGamer(int _order):
        Gamer(_order){}

void RandomGamer::selectName() {
    setName("Глупый компьютер");
}

void RandomGamer::setShips() {
    randomSetShips();
}

bool RandomGamer::move(Gamer &enemy) {
    GameView::clearScreen();
    std::cout << "Ходит игрок " << getOrder() << " (" << getName() << ")\n\n";
    int x, y;
    bool shotRes = enemy.randomMove(&x, &y);
    GameView::printField(enemy, true, x, y);
    std::cout << "\nНажмите ENTER\n";
    std::cin.get();
    return shotRes;
}
