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
    int val;               // Valor do semáforo (1) disponivel (-1) Nao disponivel
    struct semid_ds *buf;  // Buffer de status do semáforo usado para retornar getpid() e quantidade de semaforos
    unsigned short *array; // Array de valores para semáforos
};

int main() 
{   
    sleep(1);
    std::cout << "CARREGANDO SUA MAQUINA!!!! PACIENCIA!!\n";
    sleep(2);
    std::cout << "\n################################# GAMER QUIZ #####################################\n\n";
    sleep(1);

    key_t shm_key = ftok("memoria", 65);
    key_t sem_key = ftok("semaforo", 75);
    
    std::cout << "Digite aqui o numero de alunos: ";
    int number_client = 0;
    std::cin >> number_client;

    int shm_id = shmget(shm_key, sizeof(Serve) + sizeof(Client) * number_client, 0666|IPC_CREAT);
    
    int sem_id = semget(sem_key, 2, 0666|IPC_CREAT);

    semun su;
    su.val = 1;  // Inicializa o semáforo de perguntas
    semctl(sem_id, 0, SETVAL, su);
    su.val = 1;  // Inicializa o semáforo de pontuação
    semctl(sem_id, 1, SETVAL, su);

    Serve *shared_serve = (Serve *) shmat(shm_id, nullptr, 0);
    Client *shared_clients = (Client *)(shared_serve + 1);

    new (shared_serve) Serve();
    for (int i = 0; i < number_client; i++) 
    {
        new (shared_clients + i) Client();
    }

    ConfigSem::semWait(sem_id, 0);
    sleep(1);
    std::cout << "\n############################## QUESTION MACHINE ##################################\n\n";
    sleep(1);
    
    int qts_questions;
    std::cout << "Digite a quantidade de perguntas: ";
    std::cin >> qts_questions;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    shared_serve->createMultiplesQuestions(qts_questions);
    
    std::cout << "\n";

    ConfigSem::semSignal(sem_id, 0);

    for (int i = 0; i < number_client; i++) 
    {
        (shared_clients + i)->setId(i + 1);
    }
    
    sleep(2);
    std::cout << "\n#################################### START! ######################################\n\n";

    for (int i = 0; i < shared_serve->getNumbersQuestions(); i++)
    {
        for (int j = 0; j < number_client; j++)
        {
            sleep(1);
            pid_t pid = fork();  
            if (pid == 0) 
            { 
                ConfigSem::semWait(sem_id, 0);  

                std::cout << "Jogador " << (shared_clients + j)->getId() << 
                                 " (Processo ID: " << getpid() << ") respondendo a pergunta!\n";

                shared_serve->printQuestion(i);  
                std::cout << "Coloque sua resposta aqui: ";
                std::string resposta;
                getline(std::cin, resposta);
                
                if (shared_serve->noTime(i)){
                    std::cout << "Demorou para responder!!!\n\n";
                }
                else if (shared_serve->CheckQuestion(resposta, i))
                {
                    ConfigSem::semWait(sem_id, 1);

                    (shared_clients + j)->addPontos();
                    std::cout << "Jogador " << (shared_clients + j)->getId() 
                                    << " (Processo ID: " << getpid()  << ") acertou a questão!\n\n";
                    ConfigSem::semSignal(sem_id, 1);
                } 
                else 
                {
                    std::cout << "Jogador " << (shared_clients + j)->getId()
                                    << " (Processo ID: " << getpid()
                                    << ") errou a questão!!\n\n";
                }
                ConfigSem::semSignal(sem_id, 0);  // Libera o semáforo de perguntas
                _exit(0);  // Finaliza o processo filho
            }
        }

        for (int j = 0; j < number_client; j++) 
        {
            wait(nullptr);  
        }
    }

    ConfigSem::semWait(sem_id, 0);
    
    sleep(3);
    std::cout << "CALMA GAFANHOTO!!! ESTAMOS GERANDO SEUS PONTOS!!\n";
    sleep(2);
    std::cout << "\n#################################### SCORE! ######################################\n";

    for (int i = 0; i < number_client; i++) 
    {
        (shared_clients + i)->returnDados();
    }
    ConfigSem::semSignal(sem_id, 0); 

    shmdt(shared_serve);
    shmctl(shm_id, IPC_RMID, nullptr);
    semctl(sem_id, 0, IPC_RMID, 0);

    return 0;
}
