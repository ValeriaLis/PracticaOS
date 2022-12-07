#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    int i, status;
    pid_t pid;
    void my_handler(int signo, siginfo_t *si, void *ucontext);

    static struct sigaction act;
    sigval_t value;

    switch (pid = fork()) {
        case -1: //Ошибка
            perror("task4");
            exit(EXIT_FAILURE);

        case 0: //процесс потомок
            // передаем оброботчик сигнала SIGUSR1 в родительский процесс
            sigfillset(&act.sa_mask);
            act.sa_flags = SA_SIGINFO;
            act.sa_sigaction = my_handler;
            sigaction(SIGUSR1, &act, NULL);
            while(1) {
                pause();
            }
            break;
        default: //родительский процесс
            for (i = 1; i <= 10; i++) {
                sleep(1);
                value.sival_int = 404 + i;
                if (sigqueue(pid, SIGUSR1, value) != 0) {
                    perror("synchro");
                    exit(EXIT_FAILURE);
                }
            }
            sleep(2);
            kill(pid, SIGTERM);
            waitpid(pid, &status, 0);
    }

    return EXIT_SUCCESS;
}

void my_handler(int signo, siginfo_t *si, void *ucontext) {
    extern const char *const sys_siglist[];
    printf("Signal %d (%s). Data from parent process: %d\n", si->si_signo, sys_siglist[si->si_signo], si->si_value.sival_int);
}