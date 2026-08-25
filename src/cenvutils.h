#ifndef _CENVUTILS_H_
#define _CENVUTILS_H_
/* This file defines common utilities for cenv runtime, such as print_erro_tag, string mode
 * checkers and so on... */

/* Applies bold escape sequence for string literals (ONLY). */
#define BOLD_LITERAL(STR) "\x1b[1m" STR "\x1b[0m"

/* Applies bold + bright red escape sequence for string literals (ONLY). */
#define BOLD_BRIGHT_RED_LITERAL(STR) "\x1b[1;91m" STR "\x1b[0m"

/* Applies bold + bright cyan escape sequence for string literals (ONLY). */
#define BOLD_BRIGHT_CYAN_LITERAL(STR) "\x1b[1;96m" STR "\x1b[0m"

/* Applies bright white escape sequence for string literals (ONLY). */
#define BRIGHT_WHITE_LITERAL(STR) "\x1b[97m" STR "\x1b[0m"

/* Print an error tag to stderr (automatically). Note that this function doesn't automatically adds
 * newline at the end. You must handle it manually! */
void print_error_tag(const char *restrict fmt, ...);

/* Print a note tag to std(out/err) (decided by using the 'is_err' param). Note that this function
 * doesn't automatically adds newline at the end. You must handle it manually! */
void print_note_tag(int is_err, const char *restrict fmt, ...);

/* Prints content directly to stderr (shorthand for 'fprintf(stderr, ...'). */
void printerr(const char *restrict fmt, ...);

/* Returns if the provided char pointer refers to a recognizable program flag (such as --help,
 * --version, ...). Note that this function will also returns '0' if s refers to NULL or
 *  zero-length string. */
int string_is_program_flag(char *s);

/* Returns if the provided char pointer refers to NULL / zero-length / whitespace only string. */
int string_is_whitespace(char *s);

/* Apply ansi escape styling to a given dest char pointer. This function also returns the dest
 * address.
 *
 * WARN: dest and source pointer shouldn't be the same address (even if enough size). This function
 *       works with 'sprintf' function and passing 'sprintf(s, "%s...", s, ...)' can leads to
 *       undefined behavior. */
char *string_ansi_stylize(char *dest, int style, char *source);

#endif
