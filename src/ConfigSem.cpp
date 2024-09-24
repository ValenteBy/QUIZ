#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <wait.h>
#include <cstring> 

struct ConfigSem{
    void semWait(int sem_id){
        struct  sembuf sem_op;
        sem_op.sem_num = 0;
        sem_op.sem_op = -1;
        sem_op.sem_flg = 0;
        semop(sem_id, &sem_op, 1);
    }
    
    void semSignal(int sem_id){
        struct sembuf sem_op;
        sem_op.sem_num = 0;
        sem_op.sem_op = 1;
        sem_op.sem_flg = 0;
        semop(sem_id, &sem_op, 1);
    }
};