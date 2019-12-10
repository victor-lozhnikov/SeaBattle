#include <iostream>
#include "RandomPlay.h"

RandomPlay::RandomPlay(GameView &_gameView) {
    gameView = _gameView;
}

void RandomPlay::selectName() {
    std::string name;
    bool ok = false;
    while (!ok) {
        gameView.clearScreen();
        std::cout << "Введите имя игрока: ";
        getline(std::cin, name, '\n');
        if (!name.empty()) {
            gamer.setName(name);
            ok = true;
        }
    }
    bot.setName("Компьютер");
}

void RandomPlay::gameProccess() {
        selectName();
    while (true) {
        gameView.setShips(gamer);
        bot.randomSetShips();
        int move = 0;
        while (!gamer.isKilled() && !bot.isKilled()) {
            if (move == 0) {
                move = (move + !gameView.move(gamer, bot)) % 2;
            } else {
                move = (move + !gameView.randomMove(bot, gamer)) % 2;
            }
        }

        if (!gamer.isKilled()) {
            gamer.addWin();
            if (!gameView.printWinner(gamer, bot)) {
                break;
            }
        } else {
            bot.addWin();
            if (!gameView.printWinner(bot, gamer)) {
                break;
            }
        }

        gamer.removeAll();
        bot.removeAll();
    }
}
