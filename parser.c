#include "parser.h"
#include<stdio.h>
#include<string.h>

int parse_line(const char *line, command_t *cmd) {
    char buf[9];
    if (sscanf(line, " set %d %d %d", &cmd->X, &cmd->Y, &cmd->Z) == 3) {
        cmd->type = CMDTYPE_SET;
        return 1;
    }
    if (sscanf(line, " hint %d %d", &cmd->X, &cmd->Y) == 2) {
        cmd->type = CMDTYPE_HINT;
        return 1;
    }
    if (sscanf(line, " %8s", buf) == 1) {
        if (!strcmp("validate", buf)) {
            cmd->type = CMDTYPE_VALIDATE;
            return 1;
        }
        if (!strcmp("restart", buf)) {
            cmd->type = CMDTYPE_RESTART;
            return 1;
        }
        if (!strcmp("exit", buf)) {
            cmd->type = CMDTYPE_EXIT;
            return 1;
        }
    }
    
    return 0;
}
