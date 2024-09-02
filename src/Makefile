CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11

all: tests gcov_report string.a


tests :
	checkmk clean_mode=1 tests.check > tests.c | $(CC) $(CFLAGS) s21_*.c tests.c `pkg-config --cflags --libs check`


string.a : 
	$(CC) $(CFLAGS) -c s21_*.c
	ar rcs string.a *.o
# s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memset.c s21_sprintf.c s21_strchr.c s21_strcspn.c s21_strerror.c s21_strlen.c s21_strncat.c s21_strncmp.c s21_strncpy.c s21_strpbrk.c s21_strrchr.c s21_strstr.c s21_strtok.c


clang:
	clang-format -i *.c
	clang-format -n *.c

gcov_report:
	$(CC) $(CFLAGS) -o main tests.c s21_*.c -lcheck -fprofile-arcs -ftest-coverage 
	./main
	lcov --capture --directory . --output-file coverage.info 
	genhtml coverage.info --output-directory out 
	open out/index.html


	

clean : 
	rm -rf *.gcda *.gcno main out coverage.info *.o *.a tests.c