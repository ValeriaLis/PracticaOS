#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int* checkArr;


// функция печатает массив
void *det_thread_func(void *arg){
    // массив всё еще пустой
    sleep(0.5);

    int n = *(int*)arg;

    // каждую секунду что-то делать
    while(1){
        // печать массива
        for (int i = 0; i < n; i++){
            printf(":%d", checkArr[i]);
        }
        printf("\n");
        sleep(1);
    }
}

void *join_thread_func(void *arg){
    int num = *(int *)arg, r;

    sleep(num);

    // помещаем рандомное число в промежутке 1..10
    // в массив на позицию num
    r = 1 + rand() % 10;
    printf("Random number %d\n", r);
    checkArr[num] = r;
    // поток идет спать на случайное количество секунд
    sleep(r);
    return NULL;
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        printf("Use: ./example [number]\n");
        exit(0);
    }

    srand(time(NULL));

    pthread_attr_t attr;
    pthread_t detached_thread, joinable_thread;
    int n = atoi(argv[1]);
    int i;
    checkArr = (int*)calloc(n, sizeof(int));


    // инициализируем attr
    pthread_attr_init(&attr);
    // attr нужен для создание отдельного потока
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(pthread_create(&detached_thread, &attr, &det_thread_func, &n) != 0){
        fprintf(stderr, "Error\n");
        exit(0);
    }

    // создадим n потоков threads
    // каждую секунду создаем новый поток с аргуметом 0..n-1
    for(i = 0; i < n; i++){
        if(pthread_create(&joinable_thread, NULL, &join_thread_func, &i) != 0){
            printf("Error\n");
            exit(0);
        }
        sleep(1);
    }

    // присоединяемся к последнему присоеденуненному потоку
    if ((pthread_join(joinable_thread, NULL) != 0)) {
        printf("Join error\n");
        exit(0);
    }

    // и заканчиваем нашу работу
    pthread_attr_destroy(&attr);
    printf("End\n");
    return 0;
}
