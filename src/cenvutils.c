#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "cenvutils.h"

/* Error tag string (being used on 'print_error_tag' function). */
#define ERROR_TAG "\x1b[91merror\x1b[97m:\x1b[0m"

/* Note tag string (being used on 'print_error_tag' function). */
#define NOTE_TAG "\x1b[96mnote\x1b[97m:\x1b[0m"

void print_error_tag(const char *restrict fmt, ...) {
  va_list args;
  va_start(args, fmt);

  fprintf(stderr, "%s ", ERROR_TAG);
  vfprintf(stderr, fmt, args);

  va_end(args);
}

void print_note_tag(int is_err, const char *restrict fmt, ...) {
  FILE *dest = is_err ? stderr : stdout;
  va_list args;
  va_start(args, fmt);

  fprintf(dest, "%s ", NOTE_TAG);
  vfprintf(dest, fmt, args);

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
