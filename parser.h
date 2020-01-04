#ifndef PARSER_H
#define PARSER_H

/*
This enum enumerates the possible types of commands
*/
typedef enum cmdtype {
    CMDTYPE_SET,
    CMDTYPE_HINT,
    CMDTYPE_VALIDATE,
    CMDTYPE_RESTART,
    CMDTYPE_EXIT
} cmdtype_t;

/*
This struct defines a command
*/
typedef struct command {
    cmdtype_t type; /* The command's type */ 
    int X; /* The first argument */
    int Y; /* The second argument */
    int Z; /* The third argument */
} command_t;

/* 
    Parses a line and returns the matching command
    returns a boolean on whether the command is valid
*/
int parse_line(const char *line, command_t *cmd);

#endif
