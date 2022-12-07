#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

int main() {
    char host_buffer[1024];
    gethostname(host_buffer, sizeof(host_buffer)); //функция записывает имя машины в строку host_name

    printf("Host name -> %s\n", host_buffer);

    struct utsname info;
    uname(&info);//функция записывает инфу о компьютере в структуру
    //далее взаимодействие с этой же структурой для получения информации
    printf("System name -> %s\n", info.sysname);
    printf("Node name -> %s\n", info.nodename);
    printf("Release -> %s\n", info.release);
    printf("Version -> %s\n", info.version);
    printf("Machine -> %s\n", info.machine);
    printf("Host id -> %ld\n", gethostid()); // функция для возврата уникольного знаячения
    return 0;
}