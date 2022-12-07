#include <stdio.h>
#include <pthread.h>

struct thread_arg {
    char * name;
    char * str;
    int num;
};

void * func(void * arg) { //вивод потоков на экран n-ое количество раз
    struct thread_arg thread = *(struct thread_arg *) arg;
    for (int i = 0; i < thread.num; i++) {
        fprintf(stderr, "%s. %s %d\n", thread.name, thread.str, i+1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3, thread4;//имеем 4 различных потока
    struct thread_arg thrarg1 = {"Thread1", "| UKR - UAN | ", 6};
    struct thread_arg thrarg2 = {"Thread2", "| RUS - RUB | ", 3};
    struct thread_arg thrarg3 = {"Thread3", "| GERM - EUR  | ", 3};
    struct thread_arg thrarg4 = {"Thread4", "| ENG - GBP  | ", 2};
    if (pthread_create(&thread1, NULL, &func, &thrarg1) != 0) { //проверка всех потоков
        fprintf(stderr, "Error : Thread1\n");
        return 1;
    }
    if (pthread_create(&thread2, NULL, &func, &thrarg2) != 0) {
        fprintf(stderr, "Error : Thread2\n");
        return 1;
    }
    if (pthread_create(&thread3, NULL, &func, &thrarg3) != 0) {
        fprintf(stderr, "Error : Thread3\n");
        return 1;
    }
    if (pthread_create(&thread4, NULL, &func, &thrarg4) != 0) {
        fprintf(stderr, "Error : Thread4\n");
        return 1;
    }
  while(1);

    return 0;
}
