#include <stdio.h>
#include <string.h>
#include "cenvutils.h"
#include "version_action.h"

// default value for verbose flag.
#define LONG_FLAG "--long"

/* Set version data values (from gcc args defines). */
void set_version_data_fields(Version *version);

int version_action_parse(Version *version, int arg_count, char *args[]) {
  int display_mode_set;

  // set data
  set_version_data_fields(version);

  display_mode_set = 0;

  // for each arg.
  for (int i = 0; i < arg_count; i++) {

    // when refers to verbose flag
    if (strcmp(args[i], LONG_FLAG) == 0) {

      // if already done
      if (display_mode_set) {
        print_error_tag("%s flag passed twice.\n", LONG_FLAG);
        return 0;
      }

      // set mode.
      version->display_mode = LONG_DISPLAY;
      display_mode_set++;
      continue;
    }

    print_error_tag(
      "unrecognized version %s (%s)!\n",
      string_is_program_flag(args[i]) ? "flag" : "subcommand",
      args[i]
    );
    printerr("available flags are '%s' only.\n", LONG_FLAG);

    return 0;
  }

  return 1;
}

int run_version_action(Version *version) {
  if (!version) {
    printerr("(bad program): version pointer was unexpectedly <NULL>.\n");
    return 0;
  }

  // print name and tag by default
  printf("%s %s", version->app_name, version->tag_name);

  // print commit + date if verbose
  if (version->display_mode == LONG_DISPLAY) {
    printf(" (%s %s)", version->commit_hash, version->commit_date);
  }

  printf("\n");

  return 1;
}

void set_version_data_fields(Version *version) {
  if (!version)
    return;

  // those values must be defined on GCC's compilation argv since they're get from dev environment.
  version->app_name = APP_NAME;
  version->tag_name = TAG_NAME;
  version->commit_hash = TAG_COMMIT_HASH;
  version->commit_date = TAG_COMMIT_DATE;
}
