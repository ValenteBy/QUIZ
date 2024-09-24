#include<iostream>
#include<vector>
#include<string>
#include<string_view>

class Client
{
    private:
        int id;
        int pontos = 0;
    public:
        Client(/* args */);

        void setId(int id){
            this->id = id;
        }
        int getId() const{
            return id;
        }

        void addPontos(){
            pontos++;
        }
        int getPontos() const{
            return pontos;
        }

        void returnDados() const{
            std::cout << "Aluno de ID: " << getId() << " obteve no total de ponto: " << getPontos() << std::endl; 
        }
    
};

Client::Client(/* args */)
{
}

