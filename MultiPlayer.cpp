#include <iostream>
#include "MultiPlayer.h"
#include "GameView.h"

void MultiPlayer::selectNames() {
    std::string name1, name2;
    bool ok = false;
    while (!ok) {
        gameView.clearScreen();
        std::cout << "Введите имя первого игрока: ";
        getline(std::cin, name1, '\n');
        if (!name1.empty()) {
            gamer1.setName(name1);
            ok = true;
        }
    }
    ok = false;
    while (!ok) {
        gameView.clearScreen();
        std::cout << "Введите имя второго игрока: ";
        getline(std::cin, name2, '\n');
        if (!name2.empty() && name2 != name1) {
            gamer2.setName(name2);
            ok = true;
        }
    }

}

void MultiPlayer::gameProccess() {
    selectNames();
    gameView.setShips(gamer1);
    gameView.setShips(gamer2);

}

MultiPlayer::MultiPlayer(GameView _gameView) {
    gameView = _gameView;
}