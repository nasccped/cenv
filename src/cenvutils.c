#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "cenvutils.h"

/* Default string being used when string param (on 'colored_string_set_values') points to null. */
#define COLORED_STRING_DEFAULT_STRING ""

/* Default 'ColoredString' data for double colon when printing tags. */
static const ColoredString COLORED_STRING_DOUBLE_COLON_TAG = {
  .stl = NONE_STYLE,
  .fg = BRIGHT_WHITE,
  .bg = NONE_COLOR,
  .s = ":"
};

/* Default 'ColoredString' data for error tag.
 * NOTE: It only refers to the 'error' string, not the double colon.  */
static const ColoredString COLORED_STRING_ERROR_TAG = {
  .stl = BOLD,
  .fg = BRIGHT_RED,
  .bg = NONE_COLOR,
  .s = "error"
};

/* Default 'ColoredString' data for note tag.
 * NOTE: It only refers to the 'note' string, not the double colon.  */
static const ColoredString COLORED_STRING_NOTE_TAG = {
  .stl = BOLD,
  .fg = BRIGHT_CYAN,
  .bg = NONE_COLOR,
  .s = "note"
};

void colored_string_set_values(
  ColoredString *cs,
  AnsiStyleVariant stl,
  AnsiColorVariant fg,
  AnsiColorVariant bg,
  char *s
) {
  if (!cs)
    return;

  cs->stl = stl;
  cs->fg = fg;
  cs->bg = bg;
  cs->s = s ? s : COLORED_STRING_DEFAULT_STRING;
}

void print_error_tag(const char *restrict fmt, ...) {
  char error_tag_string[32], double_colon_string[16];
  va_list args;

  va_start(args, fmt);
  string_set_from_colored_string(
    error_tag_string,
    (ColoredString *) &COLORED_STRING_ERROR_TAG
  );
  string_set_from_colored_string(
    double_colon_string,
    (ColoredString *) &COLORED_STRING_DOUBLE_COLON_TAG
  );

  fprintf(stderr, "%s%s ", error_tag_string, double_colon_string);
  vfprintf(stderr, fmt, args);

  va_end(args);
}

void print_note_tag(int is_err, const char *restrict fmt, ...) {
  FILE *dest = is_err ? stderr : stdout;
  char note_tag_string[32], double_colon_string[16];
  va_list args;

  va_start(args, fmt);
  string_set_from_colored_string(
    note_tag_string,
    (ColoredString *) &COLORED_STRING_NOTE_TAG
  );
  string_set_from_colored_string(
    double_colon_string,
    (ColoredString *) &COLORED_STRING_DOUBLE_COLON_TAG
  );

  fprintf(dest, "%s%s ", note_tag_string, double_colon_string);
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

void string_set_from_colored_string(char *s, ColoredString *cs) {
  // create temp string buffer (store ansi escape) and string buffer length.
  char temp_string[16] = {0};
  int tslen = 0;

  if (!s || !cs)
    return;

  // if some style being used.
  if (cs->stl != NONE_STYLE)
    tslen += sprintf(temp_string, "\x1b[%d", cs->stl);

  // if some foreground color being used.
  if (cs->fg != NONE_COLOR) {
    // if buffer still empty.
    if (!tslen)
      tslen += sprintf(temp_string, "\x1b[%d", cs->fg + 30);

    // else, add fg param
    else
      tslen += sprintf(temp_string + tslen, ";%d", cs->fg + 30);
  }

  // if some background color being used.
  if (cs->bg != NONE_COLOR) {
    // if buffer still empty.
    if (!tslen)
      tslen += sprintf(temp_string, "\x1b[%d", cs->bg + 40);

    // else, add fg param
    else
      tslen += sprintf(temp_string + tslen, ";%d", cs->bg + 40);
  }

  if (tslen)
    sprintf(s, "%sm%s\x1b[0m", temp_string, cs->s);
  else
    sprintf(s, "%s", cs->s);
}
