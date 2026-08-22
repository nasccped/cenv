#ifndef _VERSION_ACTION_H_
#define _VERSION_ACTION_H_

/* Represents a version info single line (such as
 * "<APP_NAME> <TAG_NAME> (<COMMIT_HASH> <COMMIT_DATE>)"). */
typedef struct {
  // refers to version info
  const char
    *app_name,
    *tag_name,
    *commit_hash,
    *commit_date;

  /* Display standard. */
  enum {

    /* Just prints the app_name followed by the tag name. */
    SIMPLE_DISPLAY,

    /* Prints all the data. */
    VERBOSE_DISPLAY

  } display_mode;

} Version;

/* Does the version parsing using a version struct pointer + remaining arguments. */
int parse_version_action(Version *version, int arg_count, char *args[]);

/* Run the version struct pointer action. */
int run_version_action(Version *version);

#endif
