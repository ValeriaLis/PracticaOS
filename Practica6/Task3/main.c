#include <stdio.h>
#include <unistd.h>
#include <wait.h>
//задание А
int main() {
    setbuf(stdout, NULL);
    printf("Main PID %d\n", getpid());
    int local = 0;
    pid_t pid[2];
    pid[0] = fork(); //первый вызов fork
    if (pid[0] == 0) { //потомок 1fork
        local++;
        printf("\nLocal variable = %d\nAddress = %p\nParent PID = %d\nOwn PID = %d\n", local, &local, getppid(), getpid());
        pid_t pidd[2];
        pidd[0] = fork(); //второй вызов fork в процессе потомке
        if (pidd[0] == 0) { //потомок 2fork
            local++;
            printf("\nLocal variable = %d\nAddress = %p\nParent PID = %d\nOwn PID = %d\n", local, &local, getppid(), getpid());
        } else if (pidd[0] > 0) {//родитель 2fork
            pidd[1] = fork();// третий вызов fork
            if (pidd[1] == 0) { // потомок 3fork
                local++;
                printf("\nLocal variable = %d\nAddress = %p\nParent PID = %d\nOwn PID = %d\n", local, &local, getppid(), getpid());
            } else if (pidd[1] > 0) { // родитель 3fork
                printf("Second Main IDs1 = %d IDs2 = %d\n", pidd[0], pidd[1]);
                wait(NULL);
            }
        }
    } else if (pid[0] > 0) { //родитель 1fork
        pid[1] = fork(); // второй вызов fork в родительском процессе
        if (pid[1] == 0) { // потомок 2fork
            local++;
            printf("\nLocal variable = %d\nAddress = %p\nParent PID = %d\nOwn PID = %d\n", local, &local, getppid(), getpid());
            pid_t pidd[2];
            pidd[0] = fork(); //третий вызов fork
            if (pidd[0] == 0) { //потомок 3fork
                local++;
                printf("\nLocal variable = %d\nAddress = %p\nParent PID = %d\nOwn PID = %d\n", local, &local, getppid(), getpid());
            } else if (pidd[0] > 0) { // родитель 3fork
                pidd[1] = fork();//четвертый вызов fork
                if (pidd[1] == 0) { //потомок 4fork
                    local++;
                    printf("\nLocal variable = %d\nAddress = %p\nParent PID = %d\nOwn PID = %d\n", local, &local, getppid(), getpid());
                } else if (pidd[1] > 0) {//родитель 4fork
                    printf("Second Main IDs1 = %d IDs2 = %d\n", pidd[0], pidd[1]);
                }
            }
        } else if (pid[1] > 0) { //родитель 2fork
            printf("Main ID1 = %d ID2 = %d\n", pid[0], pid[1]);
            wait(NULL);
        }
    }

    return 0;
}