#include "s21_string.h"

// Проверка, является ли символ разделителем
int is_delimiter(char ch, const char* delim) {
  while (*delim) {
    if (ch == *delim) {
      return 1;
    }
    delim++;
  }
  return 0;
}

char* s21_strtok(char* str, const char* delim) {
  static char* last = S21_NULL;  // указатель для запоминания позиции в строке
  if (str != S21_NULL) {
    last = str;  // если передана новая строка, начинаем с нее
  }
  if (last == S21_NULL) {
    return S21_NULL;  // если конец строки, возвращаем S21_NULL
  }

  // пропускаем начальные разделители
  while (*last && is_delimiter(*last, delim)) {
    last++;
  }

  if (*last == '\0') {
    return S21_NULL;  // если достигнут конец строки после пропуска
                      // разделителей, возвращаем S21_NULL
  }

  char* token_start = last;  // начало токена
  while (*last && !is_delimiter(*last, delim)) {
    last++;
  }

  if (*last) {
    *last = '\0';  // заменяем разделитель на '\0'
    last++;  // переходим к следующему символу после разделителя
  } else {
    last = S21_NULL;  // если достигнут конец строки, запоминаем это
  }

  return token_start;
}
