//
// Created by Magnus Rødseth on 16/07/2021.
//

#ifndef GAMEOFLIFE_CELL_H
#define GAMEOFLIFE_CELL_H


#include <ostream>

class Cell {
    int x;
    int y;
    int alive = false;

    void setIsAlive(int isAlive);

public:
    Cell();

    Cell(int x, int y);

    void setX(int x);

    void setY(int y);

    void kill();

    void resurrect();

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell);

    int getX() const;

    int getY() const;

    int isAlive() const;
};


#endif //GAMEOFLIFE_CELL_H
