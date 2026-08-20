#include <string.h>
#include "cli.h"
#include "cenvutils.h"

/* Help macro when both string pointers for 'colored_set...' and 'string_set...' refers to the same
 * addres. */
#define COLORED_STRING_AND_SELF_SET(CS_PTR, STYLE, FG, BG, STR_PTR) \
  do {                                                              \
    CSSV((CS_PTR), (STYLE), (FG), (BG), (STR_PTR));                 \
    SSFCS((STR_PTR), (CS_PTR));                                     \
  } while (0)

/* Alias for 'colored_string_set_values'. */
#define CSSV(CS_PTR, STYLE, FG, BG, STR_PTR) \
  colored_string_set_values((CS_PTR), (STYLE), (FG), (BG), (STR_PTR))

/* Alias for 'string_set_from_colored_string' */
#define SSFCS(STR_PTR, CS_PTR) string_set_from_colored_string((STR_PTR), (CS_PTR))

/* When a (must) single arg is followeda by another. This function takes also a 'ColoredString'
 * pointer + bold_backtick string to avoid redo allocations on string coloring. */
void print_error_action_cant_be_followed_by_args(ColoredString *cs, char *action, char *bb);

/* When no arg is provided. This function takes also a 'ColoredString' pointer + bold_backtick
 * string to avoid redo allocations on string coloring. */
void print_error_expecting_args(ColoredString *cs, char *bb);

/* When the provided arg isn't recognized as a valid action (subcommand/flag). This function takes
 * also a 'ColoredString' pointer + bold_backtick string to avoid redo allocations on string
 * coloring. */
void print_error_undefined_action(ColoredString *cs, char *action, char *bb);

int cli_parse(Cli *cli, int arg_count, char *args[]) {
  ColoredString cs = {0};
  char bold_backtick[16] = "`";

  COLORED_STRING_AND_SELF_SET(&cs, BOLD, NONE_COLOR, NONE_COLOR, bold_backtick);

  // if no args
  if (!arg_count || !args) {
    print_error_expecting_args(&cs, bold_backtick);
    return 0;
  }

  for (int i = 0; i < arg_count; i++) {
    if (string_is_whitespace(args[i])) {
      print_error_tag("empty string isn't a valid argument!\n");
      return 0;
    }
  }

  if (strcmp(args[0], "--help") == 0) {
    if (--arg_count) {
      print_error_action_cant_be_followed_by_args(&cs, args[0], bold_backtick);
      return 0;
    }
    cli->action_kind = HELP_SUBCOMMAND_AS_FLAG;
  }

  else if (strcmp(args[0], "--version") == 0) {
    if (--arg_count) {
      print_error_action_cant_be_followed_by_args(&cs, args[0], bold_backtick);
      return 0;
    }
    cli->action_kind = VERSION_SUBCOMMAND_AS_FLAG;
  }

  else {
    print_error_undefined_action(&cs, args[0], bold_backtick);
    return 0;
  }

  return 1;
}

void print_error_action_cant_be_followed_by_args(ColoredString *cs, char *action, char *wb) {
  char yellow_action[1024] = {0};

  CSSV(cs, BOLD, BRIGHT_YELLOW, NONE_COLOR, action);
  SSFCS(yellow_action, cs);

  print_error_tag(
    "%s%s%s %s can't be followed by any argument!\n",
    wb,
    yellow_action,
    wb,
    string_is_program_flag(action) ? "flag" : "subcommand"
  );
}

void print_error_expecting_args(ColoredString *cs, char *wb) {
  char
    green_cenv[16] = "cenv",
    bold_one[16] = "one",
    green_help_flag[16] = "--help";

  COLORED_STRING_AND_SELF_SET(cs, BOLD, BRIGHT_GREEN, NONE_COLOR, green_cenv);
  COLORED_STRING_AND_SELF_SET(cs, BOLD, NONE_COLOR, NONE_COLOR, bold_one);
  COLORED_STRING_AND_SELF_SET(cs, BOLD, BRIGHT_GREEN, NONE_COLOR, green_help_flag);

  print_error_tag("no argument was provided.\n\n");
  printerr("%s%s%s program expected at least %s subcommand/flag.\n\n", wb, green_cenv, wb, bold_one);
  print_note_tag(
    1,
    "consider using %s%s%s flag to get a more detailed\n"
    "overview!\n",
    wb,
    green_help_flag,
    wb
  );
}

void print_error_undefined_action(ColoredString *cs, char *action, char *bb) {
  char yellow_action[1024] = {0};
  char green_help_flag[32] = "--help";

  CSSV(cs, BOLD, BRIGHT_YELLOW, NONE_COLOR, action);
  SSFCS(yellow_action, cs);
  COLORED_STRING_AND_SELF_SET(cs, BOLD, BRIGHT_GREEN, NONE_COLOR, green_help_flag);

  print_error_tag(
    "undefined %s being used (%s).\n\n",
    string_is_program_flag(action) ? "flag" : "subcommand",
    yellow_action
  );

  printerr(
    "Consider using the %s%s%s flag to get a more detailed\n"
    "overview!\n",
    bb,
    green_help_flag,
    bb
  );
}
