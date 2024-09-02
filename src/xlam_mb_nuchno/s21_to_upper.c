#include "./s21_string.h"

void *s21_to_upper(const char *str) {
  char *uppered_case = S21_NULL;
  if (str) {
    int len = (int)s21_strlen(str);
    uppered_case = malloc(s21_strlen(str) + 1);
    for (int i = 0; i < len; i++) {
      if (str[i] > 96 && str[i] < 123) {
        uppered_case[i] = str[i] - 32;
      } else {
        uppered_case[i] = str[i];
      }
    }
    uppered_case[len] = '\0';
  }
  return (void *)uppered_case;
}

// TODO
//  Возвращает копию строки (str), преобразованной в верхний регистр. В случае
//  какой-либо ошибки следует вернуть значение NULL.

// void *s21_to_lower(const char *str) Возвращает копию строки (str),
// преобразованной в нижний регистр. В случае какой-либо ошибки следует вернуть
// значение NULL.

// void *s21_insert(const char *src, const char *str, size_t start_index)
// Возвращает новую строку, в которой указанная строка (str) вставлена в
// указанную позицию (start_index) в данной строке (src). В случае какой-либо
// ошибки следует вернуть значение NULL.

// void *s21_trim(const char *src, const char *trim_chars)
// Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src). В
// случае какой-либо ошибки следует вернуть значение NULL.