#include "s21_string.h"

char* s21_strstr(const char* haystack, const char* needle) {
  char* result = S21_NULL;
  if (!*needle) {  // Проверка на пустое значение
    result = (char*)haystack;
  } else {
    for (const char* h = haystack; *h; h++) {
      const char* h_iter = h;
      const char* n_iter = needle;

      while (*h_iter && *n_iter && *h_iter == *n_iter) {  // Перебираем
        h_iter++;
        n_iter++;
      }

      // Если дошел до конца, вхождение найдено
      if (!*n_iter) {
        result = (char*)h;
        break;
      }
    }
  }

  return result;
}
