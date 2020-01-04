#ifndef MAINAUX_H
#define MAINAUX_H
#include "game.h"
#include "parser.h"

void initialize(game_state_t *state);

void process_command(game_state_t *state, char *line);

#endif
