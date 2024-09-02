#include <stdio.h>
#include <stdlib.h>

typedef unsigned long s21_size_t;
#define S21_NULL (void *)0


s21_size_t s21_strlen(char* str);
char* s21_strpbrk(char* str1, char* str2);
char* s21_strerror(int errno);

