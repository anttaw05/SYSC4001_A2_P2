#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>

struct Shared_data{         //shared mem struct
    int multiple;
    int counter;
};

int main(){

    struct Shared_data* data; 
    void* shared_memory = (void *)0; 

    //Create shared mem
    int shmid = shmget((key_t)1234, sizeof(struct Shared_data), 0666 | IPC_CREAT);
    if (shmid == -1){
        perror("shmget failed");
    }
    //attach to this (parent) program
    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void*)-1){
        perror("shmat failed");
    }

    data = (struct Shared_data*) shared_memory;

    printf("Memory attached to parent.\n");

    data->multiple = 3;
    data->counter = 0;

    printf("fork program starting\n");

    pid_t pid = fork();
    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);
        case 0:                                //child
            execl("./childP4", "./childP4", NULL);
            perror("fork failed");
            exit(1);

        default:                               //parent
            while(data->counter < 500){
                if (data->counter % data->multiple == 0){
                    printf("Parent process Cycle: %d\n", data->counter);
                }
                data->counter++;
                usleep(50000);
            }
            //unlink shared mem
            if(shmdt(shared_memory) == -1){
                fprintf(stderr, "shmdt failed\n");
                exit(1);
            }
            if(shmctl(shmid, IPC_RMID, 0) == -1){
                fprintf(stderr, "shmctl(IPCRMID) failed\n");
                exit(1);
            }
    }
    exit(0);
}
