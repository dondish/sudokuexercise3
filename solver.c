#include "solver.h"

void copy_as_fixed(cell_t from[BOARDSIZE][BOARDSIZE], cell_t to[BOARDSIZE][BOARDSIZE]) {
    int x,y;
    cell_t cell;
    for (x=0;x<BOARDSIZE;x++) {
        for (y=0;y<BOARDSIZE;y++) {
            cell = from[x][y];
            if (cell.value > 0) {
                to[x][y].fixed = 1;
                to[x][y].value = cell.value;
            }
        }
    }
}

int go_forward(int *x, int *y) {
    (*x)++;
    if ((*x)==BOARDSIZE) {
        (*x)=0;
        (*y)++;
        if ((*y)==BOARDSIZE) {
            return 1;
        }
    }
    return 0;
}

int go_backward(int *x, int *y) {
    (*x)--;
    if ((*x)==-1) {
        (*x)=8;
        (*y)--;
        if ((*y)==-1) {
            return 1;
        }
    }
    return 0;
}

int det_backtrack_rec(game_state_t *state, int x, int y) {
    if (state->board[y][x].fixed) {
        if (go_forward(&x, &y)) {
                return 1;
        }
        return det_backtrack_rec(state, x, y);
    }
    do {
        state->board[y][x].value++;
    } while (!is_legal(state) && (state->board[y][x].value < 10));
    
    if (state->board[y][x].value == 10) {
        state->board[y][x].value = 0;
        do {
            if (go_backward(&x, &y)) {
                return 0;
            }
        } while (state->board[y][x].fixed);
    } else {
        if (go_forward(&x, &y)) {
                return 1;
        }
    }
    return det_backtrack_rec(state, x, y);
}

int det_backtrack(game_state_t *state) {
    return det_backtrack_rec(state, 0, 0);
}