#ifndef _CLI_H_
#define _CLI_H_

#include "version_action.h"

/* Refers to the cli structured call. This struct can be parsed from stdin args
 * by using the 'parse_cli' function. */
typedef struct
{
    /* Kind of action being executed. */
    enum
    {

        /* Refers to the help flag at global scope (cenv --help). */
        HELP_ACTION,

        /* Refers to the version flag at global scope (cenv --version). */
        VERSION_ACTION

    } action_kind;

    /* Action auxiliar struct. */
    union {
        /* When version is called. */
        Version version;

    } action;

} Cli;

/* Takes a cli pointer and parse all the arguments into a final struct. It also
 * returns an 'integer' that indicates operation success. */
int cli_parse(Cli *cli, int arg_count, char *args[]);

#endif
