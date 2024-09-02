#include "./s21_string.h"

s21_size_t calculate_start_print_ind(const char *src, const char *trim_chars,
                                     s21_size_t src_len, s21_size_t trim_len) {
  int start_print_ind = 0;
  for (s21_size_t i = 0; i < src_len && !start_print_ind; i++) {
    if (!is_part_of_trim(src[i], trim_chars, trim_len)) {
      start_print_ind = i;
    }
    if (i == src_len - 1) {
      start_print_ind = 0;
    }
  }
  return start_print_ind;
}

s21_size_t calculate_end_print_ind(const char *src, const char *trim_chars,
                                   s21_size_t src_len, s21_size_t trim_len) {
  int end_print_ind = src_len - 1;
  int stop_cycle = 0;
  for (int i = src_len - 1; i >= 0 && !stop_cycle;
       i--) {  // возмодно тут в инте писать тип данных не int, а s21_size_t
    if (!is_part_of_trim(src[i], trim_chars, trim_len)) {
      if ((s21_size_t)i != src_len - 1) {
        end_print_ind = i + 1;
        stop_cycle = 1;
      } else {
        end_print_ind = i;
        stop_cycle = 1;
      }
    }
    if (i == 0 && stop_cycle == 0) {
      end_print_ind = 0;
    }
  }
  return end_print_ind;
}

int is_part_of_trim(char curr_symb, const char *trim_chars,
                    s21_size_t trim_len) {
  int is_part = 0;
  for (s21_size_t i = 0; i < trim_len && !is_part; i++) {
    if (curr_symb == trim_chars[i]) {
      is_part = 1;
    }
  }
  return is_part;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *processed_str = S21_NULL;
  if (src && trim_chars) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t trim_len = s21_strlen(trim_chars);
    processed_str = calloc(src_len + 1, sizeof(char));
    int is_begins_with_trim_set = 0;
    int is_ends_with_trim_set = 0;
    s21_size_t start_print_ind = 0;
    s21_size_t end_print_ind = src_len - 1;
    for (s21_size_t i = 0; i < trim_len; i++) {
      if (trim_chars[i] == src[0]) is_begins_with_trim_set = 1;
      if (trim_chars[i] == src[src_len - 1]) is_ends_with_trim_set = 1;
    }

    if (is_begins_with_trim_set) {
      start_print_ind =
          calculate_start_print_ind(src, trim_chars, src_len, trim_len);
    }
    if (is_ends_with_trim_set) {
      end_print_ind =
          calculate_end_print_ind(src, trim_chars, src_len, trim_len);
    }
    if (start_print_ind != end_print_ind) {
      if (start_print_ind == 0 && end_print_ind == (src_len - 1)) {
        for (s21_size_t i = 0; i < src_len; i++) {
          processed_str[i] = src[i];
        }
        processed_str[src_len] = '\0';
      } else if (src_len == end_print_ind + 1) {
        int j = 0;
        for (s21_size_t i = start_print_ind; i < end_print_ind + 1; i++, j++) {
          processed_str[j] = src[i];
        }
        processed_str[j + 1] = '\0';
      } else {
        int j = 0;
        for (s21_size_t i = start_print_ind; i < end_print_ind; i++, j++) {
          processed_str[j] = src[i];
        }
        processed_str[j + 1] = '\0';
      }
    }
  }
  return (void *)processed_str;
}

// реализовать функцию: цикл проходит по триму, проверяет начинается ли первый и
// последний символ строки хотя бы одним символом из набора, и сохраняет это в
// флаг

// void *s21_trim(const char *src, const char *trim_chars)
// Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src). В
// случае какой-либо ошибки следует вернуть значение NULL.

// Если начинается с набора, то идем по строке пока совпадает с набором

// Нужно проверить как должен работать трим, если первая строка пустая, а также,
// как очищать память в тестах, в случаях когда в trim и insert она и не
// выделялась