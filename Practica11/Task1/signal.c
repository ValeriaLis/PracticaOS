#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


// Обработчик для сигналов
void signal_handler(int signalNumber) {
    printf("%d\n", signalNumber);
    if (signalNumber == SIGINT) {
        printf("Catch signal SIGINT\n");
    } else if (signalNumber == SIGTERM) {
        printf("Catch signal SIGTERM\n");
    } else {
        fprintf(stderr, "Wrong Signal\n");
        exit(EXIT_FAILURE);
    }

     exit(EXIT_SUCCESS);
}

int main() {
    setbuf(stdout, NULL);
    printf("PID: %d\n", (int)getpid());
    //регистрируем signal_handler как наш обработчик сигнала для SIGINT
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        fprintf(stderr, "It is impossible to handle SIGINT!\n");
        exit(EXIT_FAILURE);
    }
    //регистрируем signal_handler как наш обработчик сигнала для SIGTERM
    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        fprintf(stderr, "It is impossible to handle SIGTERM!\n");
        exit(EXIT_FAILURE);
    }
    //игнорировать SIGHUP
    if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {
        fprintf(stderr, "It is impossible to ignore SIGHUP!\n");
        exit(EXIT_FAILURE);
    }
    //восстанавливаем поведение по умолчанию для сигнала SIGPROF
    if (signal(SIGPROF, SIG_DFL) == SIG_ERR) {
        fprintf(stderr, "It is impossible to reset SIGPROF !\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("The process is waiting for signal\n");
        printf("Enter number signal: "); //вводим цифровой индификатор сигнала и получаем результат
        int n;
        scanf("%d", &n);
        raise(n);
        pause();
    }

    return 0;
}