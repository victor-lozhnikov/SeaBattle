#include <iostream>
#include <stdlib.h>
#include "MultiPlayer.h"
#include "GameView.h"

using namespace std;

void printStartText() {
    cout << "Добро пожаловать в игру Морской Бой.\n\n"
            "Выберите тип игры:\n"
            "1. Два игрока\n"
            "2. Игра против глупого компьютера\n"
            "3. Игра против умного компьютера\n\n"
            "Введите одно число от 1 до 3 - номер выбранного типа игры: ";
}

void StartScreen() {
    bool isStarted = false;
    GameView gameView;
    while (!isStarted) {
        gameView.clearScreen();
        printStartText();
        string type;
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
                cout << "Выбран тип 2";
                isStarted = true;
                break;
            case '3':
                cout << "Выбран тип 3";
                isStarted = true;
                break;
            default:
                break;
        }
    }
}

int main() {
    StartScreen();
    std::cin.get();
    return 0;
}