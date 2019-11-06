#include <iostream>
#include <sstream>
#include "GameView.h"
#include "MultiPlayer.h"

void GameView::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void GameView::startScreen() {
    bool isStarted = false;
    GameView gameView;
    while (!isStarted) {
        gameView.clearScreen();
        std::cout << "Добро пожаловать в игру Морской Бой.\n\n"
                "Выберите тип игры:\n"
                "1. Два игрока\n"
                "2. Игра против глупого компьютера\n"
                "3. Игра против умного компьютера\n\n"
                "Введите одно число от 1 до 3 - номер выбранного типа игры: ";
        std::string type;
        getline(std::cin, type);
        if (type.size() > 1) {
            continue;
        }
        gameView.clearScreen();
        MultiPlayer multiPlayer(gameView);
        switch (type[0]) {
            case '1':
                multiPlayer.gameProccess();
                isStarted = true;
                break;
            case '2':
                std::cout << "Выбран тип 2";
                isStarted = true;
                break;
            case '3':
                std::cout << "Выбран тип 3";
                isStarted = true;
                break;
            default:
                break;
        }
    }
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
            inp[0] = tolower(inp[0]);
            if (inp[0] == 'r') {
                gamer.removeAll();
            }
            if (inp[0] == 'g') {
                gamer.randomSetShips();
            }
        }
        else {
            gamer.addShip(inpVector[0], inpVector[1]);
        }

        if (!gamer.isReady()) {
            continue;
        }

        bool ok = false;
        while (!ok) {
            clearScreen();
            std::cout << "Игрок " << gamer.getName() << " расставляет корабли.\n\n";
            printField(gamer);
            std::cout << "\nЕсли вас устраивает данная расстановка, введите \"y\"\n"
                         "Если вы хотите сбросить расстановку кораблей, введите \"r\"\n"
                         "Если вы хотите расставить корабли случайным образом, нажмите \"g\"\n";
            std::string inp;
            getline(std::cin, inp);
            if (inp.size() == 1) {
                inp[0] = tolower(inp[0]);
                if (inp[0] == 'y') {
                    ok = true;
                }
                if (inp[0] == 'r') {
                    gamer.removeAll();
                    ok = true;
                }
                if (inp[0] == 'g') {
                    gamer.removeAll();
                    gamer.randomSetShips();
                }
            }
        }
    }
}