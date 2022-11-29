#include <iostream>
#include "Game.h"

int main() {
    Game snake("Snake ultra pro max xs", 18, 10);
    snake.setDelay(100);
    snake.run();

    return 0;
}