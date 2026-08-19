#include <stdio.h>
#include <stdarg.h>
#include "printutils.h"

void print_err(const char *restrict fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
}

void print_out(const char *restrict fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}
