#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *thread_func(void *arg){
    int n = *(int*)arg, i;

    // отключаем возможность отмены
    if (pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL) != 0)
        printf("Setcanselstate error!\n");

    // каждую секунду печатаем итерацию
    for(i = 0; i < n*2; i++){
        printf("Iteration %d\n", i);
        sleep(1);
    }
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        printf("Use: ./example [number]\n");
        exit(0);
    }

    pthread_attr_t attr;
    pthread_t thread;
    int *status;
    int n = atoi(argv[1]);

    // создаем поток с thread_func
    pthread_attr_init(&attr);
    if(pthread_create(&thread, &attr, &thread_func, &n) != 0) {
        printf("Error\n");
        exit(0);
    }
    // засыпаем на введенное количество секунд
    sleep(n);

    // попытка закрыть поток
    if (pthread_cancel(thread) != 0)
        printf("Cancel error!\n");

    // получаем статус выхода из программы
    if ((pthread_join(thread, (void*)&status) != 0)) {
        printf("Join error\n");
        exit(0);
    }

    // анализируем статус выхода и выводим результат на экран
    if (status == PTHREAD_CANCELED)
        printf("Thread canceled\n");
    else
        printf("Thread finished by itself\n");

    pthread_attr_destroy(&attr);
    printf("End\n");
    return 0;
}
