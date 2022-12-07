#include "math.h"

float f(float x){
    float result;
    result = expf(-fabsf(x))* sinf(x);
    return result;
}