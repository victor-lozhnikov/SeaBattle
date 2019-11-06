#include <iostream>
#include <sstream>
#include "GameView.h"

void GameView::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void GameView::printField(const Gamer &gamer, bool enemy) {
    auto field = gamer.getField();
    std::cout << "   ";
    for (int i = 0; i < 10; ++i) {
        std::cout << (char)('A' + i) << " ";
    }
    std::cout << "\n";
    for (int i = 1; i <= 10; ++i) {
        std::cout << i - 1 << "  ";
        for (int j = 1; j <= 10; ++j) {
            if (field[i][j] > 0) {
                std::cout << 'o';
            }
            else if (field[i][j] == 2) {
                std::cout << 'x';
            }
            else {
                std::cout << '.';
            }
            std::cout << " ";
        }
        std::cout << '\n';
    }
}

void GameView::setShips(Gamer gamer) {
    while (!gamer.isReady()) {
        clearScreen();
        std::cout << "Игрок " << gamer.getName() << " расставляет корабли.\n\n";
        printField(gamer);
        std::cout << "\nВам доступны следующие корабли:\n"
                     "oooo - " << gamer.getAvailableShips(4) << " шт.\n"
                     "ooo  - " << gamer.getAvailableShips(3) << " шт.\n"
                     "oo   - " << gamer.getAvailableShips(2) << " шт.\n"
                     "o    - " << gamer.getAvailableShips(1) << " шт.\n";
        std::cout << "\nВведите начальную и конечную координаты вашего корабля "
                     "(например: \"g5 g7\")\n"
                     "Если вы хотите сбросить расстановку кораблей, введите \"r\"\n"
                     "Если вы хотите расставить корабли случайным образом, нажмите \"g\"\n";
        std::string inp;
        getline(std::cin, inp);
        std::vector<std::string> inpVector;
        std::istringstream ss(inp);
        std::string tmpString;
        while (ss >> tmpString) {
            inpVector.push_back(tmpString);
        }
        if (inpVector.size() > 2 || inpVector.empty()) {
            continue;
        }
        else if (inpVector.size() == 1) {
            if (inp[0] == 'r') {
                gamer.removeAll();
                continue;
            }
            if (inp[0] == 'g') {
                gamer.randomSetShips();
                continue;
            }
            inpVector.push_back(inpVector[0]);
        }
        gamer.addShip(inpVector[0], inpVector[1]);
    }

    clearScreen();
    std::cout << "Игрок " << gamer.getName() << " расставляет корабли.\n\n";
    printField(gamer);
    std::cout << "\nНажмите ENTER";
    std::cin.get();
}