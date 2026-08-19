#ifndef _CLI_H_
#define _CLI_H_

/* Refers to the cli structured call. This struct can be parsed from stdin args by using the
 * 'parse_cli' function. */
typedef struct {
  // TODO: add cli fields.
} Cli;

/* Takes a cli pointer and parse all the arguments into a final struct. It also returns an
 * 'integer' that indicates operation success. */
int cli_parse(Cli *cli, int arg_count, char *args[]);

#endif
