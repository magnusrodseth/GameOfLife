//
// Created by Magnus Rødseth on 16/07/2021.
//

#ifndef GAMEOFLIFE_GRID_H
#define GAMEOFLIFE_GRID_H


#include <ostream>
#include "Cell.h"

class Grid {
    int rows;
    int columns;
    Cell **grid{};

public:
    Grid(int rows, int columns);

    void populate();

    void update();

    friend std::ostream &operator<<(std::ostream &os, const Grid &grid);

    int getAliveNeighborsCount(int row, int col);
};


#endif //GAMEOFLIFE_GRID_H
