#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * child_func() {//поток потомок
    for (int i = 1; i < 11; i++){
        printf("Child Thread. Iteration: %d\n", i);
        sleep(1);//засыпает на 1 секунду
    }
    return NULL;
}

int main() {
    pthread_t thread;
    int status = pthread_create(&thread, NULL, &child_func, NULL); // создаем поток
    if (status != 0){//проверям на ошибку создания
        fprintf(stderr, "Error!\n");
        return 1;
    }
    for (int i = 1; i < 11; i++) {
        printf("Main Thread. Iteration: %d\n", i);
        sleep(1);//засыпает на 1 секунду
    }

    return 0;
}
