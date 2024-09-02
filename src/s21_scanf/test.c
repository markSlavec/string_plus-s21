#include <stdio.h>
#include <math.h>

int main() {
    double num = 3.14159;

    printf("Округление вверх: %.2f\n", ceil(num));
    printf("Округление вниз: %.2f\n", floor(num));
    printf("Округление к ближайшему целому: %.2f\n", round(num));
    printf("Удаление десятичной части: %.2f\n", trunc(num));

    return 0;
}
