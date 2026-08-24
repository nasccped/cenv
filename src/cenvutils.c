#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "cenvutils.h"

/* Default string being used when string param (on 'colored_string_set_values') points to null. */
#define COLORED_STRING_DEFAULT_STRING ""

/* Aux definition used within tag definitions. */
#define WHITE_DOUBLE_COLON BRIGHT_WHITE_LITERAL(":")

/* Kind of tag when calling 'print_error_tag' function. */
#define ERROR_TAG BOLD_BRIGHT_RED_LITERAL("error") WHITE_DOUBLE_COLON

/* Kind of tag when calling 'print_note_tag' function. */
#define NOTE_TAG BOLD_BRIGHT_CYAN_LITERAL("note") WHITE_DOUBLE_COLON

void print_error_tag(const char *restrict fmt, ...) {
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "%s ", ERROR_TAG);
  vfprintf(stderr, fmt, args);
  va_end(args);
}

void print_note_tag(int is_err, const char *restrict fmt, ...) {
  va_list args;
  va_start(args, fmt);
  fprintf(is_err ? stderr : stdout, "%s ", NOTE_TAG);
  vfprintf(is_err ? stderr : stdout, fmt, args);
  va_end(args);
}

void printerr(const char *restrict fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
}

int string_is_program_flag(char *s) {
  size_t slen;

  if (!s || !(slen = strlen(s)))
    return 0;

  for (size_t i = 0; i < slen; i++) {
    if (s[i] == '-')
      return 1;
  }

  return 0;
}

int string_is_whitespace(char *s) {
  size_t slen;

  // if null or zero-length
  if (!s || !(slen = strlen(s)))
    return 1;

  // for each char.
  for (size_t i = 0; i < slen; i++) switch (s[i]) {
    // refers to whitespace
    case ' ':
    case '\t':
    case '\n':
      // go next
      break;

    // non whitespace
    default:
      return 0;
  }

  // final instruction means only whitespace chars found
  return 1;
}

char *string_ansi_stylize(char *dest, int style, char *source) {
  if (!dest)
    return NULL;

  if (style <= 0) {
    sprintf(dest, "%s", source);
    return dest;
  }

  sprintf(dest, "\x1b[%dm%s\x1b[0m", style, source);
  return dest;
}
