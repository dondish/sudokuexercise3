#include "solver.h"
#include "game.h"

#include <string.h>
#include <stdlib.h>

/*
Copy all guessed values as fixed from a board to another
*/
static void copy_as_fixed(board_state_t* to, board_state_t* from) {
    int x,y;
    for (x=0; x<BOARDSIZE; x++) {
        for (y=0; y<BOARDSIZE; y++) {
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
Gather all candidates for column x, row y on the board in ascending order,
storing the result to `candidates`. Returns the number of candidates.
*/
static int gather_candidates(board_state_t* state, int x, int y, int* candidates) {
    int candidate_count = 0;
    int i = 1;
    for (; i <= BOARDSIZE; i++) {
        state->board[y][x].value = i;
        if (is_legal(state)) {
            candidates[candidate_count++] = i;
        }
    }
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
Goes forward 1 tile, wrapping at board edges. Returns whether the end of the
board was reached.
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
Callback which the backtracker uses to select the index of the next candidate
*/
typedef int(*candidate_selector_t)(int count);

/*
Main backtracking implementation - attempt to find a valid solution, scanning
forward from column `x` of row `y` and enumerating all possibilities. If multiple
candidates are found for a given cell, `selector` is used to select the index of
the next one.
Returns whether a legal solution was found.
Note: this function may modify the board state even if it returns false.
*/
static int backtrack_rec(board_state_t *state, int x, int y, candidate_selector_t selector) {
    int candidates[BOARDSIZE];
    int candidate_count;

    if (state->board[y][x].fixed) {
        if (go_forward(&x, &y)) {
                return 1;
        }
        return backtrack_rec(state, x, y, selector);
    }

    candidate_count = gather_candidates(state, x, y, candidates);
    while (candidate_count) {
        int candidate_idx = candidate_count == 1 ? 0 : selector(candidate_count);
        int next_x = x, next_y = y;

        state->board[y][x].value = candidates[candidate_idx];

        if (go_forward(&next_x, &next_y) || backtrack_rec(state, next_x, next_y, selector)) {
            return 1;
        }

        remove_candidate(candidates, candidate_idx, candidate_count);
        candidate_count--;
    }
    
    return 0;
}

static int backtrack(board_state_t* state, candidate_selector_t selector) {
    return backtrack_rec(state, 0, 0, selector);
}

static int det_backtrack_selector(int count) {
    (void) count;
    return 0; /* Always select first untested candidate */
}

static int rand_backtrack_selector(int count) {
    return rand() % count; /* Select random untested candidate */
}

static void populate_fixed_cells(game_state_t* game, int cells) {
    int i;
    for (i = 0; i < cells; i++) {
        int x, y;

        do {
            x = rand() % BOARDSIZE;
            y = rand() % BOARDSIZE;
        } while (game->board_state.board[y][x].fixed);

        game->board_state.board[y][x].value = game->solution.board[y][x].value;
        game->board_state.board[y][x].fixed = 1;
    }
}

void generate(game_state_t* game, int cells) {
    init_board(&game->board_state);
    init_board(&game->solution);

    backtrack(&game->solution, rand_backtrack_selector);
    populate_fixed_cells(game, cells);
}

int validate(game_state_t *game) {
    board_state_t tmp;
    copy_as_fixed(&tmp, &game->board_state);
    if (backtrack(&tmp, det_backtrack_selector)) {
        memcpy(&game->solution, &tmp, sizeof(board_state_t));
        return 1;
    }
    return 0;
}
