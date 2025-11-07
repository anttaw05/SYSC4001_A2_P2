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
        case -1:
            perror("fork failed");
            exit(1);
        case 0:                                //child
            execl("./childP2", "./childP2", NULL); //send to child.c
            perror("fork failed");
            exit(1);

        default:                               //parent
            message = "This is the parent, ";
            while(1) {
        
                printf("%s", message);
                if (n % 3 == 0){
                    printf("Cycle : %d, ", n);
                }
                n++;
                printf("pid is: %d\n", getpid());
        
                sleep(3);                               //2 second delay
    }
    }
    
    exit(0);
}

