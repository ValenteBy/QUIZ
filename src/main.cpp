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

union semun 
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() 
{   
    sleep(1);
    std::cout << "CARREGANDO SUA MAQUINA!!!! PACIENCIA!!\n";
    sleep(2);
    std::cout << "#####################################  GAMER QUIZ #####################################\n";
    sleep(1);

    key_t shm_key = ftok("memoria", 65);
    key_t sem_key = ftok("semaforo", 75);
    
    std::cout << "Digite aqui o numero de alunos: ";
    int number_client = 0;
    std::cin >> number_client;

    int shm_id = shmget(shm_key, sizeof(Serve) + sizeof(Client) * number_client, 0666|IPC_CREAT);
    int sem_id = semget(sem_key, 2, 0666|IPC_CREAT); // Dois semáforos: um para perguntas e outro para pontuação

    semun su;
    su.val = 1;  // Inicializa o semáforo para perguntas
    semctl(sem_id, 0, SETVAL, su);
    su.val = 1;  // Inicializa o semáforo para pontuação
    semctl(sem_id, 1, SETVAL, su);

    Serve *shared_serve = (Serve *) shmat(shm_id, nullptr, 0);
    Client *shared_clients = (Client *)(shared_serve + 1);

    new (shared_serve) Serve(); // Placement new para inicializar Serve na memória compartilhada
    for (int i = 0; i < number_client; i++) {
        new (shared_clients + i) Client(); // Placement new para Clientes
    }

    ConfigSem::semWait(sem_id, 0); // Aguarda o semáforo de perguntas
    sleep(1);
    std::cout << "##################################### QUESTION MACHINE ##############################\n";
    sleep(1);
    
    int qts_questions;
    std::cout << "Digite a quantidade de perguntas: ";
    std::cin >> qts_questions;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    shared_serve->createMultiplesQuestions(qts_questions);
    
    std::cout << "\n";

    ConfigSem::semSignal(sem_id, 0); // Libera o semáforo de perguntas

    for (int i = 0; i < number_client; i++) 
    {
        (shared_clients + i)->setId(i + 1); // Atribui o ID ao cliente
    }
    
    sleep(2);
    std::cout << "#################################### START! #####################################\n";

    for (int i = 0; i < shared_serve->getNumbersQuestions(); i++)
    {
        for (int j = 0; j < number_client; j++)
        {
            sleep(1);
            pid_t pid = fork();
            if (pid == 0) 
            { // Código do processo filho
                ConfigSem::semWait(sem_id, 0); // Aguarda o semáforo de perguntas

                std::cout << "Jogador " << (shared_clients + j)->getId() << 
                                 " (Processo ID: " << getpid() << ") respondendo a pergunta!\n";

                shared_serve->printQuestion(i);
                std::cout << "Coloque sua resposta aqui: ";
                std::string resposta;
                getline(std::cin, resposta);
                // Se for a primeira resposta correta, atribui pontos
                if (shared_serve->CheckQuestion(resposta, i))
                {
                    ConfigSem::semWait(sem_id, 1); // Aguarda o semáforo de pontuação

                    (shared_clients + j)->addPontos(); // Atribui pontos
                    std::cout << "Jogador " << (shared_clients + j)->getId() << 
                                    " (Processo ID: " << getpid()  << ") acertou a questão!\n\n";
                    ConfigSem::semSignal(sem_id, 1); // Libera o semáforo de pontuação
                } 
                else 
                {
                    std::cout << "Jogador " << (shared_clients + j)->getId() << 
                                    " (Processo ID: " << getpid()  
                                    << ") errou a questão/Demorou para responder!\n\n";
                }
                ConfigSem::semSignal(sem_id, 0); // Libera o semáforo de perguntas
                _exit(0);  // Termina o processo filho
                //std::cout << "\n";
            }
        }

        for (int j = 0; j < number_client; j++) 
        {
            wait(nullptr); // Aguarda os filhos terminarem
        }

    }

    ConfigSem::semWait(sem_id, 0);   
    
    //std::cout << "\n";
    sleep(3);
    std::cout << "CALMA GAFANHOTO!!! ESTAMOS GERANDO SEUS PONTOS!!\n";
    sleep(2);
    std::cout << "#################################### SCORE! #####################################\n";
    for (int i = 0; i < number_client; i++) 
    {
        (shared_clients + i)->returnDados();
    }
    ConfigSem::semSignal(sem_id, 0);

    shmdt(shared_serve);
    shmctl(shm_id, IPC_RMID, nullptr);
    semctl(sem_id, 0, IPC_RMID, 0); // Limpa os semáforos

    return 0;
}