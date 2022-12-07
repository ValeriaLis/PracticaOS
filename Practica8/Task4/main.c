#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_func(void *arg){
    int n = 100000; //количество иттераций
    int m = 1;
    int i;
    int x = 1;
    double p = 0;

    // разрешаем отмену
    if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) != 0)
        fprintf(stderr, "Setcanselstate error!\n");

    // настраиваем стандартную отмену
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    // вычисляем число Пи по заданию
    for(i = 0; i < n; i++){
        p += x * (1/(double)m);
        m += 2;
        x = -x;
        printf("Pi = %.5f\n", p*4);

        // инициализируем точку отмены
        pthread_testcancel();
    }
    printf("Final Pi = %.2f\n", p*4);
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

    // отмена потока
    pthread_cancel(thread);

    // получаем статус выхода
    if ((pthread_join(thread, (void*)&status) != 0)) {
        printf("Join error\n");
        exit(0);
    }

    // анализируем статус выхода
    if (status == PTHREAD_CANCELED)
        printf("Thread canceled\n"); //чем меньше ввести секунд тем вероятнее что поток будет отменен
    else
        printf("Thread finished by itself\n");

    pthread_attr_destroy(&attr);
    printf("End\n");
    return 0;
}


