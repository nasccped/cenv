#include "cli.h"
#include "cenv_common_error_display.h"
#include "cenvutils.h"
#include <stdio.h>
#include <string.h>

/* Checks if the provided X string refers to the help subcommand/flag. */
#define IS_HELP_ACTION(X) strcmp((X), "help") == 0 || strcmp((X), "--help") == 0

/* Checks if the provided X string refers to the version subcommand/flag. */
#define IS_VERSION_ACTION(X) strcmp((X), "version") == 0 || strcmp((X), "--version") == 0

/* Does the 'empty string isn't allowed' error printing. It takes the argument
 * position (index of the first) whitespace string occurence. */
inline static void print_empty_string_arg_error(int arg_pos);

/* Does the 'expecting args' error printing. */
inline static void print_expecting_arg_error();

/* Does the 'consider using --help flag' hint printing. Note that this function
 * automatically prints to stderr. */
inline static void print_help_flag_tip();

/* Does the 'undefined flag/subcommand call ...' error printing on the provided
 * string argument. */
inline static void print_undefined_argument_call_error(char *arg);

int cli_parse(Cli *cli, int arg_count, char *args[])
{
    // if no args
    if (!arg_count || !args)
    {
        print_expecting_arg_error();
        return 0;
    }

    for (int i = 0; i < arg_count; i++)
    {
        if (string_is_whitespace(args[i]))
        {
            print_empty_string_arg_error(i + 1);
            return 0;
        }
    }

    char *action = args[0];
    args++;
    arg_count--;

    if (IS_HELP_ACTION(action))
    {
        cli->action_kind = HELP_ACTION;
        return 1;
    }
    else if (IS_VERSION_ACTION(action))
    {
        cli->action_kind = VERSION_ACTION;
        return version_action_parse(&cli->action.version, arg_count, args);
    }

    print_undefined_argument_call_error(action);
    return 0;
}

inline static void print_empty_string_arg_error(int arg_pos)
{
    char pos_str[64], bold[64];
    sprintf(pos_str, "%d° arg", arg_pos);

    print_error_tag("empty string (%s) isn't a valid argument!\n", string_ansi_stylize(bold, 1, pos_str));
    print_help_flag_tip();
}

inline static void print_expecting_arg_error()
{
    print_error_tag("expecting at least %s argument.\n", BOLD_LITERAL("one"));
    print_help_flag_tip();
}

inline static void print_help_flag_tip()
{
    printerr("consider using the %s flag.\n", BOLD_LITERAL("--help"));
}

inline static void print_undefined_argument_call_error(char *arg)
{
    char bold[1024], magenta[1024];

    print_error_tag("undefined program %s (%s).\n", string_is_program_flag(arg) ? "flag" : "subcommand",
                    string_ansi_stylize(bold, 1, string_ansi_stylize(magenta, 95, arg)));
    print_help_flag_tip();
}
