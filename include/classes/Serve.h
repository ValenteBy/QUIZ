#ifndef SERVE_H
#define SERVE_H

#include <iostream>
#include <vector>
#include <string>
#include <string_view>

#define MAX_CHECK 10 // Defina um valor máximo para o vetor check

class Serve {
private:
    std::vector<std::pair<std::string, std::string>> perguntas;
    std::vector<std::vector<std::string>> respostas;
    
    int check[MAX_CHECK] = {0}; // Inicializa o vetor check para manter o controle das respostas

public:
    Serve();
    void createQuestion();
    void createMultiplesQuestions(int &n);
    void printQuestion(int &n) const;
    bool noTime(int &n);
    bool CheckQuestion(const std::string_view &answer, int &n);
    int getNumbersQuestions() const;
    void createAutomaticQuestions();
};

#endif