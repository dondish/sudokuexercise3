#include "parser.h"
#include<stdio.h>
#include<string.h>

int parseLine(const char *line, command_t *cmd) {
    if (sscanf(line, "set %d %d %d", &cmd->X, &cmd->Y, &cmd->Z) == 3) {
        cmd->type = CMDTYPE_SET;
        return 1;
    }
    if (sscanf(line, "hint %d %d", &cmd->X, &cmd->Y) == 2) {
        cmd->type = CMDTYPE_HINT;
        return 1;
    }
    if (!strncmp("validate", line, 8)) {
        cmd->type = CMDTYPE_VALIDATE;
        return 1;
    }
    if (!strncmp("restart", line, 7)) {
        cmd->type = CMDTYPE_RESTART;
        return 1;
    }
    if (!strncmp("exit", line, 4)) {
        cmd->type = CMDTYPE_EXIT;
        return 1;
    }
    return 0;
}
