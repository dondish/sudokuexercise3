#include "solver.h"
#include "game.h"
#include<assert.h>

int main()
{
    board_state_t state;
    int x,y;

    init_board(&state);
    state.board[0][1].fixed = 1;
    state.board[0][1].value = 6;
    state.board[0][8].fixed = 1;
    state.board[0][8].value = 5;
    state.board[1][4].fixed = 1;
    state.board[1][4].value = 6;
    state.board[2][8].fixed = 1;
    state.board[2][8].value = 2;
    state.board[3][7].fixed = 1;
    state.board[3][7].value = 6;
    state.board[7][6].fixed = 1;
    state.board[7][6].value = 6;
    print_board(&state);

    assert(!det_backtrack(&state));
    assert(is_legal(&state));
    print_board(&state);

    init_board(&state);
    state.board[0][1].fixed = 1;
    state.board[0][1].value = 6;
    state.board[0][8].fixed = 1;
    state.board[0][8].value = 5;
    state.board[2][4].value = 5;
    state.board[2][8].fixed = 1;
    state.board[2][8].value = 2;
    state.board[4][7].fixed = 1;
    state.board[4][7].value = 4;
    state.board[6][6].value = 5;
    state.board[8][1].fixed = 1;
    state.board[8][1].value = 9;
    print_board(&state);

    assert(det_backtrack(&state));
    assert(is_legal(&state));

    for (x=0;x<BOARDSIZE;x++){
        for (y=0;y<BOARDSIZE;y++){
            assert(state.board[y][x].value > 0);
            assert(state.board[y][x].value < 10);
        }
    }
    print_board(&state);
    return 0;
}
