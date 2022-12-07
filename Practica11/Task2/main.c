#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
#define BELLS "\007\007\007"  // Звуковой сигнал

sig_atomic_t alarm_flag = FALSE;

// Сигнал SIGALRM handler
void setFlag(int sig) {
    alarm_flag = TRUE;
}

int main(int argc, char **argv) {
    int nsecs, j;
    pid_t pid;
    static struct sigaction act;

    if (argc < 2) {
        fprintf(stderr, "Wrong strating command.\nMust be: ./example [number]\n");
        exit(EXIT_FAILURE);
    }

    if ((nsecs = atoi(argv[1])) <= 0) {
        fprintf(stderr, "Task2: invalid time\n");
        exit(EXIT_FAILURE);
    }

    switch(pid = fork()) {
        case -1: // Error
            perror("Task2");
            exit(EXIT_FAILURE);
        case 0: // Процесс потомок
            break;
        default: // Родительский процесс
            printf("Chile process Task2 with id %d is working\n", pid);
            printf("Wait a signal after %d second\n", nsecs);
            exit(EXIT_SUCCESS);
    }

    // Таймер handler
    act.sa_handler = setFlag;
    sigaction(SIGALRM, &act, NULL);

    // Таймер
    alarm(nsecs);

    // останавливаемся пока не поймаем сигнал
    pause();

    // когда словим сигнал выведем сообщение
    if (alarm_flag == TRUE) {
        printf(BELLS);
        for (j = 2; j < argc; j++) {
            printf("%s ", argv[j]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
