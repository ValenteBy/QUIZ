#include <include/classes/Client.h>  // Inclui o cabeçalho da classe Client

// Construtor padrão da classe Client. Não realiza nenhuma ação específica.
Client::Client() {}

// Função para atribuir um ID ao cliente.
void Client::setId(int id) {
    this->id = id;  // Atribui o valor do parâmetro 'id' à variável de membro 'id' da classe.
}

// Função para retornar o ID do cliente.
int Client::getId() const {
    return id;  // Retorna o valor da variável de membro 'id'.
}

// Função para adicionar pontos ao cliente.
void Client::addPontos() {
    pontos++;  // Incrementa a pontuação do cliente em 1.
}

// Função para retornar a pontuação atual do cliente.
int Client::getPontos() const {
    return pontos;  // Retorna o valor da variável de membro 'pontos'.
}

// Função para exibir os dados do cliente na tela.
void Client::returnDados() {
    std::cout << "Aluno de ID: " << getId() << " obteve no total de pontos: " << getPontos() << std::endl; 
    // Exibe a mensagem com o ID e a pontuação do cliente usando 'getId()' e 'getPontos()'.
}