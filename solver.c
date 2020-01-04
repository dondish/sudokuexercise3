#include "solver.h"

#include <string.h>

typedef int(*candidate_selector_t)(int*, int);

/*
Copy all guessed values as fixed from a board to another
*/
static void copy_as_fixed(board_state_t* to, board_state_t* from) {
    int x,y;
    for (x=0;x<BOARDSIZE;x++) {
        for (y=0;y<BOARDSIZE;y++) {
            if (from->board[x][y].value > 0) {
                to->board[x][y].fixed = 1;
            } else {
                to->board[x][y].fixed = 0;
            }
            to->board[x][y].value = from->board[x][y].value;
        }
    }
}

/*
copies board values from a board to another.
*/
static void copy_board_values(cell_t from[BOARDSIZE][BOARDSIZE], cell_t to[BOARDSIZE][BOARDSIZE]) {
    int x,y;
    for (x=0;x<BOARDSIZE;x++) {
        for (y=0;y<BOARDSIZE;y++) {
            to[x][y].value = from[x][y].value;
        }
    }
}

/* 
Gather all candidates for position (x, y) on the board in ascending order,
storing the result to `candidates`. Returns the number of candidates.
*/
static int gather_candidates(board_state_t* state, int x, int y, int* candidates) {
    int candidate_count = 0;
    int i = 1;
    int old_val = state->board[x][y].value;
    for (; i <= BOARDSIZE; i++) {
        state->board[x][y].value = i;
        if (is_legal(state)) {
            candidates[candidate_count++] = i;
        }
    }
    state->board[x][y].value = old_val;
    return candidate_count;
}

/*
Remove the i'th candidate from the list of candidates, shifting the rest over as
necessary.
*/
static void remove_candidate(int* candidates, int i, int candidate_count) {
    if (i < candidate_count - 1) {
        memmove(candidates + i, candidates + i + 1, (candidate_count - i - 1) * sizeof(int));
    }
}

/*
Goes forward 1 tile. it handles edges.
*/
static int go_forward(int *x, int *y) {
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

/*
Goes back 1 tile. it handles edges.
*/
static int go_backward(int *x, int *y) {
    (*x)--;
    if ((*x)==-1) {
        (*x)=BOARDSIZE-1;
        (*y)--;
        if ((*y)==-1) {
            return 1;
        }
    }
    return 0;
}

static int det_backtrack_rec(board_state_t *state, int x, int y) {
    if (state->board[y][x].fixed) {
        if (go_forward(&x, &y)) {
                return 1;
        }
        return det_backtrack_rec(state, x, y);
    }
    do {
        state->board[y][x].value++;
        if (is_legal(state)) {
            if (go_forward(&x, &y) || det_backtrack_rec(state, x, y)) {
                return 1;
            }
            go_backward(&x, &y);
        }
    } while ((state->board[y][x].value < 9));
    
    
    state->board[y][x].value = 0;
    return 0;
}

int det_backtrack(board_state_t *state) {
    return det_backtrack_rec(state, 0, 0);
}

int solve_from_pos(board_state_t *state) {
    /*board_state_t poscopy;
    int res;
    copy_as_fixed(state->board, poscopy.board);
    res = det_backtrack(&poscopy);
    if (res) {
        copy_board_values(poscopy.board, state->board);
    }
    return res;*/
}

int validate(game_state_t *game) {
    /*board_state_t poscopy;
    copy_as_fixed(state->board, poscopy.board);
    return det_backtrack(&poscopy);*/
}