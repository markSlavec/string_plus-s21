#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <check.h>

#define S21_NULL ((void *)0)
typedef unsigned long long s21_size_t;

void *s21_memchr(const void *str, int c, s21_size_t size);
int s21_memcmp(const void *arr1, const void *arr2, s21_size_t size);
void *s21_memcpy(void *dest, const void *src, s21_size_t size);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strrchr(const char *s, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
s21_size_t s21_strlen(const char* str);
char* s21_strpbrk(char* str1, char* str2);
char* s21_strerror(int errno);
s21_size_t s21_strcspn(const char *str, const char *input);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
void *s21_to_upper(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_to_lower(const char *str);

void *s21_trim(const char *src, const char *trim_chars);
int is_part_of_trim(char curr_symb, const char *trim_chars,
                    s21_size_t trim_len);
s21_size_t calculate_end_print_ind(const char *src, const char *trim_chars,
                                   s21_size_t src_len, s21_size_t trim_len);
s21_size_t calculate_start_print_ind(const char *src, const char *trim_chars,
                                     s21_size_t src_len, s21_size_t trim_len);
