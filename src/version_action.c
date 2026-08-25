#include "version_action.h"
#include "cenvutils.h"
#include <stdio.h>
#include <string.h>

#define LONG_FLAG "--long"
#define EXTRA_LONG_FLAG "--extra-long"

#define IS_LONG_FLAG(STR) strcmp((STR), LONG_FLAG) == 0
#define IS_EXTRA_LONG_FLAG(STR) strcmp((STR), EXTRA_LONG_FLAG) == 0

#define IS_VERSION_LONG_MODE_ENABLED(VERSION_PTR) (VERSION_PTR)->long_data.long_mode == LONG_MODE_ENABLED
#define IS_VERSION_EXTRA_LONG_MODE_ENABLED(VERSION_PTR) (VERSION_PTR)->long_data.long_mode == EXTRA_LONG_MODE_ENABLED

/* Prints 'consider using version --help' hint to stderr. */
void print_version_help_hint();

/* Set version data values (from gcc args defines). */
void set_version_data_fields(Version *version);

int version_action_parse(Version *version, int arg_count, char *args[])
{
    char magenta[1024], bold[1024];

    // set data
    set_version_data_fields(version);

    for (int i = 0; i < arg_count; i++)
    {
        if (IS_LONG_FLAG(args[i]))
        {
            if (IS_VERSION_LONG_MODE_ENABLED(version))
            {
                print_error_tag("passing %s flag twice isn't allowed.\n", BOLD_LITERAL(LONG_FLAG));
                print_version_help_hint();
                return 0;
            }
            else if (IS_VERSION_EXTRA_LONG_MODE_ENABLED(version))
            {
                print_error_tag("%s flag conflicts with %s.\n", BOLD_LITERAL(EXTRA_LONG_FLAG), BOLD_LITERAL(LONG_FLAG));
                printerr("you must choose between one of them.\n\n");
                print_note_tag(1, "");
                print_version_help_hint();
                return 0;
            }
            version->long_data.long_mode = LONG_MODE_ENABLED;
        }
        else if (IS_EXTRA_LONG_FLAG(args[i]))
        {
            if (IS_VERSION_LONG_MODE_ENABLED(version))
            {
                print_error_tag("%s flag conflicts with %s.\n", BOLD_LITERAL(LONG_FLAG), BOLD_LITERAL(EXTRA_LONG_FLAG));
                printerr("you must choose between one of them.\n\n");
                print_note_tag(1, "");
                print_version_help_hint();
                return 0;
            }
            else if (IS_VERSION_EXTRA_LONG_MODE_ENABLED(version))
            {
                print_error_tag("passing %s flag twice isn't allowed.\n", BOLD_LITERAL(LONG_FLAG));
                print_version_help_hint();
                return 0;
            }
            version->long_data.long_mode = EXTRA_LONG_MODE_ENABLED;
        }
        else
        {
            print_error_tag("undefined version %s (%s).\n", string_is_program_flag(args[i]) ? "flag" : "subcommand",
                            string_ansi_stylize(bold, 1, string_ansi_stylize(magenta, 95, args[i])));
            print_version_help_hint();
            return 0;
        }
    }

    return 1;
}

int run_version_action(Version *version)
{
    const char *app_name, *tag_annotation, *commit_hash, *commit_date;

    if (!version)
    {
        printerr("(bad program): version pointer was unexpectedly <NULL>.\n");
        return 0;
    }

    app_name = version->core_data.app_name;
    tag_annotation = version->core_data.tag_annotation;
    commit_hash = version->long_data.long_mode == LONG_MODE_ENABLED         ? version->long_data.commit_hash.short_hash
                  : version->long_data.long_mode == EXTRA_LONG_MODE_ENABLED ? version->long_data.commit_hash.full_hash
                                                                            : NULL;
    commit_date = version->long_data.commit_date;

    // print name and tag by default
    printf("%s %s", app_name, tag_annotation);

    // if no long mode
    if (commit_hash)
    {
        printf(" (%s %s)", commit_hash, commit_date);
    }

    printf("\n");
    return 1;
}

void print_version_help_hint()
{
    printerr("consider using %s.\n", BOLD_LITERAL("cenv version --help"));
}

void set_version_data_fields(Version *version)
{
    if (!version)
        return;

    // those values must be defined on GCC's compilation argv since they're get
    // from dev environment.
    version->core_data.app_name = APP_NAME;
    version->core_data.tag_annotation = TAG_ANNOTATION;
    version->long_data.commit_hash.short_hash = SHORT_COMMIT_HASH;
    version->long_data.commit_hash.full_hash = FULL_COMMIT_HASH;
    version->long_data.commit_date = COMMIT_DATE;
}
