#include <iostream>
#include <stdlib.h>
#include "MultiPlayer.h"
#include "GameView.h"

using namespace std;

int main() {
    GameView gameView;
    gameView.startScreen();
    std::cin.get();
    return 0;
}