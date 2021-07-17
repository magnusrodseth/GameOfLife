//
// Created by Magnus Rødseth on 16/07/2021.
//

#include <thread>
#include <vector>
#include <iostream>
#include "../include/Grid.h"

Grid::Grid(int rows, int columns) : rows(rows), columns(columns) {
    this->populate();
}

std::ostream &operator<<(std::ostream &os, const Grid &grid) {
    for (int row = 0; row < grid.rows; row++) {
        os << std::endl;
        for (int col = 0; col < grid.columns; col++) {
            os << grid.grid[row][col];
        }
    }

    return os;
}

void Grid::populate() {
    Cell **grid = new Cell *[this->rows];

    // Allocate columns amount of arrays in each row.
    for (int row = 0; row < this->rows; row++) {
        grid[row] = new Cell[this->columns];
    }

    // Populate grid
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->columns; col++) {
            Cell cell(row, col);
            grid[row][col] = cell;
        }
    }

    this->grid = grid;
}

void Grid::update() {
    // Rules:
    // - Any live cell with two or three live neighbours survives.
    // - Any dead cell with three live neighbours becomes a live cell.
    // - All other live cells die in the next generation. Similarly, all other dead cells stay dead.

    // Copy existing grid
    Cell **next = new Cell *[this->rows];
    memcpy(next, this->grid, this->rows * this->columns * sizeof(Cell));

    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->columns; col++) {
            int aliveNeighborsCount = this->getAliveNeighborsCount(row, col);

            // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            // Any live cell with more than three live neighbours dies, as if by overpopulation.
            if (grid[row][col].isAlive() && (aliveNeighborsCount < 2 || aliveNeighborsCount > 3)) {
                next[grid[row][col].getY()][grid[row][col].getX()].kill();
                return;
            }

            // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
            if (!grid[row][col].isAlive() && aliveNeighborsCount == 3) {
                next[grid[row][col].getY()][grid[row][col].getX()].resurrect();
                return;
            }

            // Any live cell with two or three live neighbours lives on to the next generation.
        }
    }

    // Overwrite state in grid
    this->grid = next;
}

int Grid::getAliveNeighborsCount(int row, int col) {
    int aliveNeighborsCount = 0;
    for (int y = this->grid[row][col].getY() - 1; y <= this->grid[row][col].getY() + 1; y++) {
        // Coordinates are out of bounds
        if (y < 0 || y >= this->rows) {
            continue;
        }
        for (int x = this->grid[row][col].getX() - 1; x <= this->grid[row][col].getX() + 1; x++) {
            // Only care about the 8 neighbours the current grid[row][col]
            if (x == this->grid[row][col].getX() && y == this->grid[row][col].getY()) {
                continue;
            }
            // Coordinates are out of bounds
            if (x < 0 || x >= this->columns) {
                continue;
            }

            if (this->grid[y][x].isAlive()) {
                aliveNeighborsCount++;
            }
        }
    }

    return aliveNeighborsCount;
}
