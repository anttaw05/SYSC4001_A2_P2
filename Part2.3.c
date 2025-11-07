#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    char *message;
    int n = 0;
    printf("fork program starting\n");
    pid_t pid = fork();
    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);
        case 0:                                //child
            while (n > -500){
                printf("This is the child, ");
                printf("Cycle : %d, with pid: %d \n", n, getpid());
                n--;
                usleep(5000);
            }
            exit(0); 

        default:                               //parent
            printf("Waiting for child termination\n");
            wait(NULL);
            printf("Child terminated.\n");
    }
    exit(0);
}
