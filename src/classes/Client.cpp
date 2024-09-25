#include <include/classes/Client.h>

Client::Client() {}

void Client::setId(int id) {
    this->id = id;
}

int Client::getId() const {
    return id;
}

void Client::addPontos() {
    pontos++;
}

int Client::getPontos() const {
    return pontos;
}

void Client::returnDados() {
    std::cout << "Aluno de ID: " << getId() << " obteve no total de pontos: " << getPontos() << std::endl; 
}
