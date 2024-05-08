// arvore-de-busca-binaria-balanceada.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include <iostream>

using namespace std;

struct Node {
    int value;
    int height;
    Node* left;
    Node* right;
};

class AVLTree {
private:
    Node* root;

    // Função para calcular a altura de um nó
    int getHeight(Node* node) {
        if (node == NULL)
            return 0;
        return node->height;
    }

    // Função para atualizar a altura de um nó
    void updateHeight(Node* node) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    // Função auxiliar para realizar rotações
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Função para balancear um nó
    Node* balance(Node* node) {
        int balanceFactor = getHeight(node->left) - getHeight(node->right);

        if (balanceFactor > 1 && node->value < node->left->value)
            return rotateRight(node);

        if (balanceFactor < -1 && node->value > node->right->value)
            return rotateLeft(node);

        if (balanceFactor > 1 && node->value > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balanceFactor < -1 && node->value < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Função para inserir um valor na árvore
    Node* insert(Node* node, int value) {
        if (node == NULL)
            return new Node{ value, 0, NULL, NULL};

        if (value < node->value)
            node->left = insert(node->left, value);
        else if(value > node->value)
            node->right = insert(node->right, value);
        else
            return node;

        updateHeight(node);
        return balance(node);
    }

    Node* search(Node* raiz, int num) {
        if (!raiz || raiz->value == num)
            return raiz;

        if (num < raiz->value)
            return search(raiz->left, num);
        else
            return search(raiz->right, num);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    Node* search(int num) {
        return search(root, num);
    }

    Node* getRoot()
    {
        return root;
    }

};

//função para visualizar a AVLTree
void preOrder(Node* root)
{
    if (root != NULL)
    {
        cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    std::cout << "Desafio de projeto dio.me: busca em árvores balanceadas"<<std::endl;
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(15);
    avl.insert(22);

    //Visualizar
    Node* root = avl.getRoot();
    cout << "Print AVLTree:" << endl;
    preOrder(root);
    cout << endl;

    //Teste
    cout <<"Teste:"<<endl;

    int valorBusca = 22;
    Node* result = avl.search(valorBusca);
    cout<<"Valor buscado: " << valorBusca << " Resuldado: "
        <<((result != NULL) ? "encontrado" : "nao encontrado") << endl;

}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
