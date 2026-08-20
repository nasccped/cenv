#ifndef _CENVUTILS_H_
#define _CENVUTILS_H_
/* This file defines common utilities for cenv runtime, such as print_erro_tag, string mode
 * checkers and so on... */

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

#endif
