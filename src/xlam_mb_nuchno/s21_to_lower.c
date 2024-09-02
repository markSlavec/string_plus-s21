#include "./s21_string.h"

void *s21_to_lower(const char *str) {
  char *uppered_case = S21_NULL;
  if (str) {
    int len = (int)s21_strlen(str);
    uppered_case = malloc(s21_strlen(str) + 1);
    for (int i = 0; i < len; i++) {
      if (str[i] > 64 && str[i] < 91) {
        uppered_case[i] = str[i] + 32;
      } else {
        uppered_case[i] = str[i];
      }
    }
    uppered_case[len] = '\0';
  }
  return (void *)uppered_case;
}
