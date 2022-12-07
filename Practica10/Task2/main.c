#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
//условные переменные используються с мьютексом
int value;
pthread_cond_t cond;
pthread_mutex_t mutex;
int flag;

void initialize(){//инициализируем мьютекс и условную переменную
    value = 0;
    flag = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}

void *produce(void *arg){//функция производитель
    srand(time(NULL));
    while(1){
        int tmp = (rand() % 10) + 1;//генерируем ему случайные числа
        pthread_mutex_lock(&mutex);//блокируем мьютекс
        value = tmp;
        printf("Produced: %d\n", value);
        flag = 1;//защищаем флаг
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);//разблокируем мьютекс
        sleep(1);
    }
}

void *consume(void *arg){//потребитель
    while(1){
        pthread_mutex_lock(&mutex);//блокируем мьютекс
        while(!flag){//если производитель ничего не добавил ждем
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);//разблокируем мьютекс
        printf("Consumed: %d\n", value);
        value = 0;
        flag = 0;
    }
}

int main(int argc, char **arcv){
    pthread_t producer, consumer;
// создаем наши рабочие потоки
    if (pthread_create(&producer, NULL, &produce, NULL) != 0) {
        fprintf(stderr, "Error (thread)\n");
        return 1;
    }

    if (pthread_create(&consumer, NULL, &consume, NULL) != 0) {
        fprintf(stderr, "Error (thread)\n");
        return 1;
    }

    sleep(10);//засыпаем

    pthread_cancel(producer);//закрываем производителя
    if (pthread_join(producer, NULL) != 0) {
        printf("Error\n");
    }

    pthread_cancel(consumer);//закрываем потребителя
    if (pthread_join(consumer, NULL) != 0) {
        printf("Error\n");
    }
//завершаем работу 
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
