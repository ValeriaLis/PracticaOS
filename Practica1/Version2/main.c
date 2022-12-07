#include <stdio.h>
#include "g.h"
#include "f.h"

int main() {
    float x;
    printf("Input x: ");
    scanf("%f", &x);
    printf("Result: %.5f", f(x));
    printf("\nResult: %.5f\n",g(x));
    return 0;
}
