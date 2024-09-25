#include "include/classes/Serve.h"  // Inclui o cabeçalho da classe Serve
#include <iostream>
#include <string>
#include <limits>
#include <unistd.h>  // Inclui funções POSIX como 'sleep'

// Construtor padrão da classe Serve. Atualmente não realiza nenhuma ação específica.
Serve::Serve() {}

// Função responsável por criar uma única pergunta, coletando o texto da pergunta e as opções de resposta.
void Serve::createQuestion() 
{
    std::string question;        // Armazena o texto da pergunta
    std::string correct_answer;  // Armazena a resposta correta

    // Coleta a pergunta do usuário
    std::cout << "Digite a pergunta: ";
    std::getline(std::cin, question);

    // Vetor que armazena as 4 opções de resposta
    std::vector<std::string> current_respostas;

    // Laço que coleta 4 opções de resposta para cada pergunta
    for (int i = 0; i < 4; i++) 
    {
        std::string resposta;
        std::cout << "Escreva o item " << i + 1 << ": ";
        std::getline(std::cin, resposta);
        current_respostas.push_back(resposta);
    }

    // Coleta a resposta correta do usuário
    std::cout << "Digite a resposta correta: ";
    std::getline(std::cin, correct_answer);

    // Armazena a pergunta e a resposta correta em um par, e as opções de resposta no vetor de respostas
    perguntas.push_back({question, correct_answer});
    respostas.push_back(current_respostas);
}

// Função responsável por criar múltiplas perguntas. Recebe como parâmetro o número de perguntas a serem criadas.
void Serve::createMultiplesQuestions(int &n) 
{
    // Laço que itera n vezes, criando uma pergunta em cada iteração
    for (int i = 0; i < n; i++) 
    {   
        sleep(1);  // Simula um pequeno delay entre a criação de perguntas
        std::cout << "Criando " << i + 1 << "a pergunta!!!\n";
        createQuestion();  // Chama a função que cria uma pergunta
    }
}

// Função que cria automaticamente um conjunto de perguntas e respostas pré-definidas
// void Serve::createAutomaticQuestions() {
//     // Cada bloco de perguntas/respostas pré-definidas é armazenado no vetor 'perguntas' e 'respostas'
    
//     perguntas.push_back({"Qual é o nome do famoso encanador da Nintendo?", "Mario"});
//     respostas.push_back({"Luigi", "Wario", "Toad", "Mario"});  // Resposta correta: Mario (última posição)

//     perguntas.push_back({"Qual console foi lançado primeiro?", "Sega Genesis"});
//     respostas.push_back({"Sega Genesis", "PlayStation", "Nintendo 64", "Xbox"});  // Resposta correta: Sega Genesis

//     perguntas.push_back({"Em que ano o jogo Pac-Man foi lançado?", "1980"});
//     respostas.push_back({"1985", "1990", "1980", "1995"});  // Resposta correta: 1980

//     perguntas.push_back({"Qual é o nome do jogo de luta da Capcom que apresenta personagens como Ryu e Chun-Li?", "Street Fighter"});
//     respostas.push_back({"Mortal Kombat", "Street Fighter", "Tekken", "King of Fighters"});  // Resposta correta: Street Fighter

//     perguntas.push_back({"Qual jogo é conhecido como 'O pai dos jogos de plataforma'?", "Super Mario Bros."});
//     respostas.push_back({"Donkey Kong", "Super Mario Bros.", "Sonic the Hedgehog", "Mega Man"});  // Resposta correta: Super Mario Bros.

//     perguntas.push_back({"Em qual jogo você controla um personagem chamado Link?", "The Legend of Zelda"});
//     respostas.push_back({"Castlevania", "Final Fantasy", "The Legend of Zelda", "Metroid"});  // Resposta correta: The Legend of Zelda

//     perguntas.push_back({"Qual foi o primeiro jogo a usar gráficos 3D?", "Wolfenstein 3D"});
//     respostas.push_back({"Doom", "Wolfenstein 3D", "Duke Nukem 3D", "Quake"});  // Resposta correta: Wolfenstein 3D

//     perguntas.push_back({"Qual é o nome do famoso jogo de quebra-cabeça com blocos coloridos que caem?", "Tetris"});
//     respostas.push_back({"Puzzle Bobble", "Columns", "Tetris", "Bejeweled"});  // Resposta correta: Tetris

//     perguntas.push_back({"Qual jogo tem uma franquia famosa que envolve corridas de kart com personagens da Nintendo?", "Mario Kart"});
//     respostas.push_back({"Diddy Kong Racing", "Mario Kart", "Crash Team Racing", "Sonic Drift"});  // Resposta correta: Mario Kart

//     perguntas.push_back({"Qual jogo de tiro em primeira pessoa foi desenvolvido pela id Software e revolucionou o gênero?", "Doom"});
//     respostas.push_back({"Counter-Strike", "Halo", "Doom", "Half-Life"});  // Resposta correta: Doom
// }

// Função para exibir a pergunta e suas respectivas opções de resposta na tela
void Serve::printQuestion(int &n) const {
    std::cout << "Pergunta: " << perguntas[n].first << std::endl;  // Exibe o texto da pergunta
    std::cout << "Escolha o item correto:\n";  // Exibe as instruções para o jogador
    for (int i = 0; i < 4; i++) {
        std::cout << i + 1 << " - " << respostas[n][i] << std::endl;  // Exibe as 4 opções de resposta
    }
}

// Função que verifica se a resposta fornecida está correta para a pergunta atual
bool Serve::CheckQuestion(const std::string_view &answer, int &n) 
{
    // Se a resposta estiver correta e a pergunta ainda não foi respondida corretamente, retorna true
    if (answer == perguntas[n].second && check[n] == 0) 
    {
        check[n] = 1;  // Marca que a pergunta foi respondida corretamente, para não contabilizar duas vezes
        return true;
    }
    return false;
}

// Função que retorna o número total de perguntas armazenadas
int Serve::getNumbersQuestions() const {
    return perguntas.size();  // Retorna o tamanho do vetor de perguntas
}