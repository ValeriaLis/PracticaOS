#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
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
    static struct sigaction act;

    setbuf(stdout, NULL);
    printf("PID: %d\n", (int)getpid());

    act.sa_handler = signal_handler;
    //регистрируем signal_handler как наш обработчик сигнала для SIGINT
    if (sigaction(SIGINT, &act, NULL) == -1) {//обработка ошибок
        fprintf(stderr, "It is impossible to handle SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    if (sigaction(SIGTERM, &act, NULL) == -1) {
        fprintf(stderr, "It is impossible to handle SIGTERM!\n");
        exit(EXIT_FAILURE);
    }
    //регистрируем signal_handler как наш обработчик сигнала для SIGTERM
    act.sa_handler = SIG_DFL;
    if (sigaction(SIGPROF, &act, NULL) == -1) {
        fprintf(stderr, "It is impossible to reset SIGPROF!\n");
        exit(EXIT_FAILURE);
    }
    //игнорировать SIGHUP
    act.sa_handler = SIG_IGN;
    if (sigaction(SIGHUP, &act, NULL) == -1) {
        fprintf(stderr, "It is impossible to ignore SIGHUP!\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("The process is waiting for signal\n");
        printf("Enter number signal: ");//вводим цифровой индификатор сигнала и получаем результат
        int n;
        scanf("%d", &n);
        raise(n);
        pause();
    }

    fprintf(stderr, "The program is finished\n");

    return EXIT_SUCCESS;
}