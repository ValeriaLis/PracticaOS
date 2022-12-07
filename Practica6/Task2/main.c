#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#define SEC 5

int main(void) {
    pid_t pid; //специально определенный тип для fork, являеться целым значением
    printf("Fork start:\n");
    pid = fork(); //испльзуют для создания нового процесса которые есть копией вызывающего процесса
    int count1 = 0, count2 = 0;
    time(NULL);
    clock_t begin = clock();
    clock_t end;
    double time;
    while (1) {
        end = clock();
        time = (double)(end - begin) / CLOCKS_PER_SEC;
        if (time >= SEC)
            break;
        if (pid == 0) { //потомок возвращает значение 0
            count1++;
        } else if (pid > 0) { //родительский процесс позвращает не нулевой pid
            count2++;
        } else { // ошибка вызова fork, потомок не создан
            printf("Error!\n");
        }
    }
    //вывод результата отработки программы
    printf("\nParent process: %d | Child process:  %d | time = %d sec\n", count2, count1, (int)time);
    return 0;
}