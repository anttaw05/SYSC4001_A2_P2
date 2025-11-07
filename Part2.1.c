#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    char *message;
    int n = 0;
    printf("fork program starting\n");
    pid_t pid = fork();
    switch(pid){
        case -1:                   //error
            perror("fork failed");
            exit(1);
        case 0:
            message = "This is the child,";
            break;
        default:
            message = "This is the parent,";
            break;
    }
    while(1) {
        
        printf("%s", message);
        printf("Cycle : %d, with pid: %d \n", n, pid);
        n++;
        sleep(3);                               //3 second delay
    }
    exit(0);
}

