#ifndef CONFIG_SEM_H
#define CONFIG_SEM_H

struct ConfigSem {
    static void semWait(int sem_id);
    static void semSignal(int sem_id);
};

#endif // CONFIG_SEM_H
