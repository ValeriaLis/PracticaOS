#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	printf("PID -> %d\n", getpid()); //индификатор текущего процесса
	printf("Parent PID -> %d\n", getppid()); //идификатор родительского процесса
	printf("Group PID -> %d\n", getpgrp()); //индификатор группы вызывающего процесса
	printf("Real user ID -> %d\n", getuid());//реальный индификатор владельца вызывающего процесса
	printf("Effective user ID -> %d\n", geteuid());//значение атрибута eUID
	printf("Group ID -> %d\n", getgid());// реальный индификатор группы вызывающего процесса
	printf("Effective group ID -> %d\n", getegid());//значение атрибута eGID

	return 0;
}
