#include <iostream>
#include "RandomBot.h"

RandomBot::RandomBot(GameView &_gameView) {
    gameView = _gameView;
}

void RandomBot::selectName() {
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

void RandomBot::gameProccess() {
    selectName();
    gameView.setShips(&gamer);
    bot.randomSetShips();
    int move = 0;
    while (!gamer.isKilled() && !bot.isKilled()) {
        if (move == 0) {
            move = (move + !gameView.move(gamer, bot)) % 2;
        }
        else {
            move = (move + !gameView.randomMove(bot, gamer)) % 2;
        }
    }

    if (!gamer.isKilled()) {
        gameView.printWinner(gamer);
    }
    else {
        gameView.printWinner(bot);
    }
}
