// desafio_dio_cpp_II.cpp : 
// Este arquivo contém a função 'main', onde execução do programa começa e termina.

#include <iostream>

using namespace std;

// Função para exibir o tabuleiro
void exibirTabuleiro(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << tabuleiro[i][j] << " ";
        }
        cout << endl;
    }
}

// Função para verificar se alguém ganhou
bool verificarVitoria(char tabuleiro[3][3], char jogador) {
    // Verificar linhas, colunas e diagonais
    for (int i = 0; i < 3; ++i) {
        if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) {
            return true;
        }
        if (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador) {
            return true;
        }
    }
    if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) {
        return true;
    }
    if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador) {
        return true;
    }
    return false;
}

int main() {
    char tabuleiro[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    char jogador = 'X';
    int linha, coluna;

    do {
        exibirTabuleiro(tabuleiro);
        cout << "Jogador " << jogador << ", digite a linha (1-3) e a coluna (1-3): ";
        cin >> linha >> coluna;
        linha--;
        coluna--;

        if (tabuleiro[linha][coluna] == ' ') {
            tabuleiro[linha][coluna] = jogador;
            if (verificarVitoria(tabuleiro, jogador)) {
                cout << "Jogador " << jogador << " venceu!" << endl;
                break;
            }
            jogador = (jogador == 'X') ? 'O' : 'X';
        }
        else {
            cout << "Essa posição já está ocupada. Tente novamente." << endl;
        }
    } while (true);

    exibirTabuleiro(tabuleiro);
    return 0;
}

// Jogo criado atraves do Copilot (https://copilot.microsoft.com/) como desafio de projeto do curso Formação C/C++ Developer da dio.me.