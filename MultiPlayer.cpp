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
    while (true) {
        gameView.setShips(gamer1);
        gameView.setShips(gamer2);
        int move = 0;
        Gamer *cur;
        Gamer *enemy;
        while (!gamer1.isKilled() && !gamer2.isKilled()) {
            if (move == 0) {
                cur = &gamer1;
                enemy = &gamer2;
            } else {
                cur = &gamer2;
                enemy = &gamer1;
            }

            move = (move + !gameView.move(*cur, *enemy)) % 2;
        }

        if (!gamer1.isKilled()) {
            gamer1.addWin();
            if (!gameView.printWinner(gamer1, gamer2)) {
                break;
            }
        }
        else {
            gamer2.addWin();
            if (!gameView.printWinner(gamer2, gamer1)) {
                break;
            }
        }

        gamer1.removeAll();
        gamer2.removeAll();
    }
}

MultiPlayer::MultiPlayer(GameView &_gameView) {
    gameView = _gameView;
}