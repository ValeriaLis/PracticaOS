#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    char* c;
    if(argc == 1){ // если запускаем без аргументов, выводим подсказку
        printf("getopt test\n");
        printf("For help use:\n");
        printf("$ ./example -h\n");
        return 0;
    }
    while ((opt = getopt(argc, argv, "ho:c")) != -1) { //когда все опции обработаны возвращает -1
        // ":" означает что опция "о" будет принимать аргумент
        switch (opt) {
            case 'h':
                printf("The program has three options\n"
                       "-> -h - help on using the program and stop program\n"
                       "-> -o out_file_name - non-standard output file name\n"
                       "-> -c - special mode of operation\n");
                break;
            case 'o':
                //что б выполнить необходимо ./example -o Hello
                c = (char*) optarg; // принимает строковое значение аргумента опции
                printf("Input -o -> %s\n", c);
                break;
            case 'c':
                printf("Special mod is ON\n");
                break;
            default:
                exit(1);
        }
    }
    return 0;
}