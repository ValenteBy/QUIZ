#include "include/classes/Serve.h"  // Inclui o cabeçalho da classe Serve
#include <iostream>
#include <string>
#include <limits>
#include <unistd.h>  // Inclui funções POSIX como 'sleep'

Serve::Serve() {}

void Serve::createQuestion() 
{
    std::string question;        
    std::string correct_answer;  

    std::cout << "Digite a pergunta: ";
    std::getline(std::cin, question);

    std::vector<std::string> current_respostas;

    for (int i = 0; i < 4; i++) 
    {
        std::string resposta;
        std::cout << "Escreva o item " << i + 1 << ": ";
        std::getline(std::cin, resposta);
        current_respostas.push_back(resposta);
    }

    std::cout << "Digite a resposta correta: ";
    std::getline(std::cin, correct_answer);

    perguntas.push_back({question, correct_answer});
    respostas.push_back(current_respostas);
    std::cout << "\n";
}

void Serve::createMultiplesQuestions(int &n) 
{
    for (int i = 0; i < n; i++) 
    {   
        sleep(1);  // Simula um pequeno delay entre a criação de perguntas
        std::cout << "\nCriando " << i + 1 << "a pergunta!!!\n";
        createQuestion();  // Chama a função que cria uma pergunta
    }
}

void Serve::printQuestion(int &n) const 
{
    std::cout << "Pergunta: " << perguntas[n].first << std::endl;  // Exibe o texto da pergunta
    std::cout << "Escolha o item correto:\n";  // Exibe as instruções para o jogador
    for (int i = 0; i < 4; i++) {
        std::cout << i + 1 << " - " << respostas[n][i] << std::endl;  // Exibe as 4 opções de resposta
    }
}

bool Serve::noTime(int &n)
{
    return check[n] == 1;
}

bool Serve::CheckQuestion(const std::string_view &answer, int &n)
{
    if(answer == perguntas[n].second){
        check[n] = 1;
        return true;
    }
    return false;
}

int Serve::getNumbersQuestions() const {
    return perguntas.size();  // Retorna o tamanho do vetor de perguntas
}