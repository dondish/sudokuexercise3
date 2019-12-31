#ifndef GAME_H
#define GAME_H
#define BOARDSIZE 9

typedef struct cell {
    unsigned int fixed: 1;
    unsigned int value: 4;
} cell_t;

typedef struct game_state {
    cell_t board[BOARDSIZE][BOARDSIZE];
} game_state_t;

void init_board(game_state_t *state);

void print_board(const game_state_t *state, char *res);

#endif
