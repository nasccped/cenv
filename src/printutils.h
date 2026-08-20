#ifndef _PRINTUTILS_H_
#define _PRINTUTILS_H_
/* This file defines printing utilities for the entire program. It isn't a big definition file.
 * That's just a way to avoid printf and fprintf misuse when logging to final user. */

/* Prints the formated string directly to stderr. */
void print_err(const char *restrict fmt, ...);

/* Prints the formated string directly to stdout. */
void print_out(const char *restrict fmt, ...);

#endif
