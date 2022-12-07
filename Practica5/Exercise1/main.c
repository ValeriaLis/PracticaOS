#include <stdio.h>
#include <stdlib.h>

int main() {
    extern char **environ;
    for (int i = 0; i < sizeof(environ); ++i) { //вывод переменных окружения
        printf("%s\n", environ[i]);
    }
    return 0;
}