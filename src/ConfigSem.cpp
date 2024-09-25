#include "include/ConfigSem.h"
#include <sys/sem.h> 
#include <unistd.h>

// Função para esperar (decrementar) o semáforo especificado
void ConfigSem::semWait(int sem_id, int num) {
    struct sembuf sem_op;
    sem_op.sem_num = num; // Especifica qual semáforo usar
    sem_op.sem_op = -1;   // Decrementa o semáforo
    sem_op.sem_flg = 0;
    semop(sem_id, &sem_op, 1);
}

// Função para sinalizar (incrementar) o semáforo especificado
void ConfigSem::semSignal(int sem_id, int num) {
    struct sembuf sem_op;
    sem_op.sem_num = num; // Especifica qual semáforo usar
    sem_op.sem_op = 1;    // Incrementa o semáforo
    sem_op.sem_flg = 0;
    semop(sem_id, &sem_op, 1);
}
