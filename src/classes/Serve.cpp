#include "include/classes/Serve.h"
#include <iostream>
#include <string>
#include <limits>
#include <unistd.h>

Serve::Serve() {}

void Serve::createQuestion() 
{
    std::string question;
    std::string correct_answer;

    std::cout << "Digite a pergunta: ";
    std::getline(std::cin, question);
    std::vector<std::string> current_respostas;

    for (int i = 0; i < 4; i++) 
    {
        std::string resposta;
        std::cout << "Escreva o item " << i + 1 << ": ";
        std::getline(std::cin, resposta);
        current_respostas.push_back(resposta);
    }

    std::cout << "Digite a resposta correta: ";
    std::getline(std::cin, correct_answer);

    perguntas.push_back({question, correct_answer});
    respostas.push_back(current_respostas);
}

void Serve::createMultiplesQuestions(int &n) 
{
    for (int i = 0; i < n; i++) 
    {   
        sleep(1);
        std::cout << "CRIANDO " << i + 1 << "a pergunta!!!\n";
        createQuestion();
    }
}

void Serve::createAutomaticQuestions() {
    // Perguntas e respostas automáticas
    perguntas.push_back({"Qual é o nome do famoso encanador da Nintendo?", "Mario"});
    respostas.push_back({"Luigi", "Wario", "Toad", "Mario"}); // Mario na última posição

    perguntas.push_back({"Qual console foi lançado primeiro?", "Sega Genesis"});
    respostas.push_back({"Sega Genesis", "PlayStation", "Nintendo 64", "Xbox"}); // Sega Genesis na primeira posição

    perguntas.push_back({"Em que ano o jogo Pac-Man foi lançado?", "1980"});
    respostas.push_back({"1985", "1990", "1980", "1995"}); // 1980 na terceira posição

    perguntas.push_back({"Qual é o nome do jogo de luta da Capcom que apresenta personagens como Ryu e Chun-Li?", "Street Fighter"});
    respostas.push_back({"Mortal Kombat", "Street Fighter", "Tekken", "King of Fighters"}); // Street Fighter na segunda posição

    perguntas.push_back({"Qual jogo é conhecido como 'O pai dos jogos de plataforma'?", "Super Mario Bros."});
    respostas.push_back({"Donkey Kong", "Super Mario Bros.", "Sonic the Hedgehog", "Mega Man"}); // Super Mario Bros. na segunda posição

    perguntas.push_back({"Em qual jogo você controla um personagem chamado Link?", "The Legend of Zelda"});
    respostas.push_back({"Castlevania", "Final Fantasy", "The Legend of Zelda", "Metroid"}); // The Legend of Zelda na terceira posição

    perguntas.push_back({"Qual foi o primeiro jogo a usar gráficos 3D?", "Wolfenstein 3D"});
    respostas.push_back({"Doom", "Wolfenstein 3D", "Duke Nukem 3D", "Quake"}); // Wolfenstein 3D na segunda posição

    perguntas.push_back({"Qual é o nome do famoso jogo de quebra-cabeça com blocos coloridos que caem?", "Tetris"});
    respostas.push_back({"Puzzle Bobble", "Columns", "Tetris", "Bejeweled"}); // Tetris na terceira posição

    perguntas.push_back({"Qual jogo tem uma franquia famosa que envolve corridas de kart com personagens da Nintendo?", "Mario Kart"});
    respostas.push_back({"Diddy Kong Racing", "Mario Kart", "Crash Team Racing", "Sonic Drift"}); // Mario Kart na segunda posição

    perguntas.push_back({"Qual jogo de tiro em primeira pessoa foi desenvolvido pela id Software e revolucionou o gênero?", "Doom"});
    respostas.push_back({"Counter-Strike", "Halo", "Doom", "Half-Life"}); // Doom na terceira posição
}

void Serve::printQuestion(int &n) const {
    std::cout << "Pergunta: " << perguntas[n].first << std::endl;
    std::cout << "Escolha o item correto:\n";
    for (int i = 0; i < 4; i++) {
        std::cout << i + 1 << " - " << respostas[n][i] << std::endl;
    }
}

bool Serve::CheckQuestion(const std::string_view &answer, int &n) 
{
    if (answer == perguntas[n].second && check[n] == 0) 
    {
        check[n] = 1; // Marca que a pergunta foi respondida corretamente
        return true;
    }
    return false;
}

int Serve::getNumbersQuestions() const {
    return perguntas.size();
}