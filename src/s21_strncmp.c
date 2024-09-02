#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  s21_size_t counter = 0;

  while (counter < n) {
    if (*str1 == '\0' && *str2 == '\0')
      break;
    else {
      if (*str1 == *str2)
        result = 0;
      else {
        if (*str1 > *str2)
          result = 1;
        else
          result = -1;

        break;
      }

      str1++;
      str2++;
      counter++;
    }
  }
  return result;
}