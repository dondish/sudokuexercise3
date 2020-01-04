#include "mainaux.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    game_state_t state;
    char line[1024];

    if (argc > 0) {
        srand(atoi(argv[1]));
    } else {
        srand(5);
    }

    initialize(&state);
    while (1)
    {
        if (fgets(line, 1024, stdin) == NULL) {
            if (feof(stdin)) {
                printf("Exiting...\n");
                exit(0);
            }
            printf("Error: fgets has failed\n");
            exit(1);
        }
        process_command(&state, line);
    }
    
    return 0;
}

