//
// Created by Magnus Rødseth on 16/07/2021.
//

#include <iostream>
#include "../include/Game.h"

// Determine which sleep function to use based on operating system
#ifdef _WIN32
#include <Windows.h>
#else

#include <unistd.h>

#endif

Game::Game(const Grid &grid) : grid(grid) {}

[[noreturn]] void Game::initialize() {
    int iterations = 0;

    while (true) {
        iterations++;
        std::cout << "----- Iteration " << iterations << " -----";

        grid.update();
        std::cout << grid << std::endl;
        // Wait 1 second per
        sleep(1);
    }

}


