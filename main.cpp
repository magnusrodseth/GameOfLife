#include "include/Grid.h"
#include "include/Game.h"

int main() {
    Grid grid(25, 25);
    Game game(grid);

    game.initialize();

    return 0;
}
