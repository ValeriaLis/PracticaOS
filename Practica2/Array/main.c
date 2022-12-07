#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* generateArray(int length, double min, double max);
double AverageValue(int* arr, int length);
int AmountValues(int* arr, int length, double number);
int FirstNegative(int* arr, int length);
double SumAbs(int* arr, int length, int startIndex);

int main() {
    int arrayLength = 10;
    srand(time(NULL));

    int* arr = generateArray(arrayLength, -10, 10);

    // Среднее значение элементов массива
    double value = AverageValue(arr, arrayLength);
    int amount = AmountValues(arr, arrayLength, value);

    printf("Average value is %.2lf\n", value);
    printf("Amount elements bigger than %.2lf is %d\n\n",value, amount);

    int index = FirstNegative(arr, arrayLength);

    if (index != -1) {
        double sum = SumAbs(arr, arrayLength, index);
        printf("Result after first negative number is %.2lf\n", sum);
    } else {
        printf("Sum of elements is 0\n");
    }
    return 0;
}
// создаем наш массив
int* generateArray(int length, double min, double max) {
    int * arr = (int*)malloc(sizeof(int) * length);
    for (int i = 0 ; i < length ; i++) {
        arr[i] = (int)rand() * (max - min) / (int)RAND_MAX + min;
    }
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return arr;
}
double AverageValue(int* arr, int length) {//находим среднее значение
    double sum = 0;
    for (int i = 0; i < length; i++) {
        sum += arr[i];
    }
    return sum / length;
}
//считаем количество элементов больших среднего значение
int AmountValues(int* arr, int length, double number) {
    int amount = 0;
    for (int i = 0; i < length; i++) {
        if (arr[i] > number) {
            amount++;
        }
    }
    return amount;
}
//поиск первого отрицательного числа
int FirstNegative(int* arr, int length) {
    for (int i = 0; i < length; i++) {
        if (arr[i] < 0) {
            return i;
        }
    }
    return -1;
}
//сумма модулей чисел после первого негативного числа
double SumAbs(int* arr, int length, int startIndex) {
    double sum = 0;
    for (int i = startIndex + 1; i < length ; i++) {
        sum += abs(arr[i]);
    }
    return sum;
}
