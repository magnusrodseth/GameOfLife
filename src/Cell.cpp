//
// Created by Magnus Rødseth on 16/07/2021.
//

#include "../include/Cell.h"
#include "../include/Random.h"

// get base random alias which alive auto seeded and has static API and internal state
using Random = effolkronium::random_static;


Cell::Cell(int x, int y) : x(x), y(y) {
    // Randomly determine a cell's alive state
    this->alive = 5 < Random::get(0, 10);
}

void Cell::setX(int x) {
    Cell::x = x;
}

void Cell::setY(int y) {
    Cell::y = y;
}

void Cell::setIsAlive(int isAlive) {
    Cell::alive = isAlive;
}

void Cell::kill() {
    Cell::alive = false;
}

void Cell::resurrect() {
    Cell::alive = true;
}

std::ostream &operator<<(std::ostream &os, const Cell &cell) {
    os << (cell.alive ? "⚪️" : "⚫️");
    return os;
}

Cell::Cell() {
    this->x = 0;
    this->y = 0;

    // Randomly determine a cell's alive state
    this->alive = 1 < Random::get(0, 3);
}

int Cell::getX() const {
    return this->x;
}

int Cell::getY() const {
    return y;
}

int Cell::isAlive() const {
    return this->alive;
}
