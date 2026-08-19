#include "cli.h"

int cli_parse(Cli *cli, int arg_count, char *args[]) {
  // NOTE: prevent warnings on unused params
  if (!cli || !arg_count || !args)
    return 0;

  // TODO: implement 'Cli' parsing logic.
  return 0;
}
