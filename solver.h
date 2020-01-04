#ifndef SOLVER_H
#define SOLVER_H
#include "game.h"

/*
Tries to solve the soduko.
It returns whether it succeeded or failed.
*/
int det_backtrack(game_state_t *state);

#endif
