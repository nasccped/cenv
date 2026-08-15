#include <stdio.h>
#include <string.h>

// Prints the help message
void print_help();

// Prints the app version.
void print_version();

int main(int argc, char *argv[]) {
  char *subcommand;

  switch (--argc) {

    // when no args
    case 0:
      printf("Welcome to c-env!\n");
      break;

    // when one arg
    case 1:
      argv++;
      subcommand = argv[0];

      if (strcmp(subcommand, "help") == 0)
        print_help();
      else if (strcmp(subcommand, "version") == 0)
        print_version();
      else {
        fprintf(stderr, "Non valid subcommand: %s.\n", argv[0]);
        return 1;
      }
      break;

    // when more than 1 arg
    default:
      fprintf(stderr, "Expected one (or no) subcommand. Got %d.\n", argc);
      return 1;
  }

  return 0;
}

void print_help() {
  printf("TODO: add help printing!\n");
}

void print_version() {
  printf("under development!\n");
}
