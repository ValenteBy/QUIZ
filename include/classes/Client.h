#ifndef CLIENT_H
#define CLIENT_H

class Client
{
    private:
        int id;
        bool pontos;
    /* data */
    public:
        Client(/* args */);
        void setId(int id);

        int getId() const;

        void addPontos() const;

        int getPontos() const;

        void returnDados() const;
};

Client::Client(/* args */)
{
}

#endif