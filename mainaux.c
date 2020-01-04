#include "mainaux.h"
#include "game.h"
#include "solver.h"
#include<stdio.h>
#include<stdlib.h>

void initialize(game_state_t *state) {
    int cells;
    init_board(&state->board_state);
    init_board(&state->solution);
    printf("Please enter the number of cells to fill [0-80]:\n");
    if (scanf("%d", &cells) == EOF) {
        printf("Exiting...\n");
        exit(0);
    }
    getchar();
    while (cells < 0 || cells > 80)
    {
        printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
        printf("Please enter the number of cells to fill [0-80]:\n");
        if (scanf("%d", &cells) == EOF) {
            printf("Exiting...\n");
            exit(0);
        }
        getchar();
    }
    generate(state, cells);
}

void process_command(game_state_t *state, char *line) {
    command_t cmd;
    int temp;
    
    if (parse_line(line, &cmd)) {

        switch (cmd.type)
        {
        case CMDTYPE_SET:
            if (is_finished(&state->board_state)) {
                printf("Error: invalid command\n");
                return;
            }
            if (state->board_state.board[cmd.Y-1][cmd.X-1].fixed) {
                printf("Error: cell is fixed\n");
                return;
            }
            
            temp = state->board_state.board[cmd.Y-1][cmd.X-1].value;
            state->board_state.board[cmd.Y-1][cmd.X-1].value = cmd.Z;
            
            if (!is_legal(&state->board_state)) {
                printf("Error: value is invalid\n");
                state->board_state.board[cmd.Y-1][cmd.X-1].value = temp;
                break;
            }

            print_board(&state->board_state);
            
            if (is_finished(&state->board_state)) {
                printf("Puzzle solved successfully\n");
            }
            
            break;
        
        case CMDTYPE_HINT:
            if (is_finished(&state->board_state)) {
                printf("Error: invalid command\n");
                return;
            }
            printf("Hint: set cell to %d\n", state->solution.board[cmd.Y-1][cmd.X-1].value);
            break;

        case CMDTYPE_VALIDATE:
            if (is_finished(&state->board_state)) {
                printf("Error: invalid command\n");
                return;
            }
            if (validate(state)) {
                printf("Validation passed: board is solvable\n");
            } else {
                printf("Validation failed: board is unsolvable\n");
            }
            break;

        case CMDTYPE_RESTART:
            initialize(state);
            break;

        case CMDTYPE_EXIT:
            printf("Exiting...\n");
            exit(0);

        
        default:
            break;
        }
    } else {
        printf("Error: invalid command\n");
    }
}
