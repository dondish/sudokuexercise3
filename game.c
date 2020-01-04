#include "game.h"
#include<string.h>
#include<stdio.h>
#define DASHLINE "----------------------------------\n"

void init_board(game_state_t *state) {
    int x, y;
    for (y = 0; y < BOARDSIZE; y++) {
        for (x = 0; x < BOARDSIZE; x++) {
            state->board[y][x].value = 0;
            state->board[y][x].fixed = 0;
        }
    }
}

int is_legal(game_state_t *state) {
    int checker[BOARDSIZE] = {0};
    int x,y;
    for (x=0;x<BOARDSIZE;x++) {
        for (y=0;y<BOARDSIZE;y++) {
            if (state->board[x][y].value && (checker[x] & (1 << state->board[x][y].value))) {
                return 0;
            }
            checker[x] |= (1 << state->board[x][y].value);
        }
    }
    for (x=0;x<BOARDSIZE;x++) {
        checker[x] = 0;
    }
    for (x=0;x<BOARDSIZE;x++) {
        for (y=0;y<BOARDSIZE;y++) {
            if (state->board[y][x].value && (checker[x] & (1 << state->board[y][x].value))) {
                return 0;
            }
            checker[x] |= (1 << state->board[y][x].value);
        }
    }
    return 1;
}

void print_board(const game_state_t *state, char *res) {
    int x, y;
    cell_t cell;
    for (y = 0; y < BOARDSIZE; y++) {
        if (y % 3 == 0) {
            strcat(res, DASHLINE);
        }
        for (x = 0; x < BOARDSIZE; x++) {
            if (x % 3 == 0) {
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
