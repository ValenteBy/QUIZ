#include "include/classes/Serve.h"
#include <iostream>
#include <string>
#include <limits>

Serve::Serve(){}

void Serve::createQuestion()
{
    std::string question;
    std::string correct_answer;

    std::cout << "Digite a pergunta:\n";
    std::getline(std::cin, question);

    std::vector<std::string> current_respostas; // Inicialize um novo vetor para as respostas

    for (int i = 0; i < 4; i++)
    {
        std::string resposta;
        std::cout << "Escreva o item " << i + 1 << ":\n"; // Corrigido para mostrar o índice correto
        std::getline(std::cin, resposta);
        current_respostas.push_back(resposta); // Adiciona resposta ao vetor atual
    }

    // Limpa o buffer de entrada

    std::cout << "Digite a resposta correta:\n";
    std::getline(std::cin, correct_answer);

    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    perguntas.push_back({question, correct_answer});
    respostas.push_back(current_respostas); // Armazena as respostas
}

void Serve::createMultiplesQuestions(int &n) 
{
    for (int i = 0; i < n; i++) 
    {
        createQuestion();
    }
}

void Serve::printQuestion(int &n) const
{
    std::cout << "Pergunta: " << perguntas[n].first << std::endl;
    std::cout << "Escolha o item correto!\n";

    for (int i = 0; i < 4; i++) 
    {
        std::cout << i + 1 << " - " << respostas[n][i] << std::endl;
    }
}

bool Serve::CheckQuestion(const std::string_view &answer, int &n)
{
    if(answer == perguntas[n].second || check[n] == 0)
    {
        //check[n] = 1;
        return true;
    }
    else
        return false;

}

int Serve::getNumbersQuestions() const
{
    return perguntas.size();
}

