#include "./s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *target = S21_NULL;
  s21_size_t i = 0;
  if (c == 0) {
    target = "";
  } else {
    while (target == S21_NULL && i < s21_strlen(str)) {
      if (str[i] == c) target = (char *)(str + i);
      i++;
    }
  }
  return target;
}