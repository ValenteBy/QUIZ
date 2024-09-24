#ifndef SERVE_H
#define SERVE_H

#include<iostream>
#include<vector>
#include<string>
#include<string_view>

#define MAX_CHECK

class Serve
{
private:
        std::vector<std::pair<std::string, std::string>> perguntas;
        std::vector<std::vector<std::string>> respostas;
        int check[MAX_CHECK];
    
    public:
        Serve();
        void createQuestion();

        void createMultiplesQuestions(int &n);

        void printQuestion(int &n) const;

        bool CheckQuestion(const std::string_view &answer, int &n);

        int getNumbersQuestions() const;
};

#endif