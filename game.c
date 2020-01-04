#include "game.h"
#include<string.h>
#include<stdio.h>
#define DASHLINE "----------------------------------\n"

void init_board(board_state_t *state) {
    int x, y;
    for (y = 0; y < BOARDSIZE; y++) {
        for (x = 0; x < BOARDSIZE; x++) {
            state->board[y][x].value = 0;
            state->board[y][x].fixed = 0;
        }
    }
}

int is_finished(board_state_t *state) {
    int x, y;
    for (y = 0; y < BOARDSIZE; y++) {
        for (x = 0; x < BOARDSIZE; x++) {
            if (state->board[y][x].value == 0) {
                return 0;
            }
        }
    }
    return is_legal(state);
}

int is_legal(board_state_t *state) {
    int checker[BOARDSIZE] = {0};
    int x,y;

    for (x=0;x<BOARDSIZE;x++) { /* columns */
        for (y=0;y<BOARDSIZE;y++) {
            if (state->board[x][y].value && (checker[x] & (1 << state->board[x][y].value))) {
                return 0;
            }
            checker[x] |= (1 << state->board[x][y].value);
        }
    }

    memset(checker, 0, sizeof(checker));
    for (x=0;x<BOARDSIZE;x++) { /* rows */
        for (y=0;y<BOARDSIZE;y++) {
            if (state->board[y][x].value && (checker[x] & (1 << state->board[y][x].value))) {
                return 0;
            }
            checker[x] |= (1 << state->board[y][x].value);
        }
    }

    memset(checker, 0, sizeof(checker));
    for (x=0;x<BOARDSIZE;x++) { /* blocks */
                                /* The x represents the block, like a phone 
                                x/y: 0 1 2
                                   3 4 5
                                   6 7 8
                                the y represents the placement inside the block, similarly to x.
                                to get the row number we have to take (x-(x%3)) (that will give us the block's row)
                                (x-(x%3)): 0 0 0
                                           3 3 3
                                           6 6 6
                                and then we add the y's row number which is (y-(y%3))/3
                                (y-(y%3))/3: 0 0 0
                                             1 1 1
                                             2 2 2
                                in order to get the column we will do (x%3)*3 to get the block's column
                                (x%3)*3: 0 3 6
                                         0 3 6
                                         0 3 6
                                and then we add y%3 to get the block's position:
                                y%3: 0 1 2
                                     0 1 2
                                     0 1 2
                                */
        for (y=0;y<BOARDSIZE;y++) {
            int val = state
                        ->board[(x - (x % SQRT_BOARDSIZE)) +
                                (y - (y % SQRT_BOARDSIZE)) / SQRT_BOARDSIZE]
                                [(x % SQRT_BOARDSIZE) * SQRT_BOARDSIZE +
                                y % SQRT_BOARDSIZE]
                        .value;
            int mask = 1 << val;
            if (val && (checker[x] & mask)) {
                return 0;
            }
            checker[x] |= mask;
        }
    }
    return 1;
}

void sprint_board(const board_state_t *state, char *res) {
    int x, y;
    cell_t cell;
    for (y = 0; y < BOARDSIZE; y++) {
        if (y % SQRT_BOARDSIZE == 0) {
            strcat(res, DASHLINE);
        }
        for (x = 0; x < BOARDSIZE; x++) {
            if (x % SQRT_BOARDSIZE == 0) {
                strcat(res, "| ");
            }
            cell = state->board[y][x];

            if (cell.fixed) {
                strcat(res, ".");
            } else {
                strcat(res, " ");
            }
            if (cell.value > 0) {
                sprintf(res + strlen(res), "%d ", cell.value);
            } else {
                strcat(res, "  ");
            }
        }
        strcat(res, "|\n");
    }
    strcat(res, DASHLINE);
}

void print_board(const board_state_t *state) {
    char res[1024] = {0};
    sprint_board(state, res);
    printf("%s", res);
}
