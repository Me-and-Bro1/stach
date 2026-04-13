#pragma once
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t parse_uint(const char *str, const char *opt_name) {
  char *end;
  errno = 0;
  const uint64_t val = strtoull(str, &end, 10);

  if (errno != 0 || end == str || *end != '\0') {
    fprintf(stderr, "Error: invalid number for %s: '%s'\n", opt_name, str);
    exit(EXIT_FAILURE);
  }
  return val;
}
