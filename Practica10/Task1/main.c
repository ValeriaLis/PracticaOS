#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define PRODUCED 1
#define CONSUMED 1

int *buffer, ind;
sem_t lock, empty_items, full_items;

void initialize(int size){ //инициализируем семафор
    int check;
    ind = 0;
    buffer = malloc(sizeof(int) * size);//создаем наш буфер чисел

    check = sem_init(&lock, 0, 1);
    if (check != 0) {
        perror("Semaphore initialization failed.");
        exit(EXIT_FAILURE);
    }

    check = sem_init(&empty_items, 0, size);
    if (check != 0) {
        perror("Semaphore initialization failed.");
        exit(EXIT_FAILURE);
    }

    check = sem_init(&full_items, 0, 0);
    if (check != 0){
        perror("Semaphore initialization failed.");
        exit(EXIT_FAILURE);
    }
}

void *producer(void *arg){ //генерируем случайные числа для Производителя
    srand(time(NULL));
    while(1){
        int value = (rand() % 10) + 1;
        sem_wait(&empty_items);
        sem_wait(&lock);
        printf("Produced: %d\n", value);
        buffer[ind] = value; // обязательно помещаем их в буфер
        ind++; //увеличивая размер заполненности
        sem_post(&lock);
        sem_post(&full_items);
        sleep(2); //производитель спит 2 секунды
    }
}

void *consumer(void *arg){//функция для Потребителя
    while(1) {
        sem_wait(&full_items); //семафор забирает 1 элемент, если в буфере пусто мы ожидаем появление товара
        sem_wait(&lock);
        ind--;
        printf("Consumed: %d\n", buffer[ind]);//показываем что мы забрали
        buffer[ind] = 0;
        sem_post(&lock);
        sem_post(&empty_items);
        sleep(2);//так же засыпаем на 2 секунды, можно поставить меньше на работу программы это не повлияет
    }
}

void *print(void *arg){//функция для вывода нашего буфера
    int size = *(int*) arg;
    int i;
    while (1) {
        for (i = 0; i < size; i++){
            printf("%d ", buffer[i]);
        }
        printf("\n");
        sleep(1);
    }
}

int main(int argc, char **argv){
    pthread_t *pr, *cn;
    int size = 10;
    if (argc > 1){//получаем значение из консоли которое равно кол-ву элементов
        size = atoi(argv[1]);
    }
    initialize(size);

    pthread_attr_t attr;
    pthread_t pt;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&pt, &attr, &print, &size);
    pthread_attr_destroy(&attr);

    pr = malloc(sizeof(pthread_t) * PRODUCED);
    cn = malloc(sizeof(pthread_t) * CONSUMED);

    for (int i = 0; i < PRODUCED; i++){//создаем первый поток
        if (pthread_create(&pr[i], NULL, &producer, NULL) != 0) {
            fprintf(stderr, "Error (thread)\n");
            return 1;
        }
    }

    for (int i = 0; i < CONSUMED; i++){//создаем второй поток
        if (pthread_create(&cn[i], NULL, &consumer, NULL) != 0) {
            fprintf(stderr, "Error (thread)\n");
            return 1;
        }
    }

    sleep(15);//засыпаем на 15 секунд

    for(int i = 0; i < PRODUCED; ++i){
        pthread_cancel(pr[i]);
        if (pthread_join(pr[i], NULL) != 0) {
            printf("Error\n");
        }
    }

    for(int i = 0; i < CONSUMED; ++i){
        pthread_cancel(cn[i]);
        if (pthread_join(cn[i], NULL) != 0) {
            printf("Error\n");
        }
    }

    pthread_cancel(pt);//отменяем поток производитель

    free(pr);
    free(cn);
    free(buffer);
    sem_destroy(&lock);
    sem_destroy(&empty_items);
    sem_destroy(&full_items);
    return 0;
}
