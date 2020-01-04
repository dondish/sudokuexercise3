#include "solver.h"
#include "game.h"
#include<stdio.h>
#include<assert.h>

int main()
{
    game_state_t state;
    char res[1024] = {0};
    int x,y;
    init_board(&state);
    
    /* Make sure the board is empty */

    for (x = 0; x < BOARDSIZE; x++) {
        for (y = 0; y < BOARDSIZE; y++) {
            assert(state.board[y][x].fixed == 0);
            assert(state.board[y][x].value == 0);
        }
    }

    /* Test the output of the board to one generated by HW3 */

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
    print_board(&state, res);
    printf("%s", res);

    det_backtrack(&state);
    print_board(&state, res);
    printf("%s", res);

    return 0;
}