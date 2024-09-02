#include "s21_string.h"

s21_size_t s21_strcspn(const char *str, const char *input) {
  s21_size_t len = 0;
  int flag = 1;
  const char *start = input;

  if (str == S21_NULL || input == S21_NULL) {
    return len;
  } else {
    while (*str != '\0' && flag == 1) {
      input = start;
      while (*input != '\0') {
        if (*str == *input) {
          flag = 0;
          break;
        } else
          input++;
      }

      if (flag == 1) {
        len++;
        str++;
      }
    }
  }
  return len;
}