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

// Definição de uma união para o controle dos valores dos semáforos
union semun 
{
    int val;                   // Valor do semáforo
    struct semid_ds *buf;      // Buffer de status do semáforo
    unsigned short *array;     // Array de valores para semáforos
};

int main() 
{   
    // Funções de espera para simular um carregamento do jogo
    sleep(1);
    std::cout << "CARREGANDO SUA MAQUINA!!!! PACIENCIA!!\n";
    sleep(2);
    std::cout << "#####################################  GAMER QUIZ #####################################\n";
    sleep(1);

    // Criação de chaves únicas para memória compartilhada e semáforos
    key_t shm_key = ftok("memoria", 65);
    key_t sem_key = ftok("semaforo", 75);
    
    // Solicita o número de clientes (jogadores)
    std::cout << "Digite aqui o numero de alunos: ";
    int number_client = 0;
    std::cin >> number_client;

    // Criação da memória compartilhada para armazenar a classe `Serve` e os `Client` (jogadores)
    int shm_id = shmget(shm_key, sizeof(Serve) + sizeof(Client) * number_client, 0666|IPC_CREAT);
    // Criação de dois semáforos: um para controle de perguntas e outro para pontuações
    int sem_id = semget(sem_key, 2, 0666|IPC_CREAT);

    // Inicialização dos semáforos
    semun su;
    su.val = 1;  // Inicializa o semáforo de perguntas
    semctl(sem_id, 0, SETVAL, su);
    su.val = 1;  // Inicializa o semáforo de pontuação
    semctl(sem_id, 1, SETVAL, su);

    // Mapeia a memória compartilhada para as classes `Serve` e `Client`
    Serve *shared_serve = (Serve *) shmat(shm_id, nullptr, 0);
    Client *shared_clients = (Client *)(shared_serve + 1);

    // Inicialização explícita da classe `Serve` e `Client` utilizando placement new
    new (shared_serve) Serve();
    for (int i = 0; i < number_client; i++) {
        new (shared_clients + i) Client();
    }

    // Espera o semáforo de perguntas
    ConfigSem::semWait(sem_id, 0);
    sleep(1);
    std::cout << "##################################### QUESTION MACHINE ##############################\n";
    sleep(1);
    
    // Solicita a quantidade de perguntas ao usuário
    int qts_questions;
    std::cout << "Digite a quantidade de perguntas: ";
    std::cin >> qts_questions;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Cria as perguntas e respostas
    shared_serve->createMultiplesQuestions(qts_questions);
    
    std::cout << "\n";

    // Libera o semáforo de perguntas
    ConfigSem::semSignal(sem_id, 0);

    // Atribui IDs únicos para cada cliente
    for (int i = 0; i < number_client; i++) 
    {
        (shared_clients + i)->setId(i + 1);
    }
    
    // Simula um atraso antes do início do jogo
    sleep(2);
    std::cout << "#################################### START! #####################################\n";

    // Laço principal que processa todas as perguntas
    for (int i = 0; i < shared_serve->getNumbersQuestions(); i++)
    {
        for (int j = 0; j < number_client; j++)
        {
            sleep(1);
            pid_t pid = fork();  // Criação de um processo filho para cada cliente
            if (pid == 0) 
            { 
                // Código do processo filho
                ConfigSem::semWait(sem_id, 0);  // Espera o semáforo de perguntas

                std::cout << "Jogador " << (shared_clients + j)->getId() << 
                                 " (Processo ID: " << getpid() << ") respondendo a pergunta!\n";

                shared_serve->printQuestion(i);  // Imprime a pergunta
                std::cout << "Coloque sua resposta aqui: ";
                std::string resposta;
                getline(std::cin, resposta);
                
                // Verifica se a resposta está correta e se é a primeira resposta correta
                if (shared_serve->CheckQuestion(resposta, i))
                {
                    ConfigSem::semWait(sem_id, 1);  // Espera o semáforo de pontuação

                    (shared_clients + j)->addPontos();  // Adiciona pontos ao jogador
                    std::cout << "Jogador " << (shared_clients + j)->getId() << 
                                    " (Processo ID: " << getpid()  << ") acertou a questão!\n\n";
                    ConfigSem::semSignal(sem_id, 1);  // Libera o semáforo de pontuação
                } 
                else 
                {
                    std::cout << "Jogador " << (shared_clients + j)->getId() << 
                                    " (Processo ID: " << getpid()  
                                    << ") errou a questão/Demorou para responder!\n\n";
                }
                ConfigSem::semSignal(sem_id, 0);  // Libera o semáforo de perguntas
                _exit(0);  // Finaliza o processo filho
            }
        }

        // Espera a finalização de todos os processos filhos
        for (int j = 0; j < number_client; j++) 
        {
            wait(nullptr);  
        }
    }

    ConfigSem::semWait(sem_id, 0);   
    
    // Simula um atraso antes de mostrar os pontos
    sleep(3);
    std::cout << "CALMA GAFANHOTO!!! ESTAMOS GERANDO SEUS PONTOS!!\n";
    sleep(2);
    std::cout << "#################################### SCORE! #####################################\n";
    
    // Mostra a pontuação final de cada cliente
    for (int i = 0; i < number_client; i++) 
    {
        (shared_clients + i)->returnDados();
    }
    ConfigSem::semSignal(sem_id, 0);

    // Desvincula e remove a memória compartilhada e os semáforos
    shmdt(shared_serve);
    shmctl(shm_id, IPC_RMID, nullptr);
    semctl(sem_id, 0, IPC_RMID, 0);

    return 0;
}