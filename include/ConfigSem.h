#ifndef CONFIGSEM_H
#define CONFIGSEM_H

#include <sys/sem.h>

class ConfigSem {
public:
    static void semWait(int sem_id, int num);
    static void semSignal(int sem_id, int num);
};

#endif
