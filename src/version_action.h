#ifndef _VERSION_ACTION_H_
#define _VERSION_ACTION_H_

/* Represents a version info single line (such as
 * "<APP_NAME> <TAG_NAME> (<COMMIT_HASH> <COMMIT_DATE>)"). */
typedef struct
{
    /* Refers to the core 'version' action. */
    struct
    {
        const char

            /* App name of the binary. */
            *app_name,

            /* Current tag annotation (git repo required). */
            *tag_annotation;

    } core_data;

    /* Refers when some kind of 'long' variant is called (such as '--long' or '--extra-long'). */
    struct
    {
        /* Which variant was used to call long mode. */
        enum
        {
            /* Long wasn't called. */
            LONG_MODE_DISABLED,

            /* Long was called. */
            LONG_MODE_ENABLED,

            /* Extra-Long was called. */
            EXTRA_LONG_MODE_ENABLED

        } long_mode;

        /* Commit hash data. */
        struct
        {
            const char

                /* Short commit hash. */
                *short_hash,

                /* Full commit hash. */
                *full_hash;

        } commit_hash;

        /* Commit date. */
        const char *commit_date;

    } long_data;

} Version;

/* Does the version parsing using a version struct pointer + remaining
 * arguments. */
int version_action_parse(Version *version, int arg_count, char *args[]);

/* Run the version struct pointer action. */
int run_version_action(Version *version);

#endif
