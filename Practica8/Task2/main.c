#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_func(){
    int i = 0;

    // разрешаем отмену
    if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) != 0)
        printf("Setcanselstate error!\n");

    // настраиваем возможности
    if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL) != 0)
        printf("Setcanseltype error!\n");

    // Печатаем нашу итерацию
    while(1){
        printf("Iteration %d\n", i++);
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

    // инициализируем attr, и создадим поток с thread_func
    pthread_attr_init(&attr);
    if(pthread_create(&thread, &attr, &thread_func, NULL) != 0) {
        printf("Error\n");
        exit(0);
    }

    // засыпаем на введенное количество секунд
    sleep(n);

    // запрос на закрытие потока
    if (pthread_cancel(thread) != 0)
        printf("Cancel error!\n");

    // получаем статус выхода
    if ((pthread_join(thread, (void*)&status) != 0)) {
        printf("Join error\n");
        exit(0);
    }

    // проверяем статус выхода и выводим результат
    if (status == PTHREAD_CANCELED)
        printf("Thread canceled\n");
    else
        printf("Thread finished normaly\n");

    pthread_attr_destroy(&attr);
    printf("End\n");
    return 0;
}
