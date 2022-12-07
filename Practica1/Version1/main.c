#include <stdio.h>
#include <math.h>
float f(float x){
    float result;
    result = expf(-fabsf(x))* sinf(x);
    return result;
}

float g(float x){
    float result;
    result = expf(-fabsf(x)) * cosf(x);
    return result;
}
int main() {
    float x;
    printf("Input x: ");
    scanf("%f", &x);
    printf("Result: %.5f", f(x));
    printf("\nResult: %.5f\n",g(x));
    return 0;
}
