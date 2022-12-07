#include <stdio.h>
#include <stdlib.h>


int main() {
    char *env_name = "HOME_LIST_ARRAY";
    char *env_name1 = "WT_SESSION";
    char *s;
    char *s1;
    s = getenv(env_name);
    s1 = getenv(env_name1);
    printf("First variable:\n");
    if(s != NULL) {
        printf("%s = %s\n", env_name, s);
    }
    else {
        printf("this variable does not exist\n");
    }
    printf("Second variable:\n");
    if(s1 != NULL) {
        printf("%s = %s\n", env_name1, s1);
    }
    else {
        printf("this variable does not exist\n");
    }
    return 0;
}