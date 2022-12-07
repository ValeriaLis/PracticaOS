#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {
    pid_t pid;
    pid = fork();//запускаем процесс
    int status;
    if (pid == 0) {
        fprintf(stderr, "Exec error\n");
        return 0;
    } else if (pid > 0) {
        system("ps -ax"); //выводим список процессов
        wait(&status);// приводим в режим зомби
        printf("After wait method call\n");
        system("ps -ax");
        return 0;
    }
    return 0;
}