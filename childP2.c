#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int n = 0;
    pid_t pid = getpid();
    while(1){
        printf("This is the child");
        printf("Cycle : %d, ", n);
        printf("pid is: %d\n", pid);
        n--;

        sleep(3);       //1 second delay
    }
    exit(0);
}