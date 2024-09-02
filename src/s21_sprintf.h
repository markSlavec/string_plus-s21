#include "s21_string.h"
#include <stdarg.h>
#include <math.h>

#define BUFFER_SIZE 10000

typedef struct {
    bool minus; //
    bool plus; //
    bool space;
    bool zero; //
    bool hash;
    int precision; //
    int is_precision_set; //
    int width; //
    char length; //
    char specifier; //
} Spec;

int s21_sprintf(char *str, const char *format, ...);
const char *specs_define(Spec *specs, const char *format);
const char *width_precicion_define(const char *format, Spec *specs, va_list arguments);
int array_to_int(char *buffer);
const char *length_define(const char *format, Spec *specs);
void processing(Spec *specs, char *buffer_str, va_list arguments);
void integer_strategy(Spec *specs, char *buffer_str, va_list arguments);
void integer_to_char_array(long num, char *buff);
void precision_processing(Spec *specs, char *buffer_str);
void flags_processing(Spec *specs, char *buffer_str);
void clean_buffer(char *buffer);
void unsigned_strategy(Spec *specs, char *buffer_str, va_list arguments);
void unsigned_to_array(long val, char *buff, int base);
void octal_strategy(Spec *specs, char *buffer_str, va_list arguments);
void hex_strategy(Spec *specs, char *buffer_str, va_list arguments);
void char_strategy(Spec *specs, char *buffer_str, va_list arguments);
void string_strategy(Spec *specs, char *buffer_str, va_list arguments);
void pointer_strategy(Spec *specs, char *buffer_str, va_list arguments);
void float_strategy(Spec *specs, char *buffer_str, va_list arguments);
void double_to_string(long double val, char *ret, Spec f);
void mantiss_strategy(Spec *specs, char *buffer_str, va_list arguments);
void mantiss(char *buffer_str, int pow, char sign, Spec *specs);
void gG_strategy(Spec *specs, char *buffer_str, va_list arguments);
void remove_trailing_zeroes(char *buffer_str) ;
void format_gG_precision(char *buff, int precision, Spec *specs, int flag_g_f);




