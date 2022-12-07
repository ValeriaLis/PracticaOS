#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *env_name = "NEW_ENV_NAME"; //придумали какую-то свою переменную окружения
    char *value = "test_program"; //придумали значение
    int set = setenv(env_name, value, 1); //функция для установки значения переменной окружения
    printf("Calling setenv with: variable %s, value %s\n", env_name, value);
    if(set != 0){ // возвращает 0 если при успешном завершении и -1 если ошибка
        printf("Name or value not correct");
    }
    printf("New value %s equals %s\n\n", env_name, value); // выводим результат
    char env[100];//создадим массив для записи
    strcpy(env, env_name);
    strcat(env, "=");
    strcat(env, value);
// функция добавляет новую или заменяет существующую переменную окружения  используя init_str
// для этого и применяем функции strcat и strcpy
    int put = putenv(env);

    if(put == 0 ){ //возвращает 0 при успешном выполнении и -1 если ошибка
        printf("The program was completed successfully\n");
        printf("Calling getenv with: variable %s, value %s\n", env_name, value);
    }
    else {
        printf("Error");
    }
    return 0;
}