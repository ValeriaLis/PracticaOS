#include "math.h"

float g(float x){
    float result;
    result = expf(-fabsf(x)) * cosf(x);
    return result;
}