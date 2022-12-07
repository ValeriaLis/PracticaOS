#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//для запуска ./example 2 3 5
int main(int argc, char** argv) { //переменные передаються из командной строки
    double a = atof(argv[1]); // преобразовует строку в значение типа double
    double b = atof(argv[2]);
    double c = atof(argv[3]);
    printf("Example -> %.1lfx^2+%.1lfx+%.1lf = 0\n", a, b ,c);
    double d = pow(b,2) - 4*a*c;
    printf("D = b^2-4ac = %.1lf\n", d);
    if(d < 0) {
        printf("D < 0, NO Solutions!\n");
    }
    else if(d == 0) {
        double x1 = (double)-b/(2*a);
        printf("D = 0, one solution -> %2.lf\n", x1);
    }
    else {
        double x1 = (double)(-b + sqrtl(d)) / (2*a);
        double x2 = (double)(-b - sqrtl(d)) / (2*a);
        printf("D > 0, we got two solutions: \nx1 = %.2lf\nx2 = %.2lf\n", x1, x2);
    }
    return 0;
}