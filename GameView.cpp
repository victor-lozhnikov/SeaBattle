#include <iostream>
#include <sstream>
#include "GameView.h"
#include "MultiPlayer.h"
#include "RandomPlay.h"
#include "SmartPlay.h"
#include "optionparser.h"

/*
 -1 - недоступна для расстановки
 0 - пустая
 1 - занята кораблем
 2 - прострелена
 3 - простреленный корабль
 4 - убитый корабль
*/

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


        if (type[0] == '1') {
            MultiPlayer multiPlayer(gameView);
            multiPlayer.gameProccess();
            isStarted = true;
        }
        else if (type[0] == '2') {
            RandomPlay randomPlay(gameView);
            randomPlay.gameProccess();
            isStarted = true;
        }
        else if (type[0] == '3') {
            SmartPlay smartPlay(gameView);
            smartPlay.gameProccess();
            isStarted = true;
        }
    }
}

void GameView::printField(const Gamer &gamer, bool enemy, int cur_x, int cur_y) {
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

void GameView::setShips(Gamer &gamer) {
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
            else {
                gamer.addShip(inpVector[0], inpVector[0]);
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

bool GameView::move (Gamer &cur, Gamer &enemy) {
    bool ok = false;
    int shotRes = -1;
    int x, y;
    while (!ok) {
        clearScreen();
        std::cout << "Ходит игрок " << cur.getName() << "\n\n";
        printField(enemy, true);
        std::cout << "\nВведите координаты точки, в которую вы хотите выстрелить (например \"g5\")\n";
        std::string inp;
        getline(std::cin, inp);
        if (inp.size() != 2) {
            continue;
        }
        inp[0] = tolower(inp[0]);
        shotRes = enemy.shot(inp, &x, &y);
        if (shotRes == -1) {
            continue;
        }
        clearScreen();
        std::cout << "Ходит игрок " << cur.getName() << "\n\n";
        printField(enemy, true, x, y);
        std::cout << "\nНажмите ENTER\n";
        std::cin.get();
        ok = true;
    }
    return (shotRes == 1);
}

bool GameView::randomMove(Gamer &cur, Gamer &enemy) {
    clearScreen();
    std::cout << "Ходит игрок " << cur.getName() << "\n\n";
    int x, y;
    bool shotRes = enemy.randomMove(&x, &y);
    printField(enemy, true, x, y);
    std::cout << "\nНажмите ENTER\n";
    std::cin.get();
    return shotRes;
}

bool GameView::smartMove(Gamer &cur, Gamer &enemy) {
    clearScreen();
    std::cout << "Ходит игрок " << cur.getName() << "\n\n";
    int x, y;
    bool shotRes = enemy.smartMove(&x, &y);
    printField(enemy, true, x, y);
    std::cout << "\nНажмите ENTER\n";
    std::cin.get();
    return shotRes;
}

bool GameView::printWinner(const Gamer &winner, const Gamer &loser) {
    while (true) {
        clearScreen();
        std::cout << "Игрок " << winner.getName() << " победил!\n\n";
        std::cout << "Количество побед:\n";
        if (loser.getWinCount() > winner.getWinCount()) {
            std::cout << loser.getName() << " : " << loser.getWinCount() << "\n";
            std::cout << winner.getName() << " : " << winner.getWinCount() << "\n";
        } else {
            std::cout << winner.getName() << " : " << winner.getWinCount() << "\n";
            std::cout << loser.getName() << " : " << loser.getWinCount() << "\n";
        }
        std::cout << "\nХотите сыграть еще раз?\n"
                     "Введите \"y\", если да, \"n\", если нет.\n";
        std::string inp;
        getline(std::cin, inp);
        if (inp.size() == 1) {
            inp[0] = tolower(inp[0]);
            if (inp[0] == 'y') {
                return true;
            }
            if (inp[0] == 'n') {
                return false;
            }
        }
    }
}