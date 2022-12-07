#include <stdio.h>
#include <stdlib.h>

void showEnvironment(); // функция вывода всего окружения

int main(int argc, char **argv) {

    showEnvironment(); //показуем все переменные окружения

    if (argc == 2) { // при вводе аргумента выводим сообщение и удаляем эту переменную окружения
        printf("\nDeleting variable %s from environment\n\n", argv[1]);
        if (unsetenv(argv[1]) != 0) {//функция удаления переменной с именем NAME
            //возвращает 0 при успешном выполнении и -1 при ошибке
            fprintf(stderr, "Cannot unset %s\n", argv[1]);
            return 1;
        }
    } else { //если имя переменной не введено удаляем всё окружение
        printf("\nVariable not found\nDELETING ALL ENVIRONMENT!\n");
        clearenv(); // функция очистки всего окружения
    }

    showEnvironment(); // демонстрируем результат после проведенных действий

    printf("\n");

    return 0;
}

void showEnvironment() {
    extern char **environ;
    char **env = environ;
    if (env) {
        printf("Environment variable list start\n");
        while(*env) {
            printf("\t%s\n", *env);
            env++;
        }
        printf("Environment variable list end\n");
    } else {
        printf("Environment list is EMPTY\n");
    }
}
