#include "s21_string.h"

char *s21_strrchr(const char *s, int c) {
  const char *last = S21_NULL;
  if (c == '\0') last = "";

  while (*s != '\0') {
    if (*s == c) last = s;
    s++;
  }
  return (char *)last;
}
