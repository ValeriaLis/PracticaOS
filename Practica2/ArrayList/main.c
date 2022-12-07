#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//генерируем массив случайных чисел в диапазоне
int* get_array(int size, int* arr) {
    srand(time(NULL));
    for(int i = 0; i < size; i++) {
        arr[i] = rand() % 10;
    }
    return arr;
}
//функция для добавления элемента в конец
int* add(int item, int sizeOfArray, int* arr) {
    arr[sizeOfArray] = item;
    return arr;
}
//вставка в середину массива
int* insert(int item, int size, int* arr) {
    for(int i = size-1; i >= size / 2; i--){
        arr[i + 1] = arr[i];
    }
    arr[size/2] = item;
    return arr;
}
//размер массива
int get_size(int size){
    return size;
}
//удаление элемента за его индексом
int* delete(int index, int size, int *arr) {
    for(int i = 0; i < size; i++) {
        if(i >= index-1) {
            arr[i] = arr[i + 1];
        }
    }
    return arr;
}
//замена элемента по индексу
int* change(int index, int new_element, int* arr) {
    arr[index-1] = new_element;
    return arr;
}
//получить заданое значение
int get_element(int index, int* arr) {
    return arr[index-1];
}
//функция для вывода массива
void print(int size, int* arr) {
    printf(" [ ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]");
}
void menu(){    //меню
    printf("\n1. Add(item)\n");
    printf("2. Insert(ID, item)\n");
    printf("3. Size()\n");
    printf("4. delete(ID)\n");
    printf("5. Set(ID, item)\n");
    printf("6. Get(ID)\n");
    printf("0. Exit\n");
}
int main() {
    int size = 7;
    int* arr = (int*)malloc(size * sizeof(int));
    arr = get_array(size, arr);
    int flag;
    int item = 0;
    int new_element = 0;

    while(1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &flag);
        switch(flag) {
            case 1:
                printf("Enter the item: ");
                scanf("%d", &item);
                printf("Array before -> ");
                print(size, arr);
                add(item, size, arr);
                size = size + 1;
                printf("\nArray after ->");
                print(size, arr);
                break;
            case 2:
                printf("Enter the item: ");
                scanf("%d", &item);
                printf("Array before -> ");
                print(size, arr);
                size = size + 1;
                insert(item, size, arr);
                printf("\nArray after ->");
                print(size, arr);
                break;
            case 3:
                printf("Number of elements = %d", get_size(size));
                break;
            case 4:
                printf("Enter the index: ");
                scanf("%d", &item);
                printf("Array before -> ");
                print(size, arr);
                delete(item, size, arr);
                size = size-1;
                printf("\nArray after ->");
                print(size, arr);
                break;
            case 5:
                printf("Enter the index: ");
                scanf("%d", &item);
                printf("Enter the value of the element by index: ");
                scanf("%d", &new_element);
                printf("Array before -> ");
                print(size, arr);
                change(item, new_element, arr);
                printf("\nArray after ->");
                print(size, arr);
                break;
            case 6:
                printf("Enter the index: ");
                scanf("%d", &item);
                printf("Your element = %d\n", get_element(item, arr));
                print(size, arr);
                break;
            case 0:
                free(arr);
                exit(0);
            default:
                printf("Invalid choice!!!\n");
        }
    }
}