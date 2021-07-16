//
// Created by Magnus Rødseth on 16/07/2021.
//

#ifndef GAMEOFLIFE_GAME_H
#define GAMEOFLIFE_GAME_H


#include "Grid.h"

class Game {
    Grid grid;

public:
    Game(const Grid &grid);

    [[noreturn]] void initialize();
};


#endif //GAMEOFLIFE_GAME_H
