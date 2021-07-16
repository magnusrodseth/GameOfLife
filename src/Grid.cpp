//
// Created by Magnus Rødseth on 16/07/2021.
//

#include <thread>
#include <vector>
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
            Cell &cell = grid[row][col];

            this->updateNeighbors(next, cell);
        }
    }

    // Overwrite state in grid
    this->grid = next;
}

void Grid::updateNeighbors(Cell **grid, Cell &cell) {
    int aliveNeighborsCount = 0;

    for (int y = cell.getY() - 1; y <= cell.getY() + 1; y++) {
        // Coordinates are out of bounds
        if (y < 0 || y >= this->rows) {
            continue;
        }
        for (int x = cell.getX() + 1; x <= cell.getX() + 1; x++) {
            // Only care about the 8 neighbours the current cell
            if (x == cell.getX() && y == cell.getY()) {
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

    // Any dead cell with three live neighbours becomes a live cell.
    if (!cell.isAlive() && aliveNeighborsCount == 3) {
        grid[cell.getY()][cell.getX()].resurrect();
        return;
    }

    // Any live cell with two or three live neighbours survives.
    if (cell.isAlive() && (aliveNeighborsCount >= 2 && aliveNeighborsCount <= 3)) {
        return;
    }

    // All other live cells die in the next generation. Similarly, all other dead cells stay dead.
    grid[cell.getY()][cell.getX()].kill();
}
