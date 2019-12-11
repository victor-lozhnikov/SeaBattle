#include <iostream>
#include <sstream>
#include "GameView.h"
#include "optionparser.h"
#include "GamePlay.h"
#include "ConsoleGamer.h"
#include "RandomGamer.h"
#include "SmartGamer.h"

void GameView::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void GameView::printHelp() {
    std::cout << "Добро пожаловать в игру Морской Бой.\n\n";
    std::cout << "В данной версии реализованы три варианта игры:\n"
                 "1. Интерактивная сессия (console) - за игрока играет пользователь\n"
                 "2. Случайная стратегия (random) - все решения случайные\n"
                 "3. Оптимальная стратегия (smart) - расстановка кораблей и последующие ходы оптимизированы на выигрыш\n\n";

    std::cout << "Параметры запуска программы включают в себя (короткое и полное имя, порядок не важен):\n"
                 "1. -h --help - печать сообщения со списком параметров программы и завершение работы\n"
                 "2. -c --count \n"
                 "   Default: 1, количество раундов в серии\n"
                 "3. -f --first\n"
                 "   Default: random, тип первого игрока\n"
                 "4. -s --second\n"
                 "   Default: random, тип второго игрока\n\n";

    std::cout << "Приятной игры!\n\nНажмите ENTER\n";
    std::cin.get();
}

void GameView::printField(const Gamer &gamer, bool enemy, int cur_x, int cur_y) {
/*
 -1 - недоступна для расстановки
 0 - пустая
 1 - занята кораблем
 2 - прострелена
 3 - простреленный корабль
 4 - убитый корабль
*/
    auto field = gamer.getField();
    std::cout << "   ";
    for (int i = 0; i < 10; ++i) {
        std::cout << (char)('A' + i) << " ";
    }
    std::cout << "\n";
    for (int i = 1; i <= 10; ++i) {
        std::cout << i - 1 << "  ";
        for (int j = 1; j <= 10; ++j) {
            if (i == cur_x && j == cur_y) {
                std::cout << "\x1b[1;33m";
            }
            else if (field[i][j] > 2) {
                std::cout << "\x1b[1;34m";
            }
            if (field[i][j] < 1) {
                std::cout << '.';
            }
            else if ((field[i][j] == 1 && !enemy) || (field[i][j] == 3)) {
                std::cout << 'o';
            }
            else if (field[i][j] == 4) {
                std::cout << "O";
            }
            else if (field[i][j] == 2) {
                std::cout << 'x';
            }
            else {
                std::cout << '.';
            }
            if ((i == cur_x && j == cur_y) || field[i][j] > 2) {
                std::cout << "\x1b[0m";
            }
            //std::cout << field[i][j];
            std::cout << " ";
        }
        std::cout << '\n';
    }
}

void GameView::printWinner(Gamer &gamer1, Gamer &gamer2, int count) {
    clearScreen();
    if (!gamer1.isKilled()) {
        std::cout << "Игрок 1 (" << gamer1.getName() << ") победил!\n\n";
        gamer1.addWin();
    } else {
        std::cout << "Игрок 2 (" << gamer2.getName() << ") победил!\n\n";
        gamer2.addWin();
    }

    std::cout << "Количество побед:\n";
    std::cout << "Игрок 1 (" << gamer1.getName() << ") : " << gamer1.getWinCount() << "\n";
    std::cout << "Игрок 2 (" << gamer2.getName() << ") : " << gamer2.getWinCount() << "\n";

    std::cout << "\nОсталось игр: " << count << " \n\nНажмите ENTER\n";
    std::cin.get();
}