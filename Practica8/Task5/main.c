#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static pthread_key_t thread_key;

void *thread_func(void *arg){
    int id = *(int*) arg, i, stringsAmount, r;


    char* str = "Random number is";
    // устанавливаем значение ключа потока в str
    pthread_setspecific(thread_key, (void*) str);

    // получаем значение ключа
    char* spec = (char*) pthread_getspecific(thread_key);

    // печатаем случайное количество строк заполненых рандомным текстом и значениями
    stringsAmount = 1 + rand() % 10;
    for (i = 0; i < stringsAmount; i++){
        r = 1 + rand() % 10;
        printf("I'm thread #%d. %s %d\n", id, spec, r);
    }
    // засыпаем до конца жизни
    sleep(stringsAmount);
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        printf("Use: ./example [number]\n");
        exit(0);
    }
    srand(time(NULL));

    // здесь мы получаем массив потоков
    int n = atoi(argv[1]);
    pthread_t threads[n];
    int i;

    // ключ виден всем потокам в процессе но значение для всех разное
    pthread_key_create(&thread_key, NULL);

    // создаем n потоков с помощью thread_func каждую секунду
    for(i = 0; i < n; i++){
        if(pthread_create(&(threads[i]), NULL, &thread_func, &i) != 0){
            printf("Error\n");
            exit(0);
        }
        sleep(1);
    }

    //ждем пока все потоки закончат свою роботу
    for (i = 0; i < n; i++){
        if ((pthread_join(threads[i], NULL) != 0)) {
            fprintf(stderr, "Join error\n");
            exit(0);
        }
    }
    printf("End\n");
    return 0;
}
