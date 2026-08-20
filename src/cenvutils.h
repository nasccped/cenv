#ifndef _CENVUTILS_H_
#define _CENVUTILS_H_
/* This file defines common utilities for cenv runtime, such as print_erro_tag, string mode
 * checkers and so on... */

/* Refers to all available ansi color escapes. They're tagged if it's respective integer value
 * (which must be handled based on the put qualifier (foreground/background)). */
typedef enum {

  // means no color
  NONE_COLOR = -1,

  // normal colors
  BLACK   = 0,
  RED     = 1,
  GREEN   = 2,
  YELLOW  = 3,
  BLUE    = 4,
  MAGENTA = 5,
  CYAN    = 6,
  WHITE   = 7,

  // bright colors.
  BRIGHT_BLACK   = 60,
  BRIGHT_RED     = 61,
  BRIGHT_GREEN   = 62,
  BRIGHT_YELLOW  = 63,
  BRIGHT_BLUE    = 64,
  BRIGHT_MAGENTA = 65,
  BRIGHT_CYAN    = 66,
  BRIGHT_WHITE   = 67

} AnsiColorVariant;

/* Refers to available ansi format styles. */
typedef enum {
  NONE_STYLE = -1,
  BOLD       = 1,
  ITALIC     = 3
} AnsiStyleVariant;

/* Refers to an ansi colored string. */
typedef struct {

  /* Style being used, such as bold, italic and so on... */
  AnsiStyleVariant stl;

  
  AnsiColorVariant
    /* Color variant being used on foreground. */
    fg,
    /* Color variant being used on background. */
    bg;

  /* String pointer being held. */
  char *s;

} ColoredString;

/* Set new values on a 'ColoredString' pointer. Note that this function only works if 'cs' points
 * to a non NULL address. 'string' pointer can also be null. If so, 'ColoredString.s' field gonna
 * point to an empty string. */
void colored_string_set_values(
  ColoredString *cs,
  AnsiStyleVariant stl,
  AnsiColorVariant fg,
  AnsiColorVariant bg,
  char *s
);

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

/* Sets 's' string inner value based on cs fields. Note that this function doesn't run overflow
 * checking. Just be sure about string mem size. */
void string_set_from_colored_string(char *s, ColoredString *cs);

#endif
