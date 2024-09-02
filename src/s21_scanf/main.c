#include "s21_string.h"
#include "s21_sscanf.h"
#include <string.h> 

    int main() {
    char str[20] = "12.123";
    //long int a = 0x0;
    float number21 = 0, number = 0;
    int k;
    char arr[30];
    s21_sscanf(str, "%f", &number21);
    sscanf(str, "%f", &number);
    printf("%f\n%f", number21, number);
    // if(k== 1){
    //     printf("!%d!", number);
    // }else{
    //     printf("no");
    // }
    return 0;
}
