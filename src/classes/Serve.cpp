#include<iostream>
#include<vector>
#include<string>
#include<string_view>


class Serve
{
    private:
        std::vector<std::pair<std::string, std::string>> perguntas;
        std::vector<std::vector<std::string>> respostas;
    
    public:
        Serve(/*ARGS*/);
        void createQuestion(){
            std::string question;
            std::string correct_answer;

            std::cout << "Digite a pergunta:\n";
            std::getline(std::cin, question);

            for(int i = 0; i < 4; i++){
                std::string resposta;
                std::cout << "Escreva o item " << i << ":\n";
                std::cin >> resposta;
                respostas.back().push_back(resposta);
            }
            
            std::cout << "Digite a resposta correta:\n";
            std::getline(std::cin, correct_answer);      
            perguntas.push_back({question, correct_answer});
        }

        void createMultiplesQuestions(int &n){
            for(int i = 0; i < n; i++){
                createQuestion();
            }
        }

        void printQuestion(int &n) const{
            std::cout << "Pergunta: " <<  perguntas[n].first << std::endl;

            std::cout << "Escolha o item correto!\n";
            for(int i = 0; i < 4; i++){
                std::cout << i + 1 << " - " << respostas[n][i] << std::endl;
            }
        }

        bool CheckQuestion(const std::string_view &answer, int &n) const{
            if(answer == perguntas[n].second)
                return true;
            return false;
        }

        int getNumbersQuestions() const{
            return perguntas.size();
        }
};

Serve::Serve(/* args */)
{
}
