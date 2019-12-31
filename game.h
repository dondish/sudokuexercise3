#ifndef GAME_H
#define GAME_H
#define BOARDSIZE 9

/* This struct represents a cell in the board. */
typedef struct cell {
    unsigned int fixed: 1;
    unsigned int value: 4;
} cell_t;

/* This struct represents the game's state. */
typedef struct game_state {
    cell_t board[BOARDSIZE][BOARDSIZE];
} game_state_t;

/*
Initializes all of the cells to 0
*/
void init_board(game_state_t *state);

/*
Writes the structure of the board to the string given. 
*/
void print_board(const game_state_t *state, char *res);

#endif
