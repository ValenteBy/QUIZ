#include "include/classes/Serve.h"
#include "include/classes/Client.h"
#include "include/ConfigSem.h"

#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <wait.h>
#include <cstring>
#include <limits>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    key_t shm_key = ftok("memoria", 65);
    key_t sem_key = ftok("semaforo", 75);
    
    std::cout << "Digite aqui o numero de alunos:\n";
    int number_client = 0;
    std::cin >> number_client;

    int shm_id = shmget(shm_key, sizeof(Serve) + sizeof(Client) * number_client, 0666|IPC_CREAT);
    int sem_id = semget(sem_key, 1, 0666|IPC_CREAT);

    semun su;
    su.val = 1;  // Inicializa o semáforo com 1 (disponível)
    semctl(sem_id, 0, SETVAL, su);

    Serve *shared_serve = (Serve *) shmat(shm_id, nullptr, 0);
    Client *shared_clients = (Client *)(shared_serve + 1);

    new (shared_serve) Serve(); // Placement new para inicializar Serve na memória compartilhada
    for (int i = 0; i < number_client; i++) {
        new (shared_clients + i) Client(); // Placement new para Clientes
    }

    ConfigSem::semWait(sem_id);

    int qts_questions;
    std::cout << "Digite a quantidade de perguntas:\n";
    std::cin >> qts_questions;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    shared_serve->createMultiplesQuestions(qts_questions);

    ConfigSem::semSignal(sem_id);

    for (int i = 0; i < shared_serve->getNumbersQuestions(); i++)
    {
        (shared_clients + i)->setId(i);
        for (int j = 0; j < number_client; j++)
        {
            pid_t pid = fork();
            if (pid == 0) { // Código do processo filho
                ConfigSem::semWait(sem_id);
                std::cout << "Jogador " << (shared_clients + j)->getId() << " respondendo a pergunta!\n";
                shared_serve->printQuestion(i);
                std::string resposta;
                getline(std::cin, resposta);
                if(shared_serve->CheckQuestion(resposta, i))
                {
                    std::cout << "Acertou a questao!\n";
                    (shared_clients + j)->addPontos();
                }
                else
                {
                    std::cout << "Errou a questao\n";
                }
                ConfigSem::semSignal(sem_id);
                _exit(0);  // Termina o processo filho
            }
        }
        for (int j = 0; j < number_client; j++) 
        {
            wait(nullptr); // Aguarda os filhos terminarem
        }
    }

    ConfigSem::semWait(sem_id);
    for (int i = 0; i < number_client; i++) 
    {
        (shared_clients + i)->returnDados();
    }
    ConfigSem::semSignal(sem_id);

    shmdt(shared_serve);
    shmctl(shm_id, IPC_RMID, nullptr);
    semctl(sem_id, 0, IPC_RMID, 0); // Limpa o semáforo


    return 0;
}