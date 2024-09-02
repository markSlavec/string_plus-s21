#include "s21_string.h"

char* s21_strpbrk(char* str1, char* str2) {
  int flag = 0;
  char* temp = str2;
  while (*str1 != '\0' && flag == 0) {
    while (*str2 != '\0' && flag == 0) {
      if (*str1 != *str2 && flag == 0) {
        str2++;
      } else {
        flag = 1;
      }
    }
    if (flag == 0) {
      str1++;
      str2 = temp;
    }
  }
  return flag ? str1 : S21_NULL;
}