#include <stdio.h>
#include "cli.h"

int main(int argc, char *argv[]) {
  static Cli cli = {0};

  if (!cli_parse(&cli, --argc, ++argv))
    return 1;

  switch (cli.action_kind) {
    case HELP_ACTION:
      printf("--help was called!\n");
      break;

    case VERSION_ACTION:
      if (!run_version_action(&cli.action.version))
        return 1;

      break;
  }

  return 0;
}
