#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <ctype.h>
#include "s21_string.h"

typedef struct TYPE{
    int d;
    int i;
    int c;
    int f;
    int s;
    int o;
    int x;
    int X;
    int g;
    int G;
    int u;
    int p;
    int e;
    int E;
    int n;
    int flag;
    int l;
    int h;
    int L;
} type;

int s21_sscanf(const char* str, const char* format, ...);
void Specifier(int flag, type type, const char** str, int* count_elements, int* p_d, char* p_c, float* p_f, char* p_s, int* p_i, int* p_o, int* p_x, float* p_g, int* p_u, void** p_p, int* p_n, va_list arg, int* count_specifier, int* count_n, short* ph_d, short* ph_i, short* ph_o, short* ph_u,short* ph_x);
void Specifier_c(const char** str, int* count_elements, char** p_c, int* count_n);
int Specifier_d(const char** str, int* count_elements, int** p_d, int* count_n);
int Specifier_i(const char** str, int* count_elements, int** p_i, int* count_n);
int Specifier_f(const char** str, int* count_elements, float** p_f, int* count_n);
int Specifier_g(const char** str, int* count_elements, float** p_g, int* count_n);
int Specifier_o(const char** str, int* count_elements, int** p_o, int* count_n);
void Specifier_s(const char** str, int* count_elements, char** p_s, int* count_n);
int Specifier_u(const char** str, int* count_elements, int** p_u, int* count_n);
int Specifier_x(const char** str, int* count_elements, int** p_x, int* count_n);
int Specifier_p(const char** str, int* count_elements, void** p_p, int* count_n);
int Specifier_n(const char** str, int* count_elements, int* p_n, int* count_n);

int s21_parcer(char format, type* type);
void refresh_structure(type* type);

int Hexadecimal_system_or_Octal_system(const char** str, int* count_num,int *count_n);
int to_Hexadecimal_system(int sum);
int to_Octal_system(int sum);
void sign(const char** str, int* negative_degree, int* positive_degree, int* degree, int* flag, int* count_n);
void degrees(int negative_degree, int positive_degree, float* sum, int degree);
void count_numbers(const char** str, int* flag, int* count_num, int* plus, int* minus);
void count_sum_before_dot(int* count_num, float* sum, const char** str, int* count_n);
void skip_space(const char** str, int* space, int* number, int* count_n);
void sign_processing(int* flag, int* minus, int* plus, const char** str, int* count_num);
void sign_processing_for_i(int* flag, int* minus, int* plus, const char** str, int* count_num, int* x, int* count_n);
