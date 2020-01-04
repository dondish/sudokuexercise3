#ifndef GAME_H
#define GAME_H

#define SQRT_BOARDSIZE 3
#define BOARDSIZE (SQRT_BOARDSIZE * SQRT_BOARDSIZE)

/* This struct represents a cell in the board. */
typedef struct cell {
    unsigned int fixed: 1;
    unsigned int value: 4;
} cell_t;

/* This struct represents the board's state. */
typedef struct board_state {
    cell_t board[BOARDSIZE][BOARDSIZE];
} board_state_t;

/* This struct represents the game's state. */
typedef struct game_state {
    board_state_t board_state;
    board_state_t solution;
} game_state_t;

/*
Initializes all of the cells to 0
*/
void init_board(board_state_t *state);

/*
Returns whether the board is legal.
*/
int is_legal(board_state_t *state);

/*
Returns whether the board is finished.
*/
int is_finished(board_state_t *state);

/*
Writes the structure of the board to the given string. 
*/
void sprint_board(const board_state_t *state, char *res);

/*
Writes the structure of the board to stdout. 
*/
void print_board(const board_state_t *state);

#endif
