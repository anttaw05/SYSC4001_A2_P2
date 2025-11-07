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
    void* shared_memory = (void *)0;       //instance of shared mem

    //Create shared mem
    int shmid = shmget((key_t)1234, sizeof(struct Shared_data), 0666);
    if (shmid == -1){
        perror("shmget failed");
    }
    //allow access to this (parent) program
    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void*)-1){
        perror("shmmat failed");
    }

    data = (struct Shared_data*) shared_memory;

    printf("Memory attached to child.\n");

    while(data->counter <= 500){    //wait for 100

        if (data->counter % data->multiple == 0 && data->counter > 100){
            printf("Child process Cycle: %d\n", data->counter);
        }
        usleep(50000);
    }
    
    printf("Child Process now commencing\n");

    //unlink shared mem.
    if(shmdt(shared_memory) == -1){
        perror("shmdt failed");
        exit(1);
    }
    exit(0);
}