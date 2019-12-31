#ifndef GAME_H
#define GAME_H
#define BOARDSIZE 9

typedef struct cell {
    int fixed: 1;
    int value: 4;
} cell_t;

typedef struct game_state {
    cell_t *board[BOARDSIZE][BOARDSIZE];
} game_state_t;

#endif
