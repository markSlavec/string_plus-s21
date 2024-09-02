#include "./s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *processed_str = S21_NULL;
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  if (src_len >= start_index) {
    processed_str = malloc(src_len + str_len + 1);
    int j = 0;
    int k = start_index;
    for (s21_size_t i = 0; i < start_index; i++) {
      processed_str[i] = src[i];
    }
    for (s21_size_t i = start_index; i < str_len + start_index; i++) {
      processed_str[i] = str[j];
      j++;
    }
    for (s21_size_t i = start_index + str_len; i < src_len + str_len; i++) {
      processed_str[i] = src[k++];
    }
    processed_str[src_len + str_len] = '\0';
  }
  return (void *)processed_str;
}

// void *s21_insert(const char *src, const char *str, size_t start_index)
// Возвращает новую строку, в которой указанная строка (str) вставлена в
// указанную позицию (start_index) в данной строке (src). В случае какой-либо
// ошибки следует вернуть значение NULL.

//что надо сделать - сдвинуть начиная со старт индекс все элементы на str_len
//позиций
//