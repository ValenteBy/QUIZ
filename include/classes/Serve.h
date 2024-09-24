#ifndef SERVE_H
#define SERVE_H

class Serve
{
private:
        std::vector<std::pair<std::string, std::string>> perguntas;
        std::vector<std::vector<std::string>> respostas;
    
    public:
        Serve(/*ARGS*/);
        void createQuestion();

        void createMultiplesQuestions(int &n);

        void printQuestion(int &n) const;

        bool CheckQuestion(const std::string_view &answer, int &n) const;

        int getNumbersQuestions() const;
};

Serve::Serve(/* args */)
{
}

#endif
