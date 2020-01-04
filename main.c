#include "mainaux.h"
#include "game.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    game_state_t state;
    char line[1024];

    if (argc > 1) {
        srand(atoi(argv[1]));
    } else {
        puts("Error: missing seed argument");
        return 1;
    }

    initialize(&state);
    print_board(&state.board_state);
    while (1)
    {
        if (fgets(line, 1024, stdin) == NULL) {
            if (feof(stdin)) {
                puts("Exiting...");
                return 0;
            }
            puts("Error: fgets has failed");
            return 1;
        }
        process_command(&state, line);
    }
    
    return 0;
}
