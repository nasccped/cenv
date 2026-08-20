#include <stdio.h>
#include "cli.h"

int main(int argc, char *argv[]) {
  static Cli cli = {0};

  if (!cli_parse(&cli, --argc, ++argv))
    return 1;

  switch (cli.action_kind) {
    case HELP_SUBCOMMAND_AS_FLAG:
      printf("--help was called!\n");
      break;

    case VERSION_SUBCOMMAND_AS_FLAG:
      printf("--version was called!\n");
      break;
  }

  return 0;
}
