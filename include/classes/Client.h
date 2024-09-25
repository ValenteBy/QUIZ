#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>

class Client {
private:
    int id = 0;
    int pontos = 0;

public:
    Client();
    void setId(int id);
    int getId() const;
    void addPontos();
    int getPontos() const;
    void returnDados();
};

#endif
