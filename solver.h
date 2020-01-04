#ifndef SOLVER_H
#define SOLVER_H

#include "game.h"

/*
Check whether the current game is solveable, filling out the solution if it is.
*/
int validate(game_state_t *game);

/*
Generates a board of the amount of cells given.
*/
int generate(game_state_t *game, int cells);

#endif
