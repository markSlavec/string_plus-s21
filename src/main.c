#include "s21_string.h"
#include <string.h>
#include "s21_sprintf.h"

int main(){
char result[200];


printf("%d", s21_sprintf(result, "print: %d %hd %ld, %+d %+d % d %05d %05d %-5d %5d %.6d %1d %05d", __INT_MAX__, __SHRT_MAX__,
                           __LONG_MAX__, 2, 2, 2, 23, 23, 23, 23, 20, 1, 232));
puts(result);

// instructions to compile:

 // gcc main.c s21_sprintf.c ../s21_strlen.c ../s21_memset.c ../s21_strncpy.c  ../s21_strncat.c ../s21_strchr.c -lm
 // и директории s21_sprintf

 
return 0;
}

