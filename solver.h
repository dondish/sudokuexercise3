#ifndef SOLVER_H
#define SOLVER_H

#include "game.h"

/*
Check whether the current game is solveable, filling out the solution if it is.
*/
int validate(game_state_t *game);

/*
Generate a random solution for the game and copy the specified number of cells
to the game state as fixed.
*/
void generate(game_state_t *game, int cells);

#endif
