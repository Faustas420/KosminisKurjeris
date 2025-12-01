#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand((unsigned)time(nullptr));

    int difficulty;
    std::cout << "Select difficulty (1=Easy, 2=Medium, 3=Hard): ";
    std::cin >> difficulty;

    Game game(difficulty);
    game.run();

    return 0;
}
