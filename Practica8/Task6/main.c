#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void cleanHandler(){
    // бесполезный текст
    fprintf(stderr, "Clean handler started its work.\n");
}

void *thread_func(){
    int i = 0;
    // выводим какую-то информацию в поток вывода 10 раз каждую секунду
    while(1){
        printf("Iteration %d\n", i++);
        sleep(1);
        if (i == 10)
            break;
    }
    // Выводим какой-то снова бесполезный текст
    fprintf(stderr, "Thread finished its work\n");
    return NULL;
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        printf("Use: ./example [number]\n");
        exit(0);
    }
    
    pthread_t thread;
    void* res;
    int n = atoi(argv[1]);

    // создаем поток с помощью thread_func
    if(pthread_create(&thread, NULL, &thread_func, NULL) != 0) {
        fprintf(stderr, "Error\n");
        exit(0);
    }

    // засыпаем на введенное количество секунд
    sleep(n);

    // помещаем функцию cleanHandler на вверх стека что автоматически выполнит эту функцию
    // когда поток будет закрыт с помощью pthread_cancel или pthread_exit
    pthread_cleanup_push(cleanHandler, NULL);

        // отмена потока
        pthread_cancel(thread);

    pthread_cleanup_pop(1);

    pthread_join(thread, &res);

    // выводим текст, если поток будет отменент
    if (res == PTHREAD_CANCELED)
        fprintf(stderr, "Main thread finished thread's work\n");

    printf("End\n");
    return 0;
}
