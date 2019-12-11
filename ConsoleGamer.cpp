#include <iostream>
#include <sstream>
#include "ConsoleGamer.h"
#include "GameView.h"

ConsoleGamer::ConsoleGamer(int _order):
    Gamer(_order){}

void ConsoleGamer::selectName() {
    std::string name;
    std::string _order;
    if (getOrder() == 1) {
        _order = "первого";
    }
    else {
        _order = "второго";
    }
    while (true) {
        GameView::clearScreen();
        std::cout << "Введите имя "  << _order << " игрока: ";
        getline(std::cin, name, '\n');
        if (!name.empty()) {
            setName(name);
            return;
        }
    }
}

void ConsoleGamer::setShips() {
    while (!isReady()) {
        GameView::clearScreen();
        std::cout << "Игрок " << getOrder() << " (" << getName() << ") расставляет корабли\n\n";
        GameView::printField(*this);
        std::cout << "\nВам доступны следующие корабли:\n"
                     "oooo - " << getAvailableShips(4) << " шт.\n"
                     "ooo  - " << getAvailableShips(3) << " шт.\n"
                     "oo   - " << getAvailableShips(2) << " шт.\n"
                     "o    - " << getAvailableShips(1) << " шт.\n";
        std::cout << "\nВведите начальную и конечную координаты вашего корабля "
                     "(например: \"g5 g7\")\n"
                     "Если вы хотите сбросить расстановку кораблей, введите \"r\"\n"
                     "Если вы хотите расставить корабли случайным образом, введите \"g\"\n";
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
                removeAll();
            }
            if (inp[0] == 'g') {
                randomSetShips();
            }
            else {
                addShip(inpVector[0], inpVector[0]);
            }
        }
        else {
            addShip(inpVector[0], inpVector[1]);
        }

        if (!isReady()) {
            continue;
        }

        bool ok = false;
        while (!ok) {
            GameView::clearScreen();
            std::cout << "Игрок " << getOrder() << " (" << getName() << ") расставляет корабли\n\n";
            GameView::printField(*this);
            std::cout << "\nЕсли вас устраивает данная расстановка, введите \"y\"\n"
                         "Если вы хотите сбросить расстановку кораблей, введите \"r\"\n"
                         "Если вы хотите расставить корабли случайным образом, введите \"g\"\n";
            getline(std::cin, inp);
            if (inp.size() == 1) {
                inp[0] = tolower(inp[0]);
                if (inp[0] == 'y') {
                    ok = true;
                }
                if (inp[0] == 'r') {
                    removeAll();
                    ok = true;
                }
                if (inp[0] == 'g') {
                    removeAll();
                    randomSetShips();
                }
            }
        }
    }
}

bool ConsoleGamer::move(Gamer &enemy) {
    bool ok = false;
    int shotRes = -1;
    int x, y;
    while (!ok) {
        GameView::clearScreen();
        std::cout << "Ходит игрок " << getOrder() << " (" << getName() << ")\n\n";
        GameView::printField(enemy, true);
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
        GameView::clearScreen();
        std::cout << "Ходит игрок " << getOrder() << " (" << getName() << ")\n\n";
        GameView::printField(enemy, true, x, y);
        std::cout << "\nНажмите ENTER\n";
        std::cin.get();
        ok = true;
    }
    return (shotRes == 1);
}