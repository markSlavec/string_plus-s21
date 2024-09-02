#include "./s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *dest_work = dest;
  s21_size_t i;
  while (*dest_work) {
    dest_work++;
  }
  for (i = 0; i < n; i++) {
    dest_work[i] = src[i];
  }
  dest_work[i] = '\0';
  return dest;
}