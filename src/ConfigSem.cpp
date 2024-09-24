#include "include/ConfigSem.h"
#include <sys/sem.h>
#include <unistd.h>


void ConfigSem::semWait(int sem_id)
{
        struct  sembuf sem_op;
        sem_op.sem_num = 0;
        sem_op.sem_op = -1;
        sem_op.sem_flg = 0;
        semop(sem_id, &sem_op, 1);
}

void ConfigSem::semSignal(int sem_id)
{
        struct sembuf sem_op;
        sem_op.sem_num = 0;
        sem_op.sem_op = 1;
        sem_op.sem_flg = 0;
        semop(sem_id, &sem_op, 1);
}
