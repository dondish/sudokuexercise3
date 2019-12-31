#include "parser.h"
#include<assert.h>

int main()
{
    command_t cmd;

    /* basic tests */

    const char *line = "set 1 2 3";
    assert(parseLine(line, &cmd));
    assert(cmd.type == CMDTYPE_SET);
    assert(cmd.X == 1);
    assert(cmd.Y == 2);
    assert(cmd.Z == 3);
    /* assert(cmd.X == 2); should fail */
    
    line = "hint 4 5";
    assert(parseLine(line, &cmd));
    assert(cmd.type == CMDTYPE_HINT);
    assert(cmd.X == 4);
    assert(cmd.Y == 5);

    line = "validate";
    assert(parseLine(line, &cmd));
    assert(cmd.type == CMDTYPE_VALIDATE);

    line = "restart";
    assert(parseLine(line, &cmd));
    assert(cmd.type == CMDTYPE_RESTART);

    line = "exit";
    assert(parseLine(line, &cmd));
    assert(cmd.type == CMDTYPE_EXIT);

    line = "fake";
    assert(!parseLine(line, &cmd));

    /* initial space test */

    line = "  hint 4 5";
    assert(parseLine(line, &cmd));
    assert(cmd.type == CMDTYPE_HINT);
    assert(cmd.X == 4);
    assert(cmd.Y == 5);

    line = "  validate";
    assert(parseLine(line, &cmd));
    assert(cmd.type == CMDTYPE_VALIDATE);

    /* additional parameters */
    
    line = "set 1 2 3 4";
    assert(parseLine(line, &cmd));
    assert(cmd.type == CMDTYPE_SET);
    assert(cmd.X == 1);
    assert(cmd.Y == 2);
    assert(cmd.Z == 3);

    line = "set 1 2 3 yeetus";
    assert(parseLine(line, &cmd));
    assert(cmd.type == CMDTYPE_SET);
    assert(cmd.X == 1);
    assert(cmd.Y == 2);
    assert(cmd.Z == 3);

    /* insufficient parameters */

    line = "set 1 2";
    assert(!parseLine(line, &cmd));

    line = "set 1";
    assert(!parseLine(line, &cmd));

    line = "set";
    assert(!parseLine(line, &cmd));

    line = "hint 1";
    assert(!parseLine(line, &cmd));

    line = "hint";
    assert(!parseLine(line, &cmd));

    return 0;
}
