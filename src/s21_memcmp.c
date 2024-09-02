#include "s21_string.h"

// int s21_memcmp(void *arr1, void *arr2, s21_size_t size) {
//   int result = 0;

//   char *ptr1 = (char *)arr1;
//   char *ptr2 = (char *)arr2;
//   for (int i = 0; result == 0 && ptr1[i] != '\0' && i < size; i += 1)
//     result = ptr1[i] - ptr2[i];

//   return result;
// }

int s21_memcmp(const void *arr1, const void *arr2, s21_size_t size) {
  unsigned char *temp1 = (unsigned char *)arr1;
  unsigned char *temp2 = (unsigned char *)arr2;
  for (s21_size_t i = 0; i < size; ++i) {
    if (temp1[i] != temp2[i]) {
      return temp1[i] - temp2[i];
    }
  }
  return 0;
}
