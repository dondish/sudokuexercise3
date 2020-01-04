#include "solver.h"
#include "game.h"
#include<assert.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    game_state_t game;
    int x, y;

    srand(5);

    generate(&game, 10);
    assert(is_legal(&game.solution));
    print_board(&game.board_state);
    print_board(&game.solution);

    init_board(&game.board_state);
    game.board_state.board[0][1].fixed = 1;
    game.board_state.board[0][1].value = 6;
    game.board_state.board[0][8].fixed = 1;
    game.board_state.board[0][8].value = 5;
    game.board_state.board[2][4].value = 5;
    game.board_state.board[2][8].fixed = 1;
    game.board_state.board[2][8].value = 2;
    game.board_state.board[4][7].fixed = 1;
    game.board_state.board[4][7].value = 4;
    game.board_state.board[6][6].value = 5;
    game.board_state.board[8][1].fixed = 1;
    game.board_state.board[8][1].value = 9;

    assert(validate(&game));
    assert(is_legal(&game.solution));

    for (x = 0; x < BOARDSIZE; x++) {
        for (y = 0; y < BOARDSIZE; y++) {
            assert(game.solution.board[y][x].value > 0);
            assert(game.solution.board[y][x].value < 10);
        }
    }
    print_board(&game.solution);

    memcpy(&game.board_state, &game.solution, sizeof(board_state_t));
    game.board_state.board[8][8].value = 5;
    game.board_state.board[8][3].value = 0;
    game.board_state.board[8][3].fixed = 0;
    game.board_state.board[0][8].value = 0;
    game.board_state.board[0][8].fixed = 0;
    game.board_state.board[6][6].value = 0;
    game.board_state.board[6][6].fixed = 0;
    print_board(&game.board_state);

    assert(is_legal(&game.board_state));
    assert(!validate(&game));

    return 0;
}
