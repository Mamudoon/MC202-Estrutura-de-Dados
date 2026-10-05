#ifndef CARTESIANA_H
#define CARTESIANA_H

typedef struct no_arvore ArvNo;

typedef struct fila { // os nós de uma árvore cartesiana
    ArvNo **A;
    long first;
    long tamanho;
    long capacidade;
    long camada; // usado para que a impressão separe as camadas da árvore por linha
} Fila;

struct no_arvore { // os nós de uma árvore cartesiana
    ArvNo *esquerda;
    ArvNo *direita;
    ArvNo *pai;
    long valor;
    long rotulo; // índice no vetor
};

typedef struct arvore { // começo de uma árvore cartesiana
    ArvNo *raiz;
} Arvore;

/**
 * Adiciona nós para a árvore T, mantendo a ordenação cartesiana;
 * (Nó que está sendo inserido, o rótulo dele (indice no vetor), valor do número)
 */
ArvNo* adicionar_no_arvore(ArvNo *no, long rotulo, long valor); 

/**
 * Adiciona 1 nó ao fim da fila;
 * (Fila de nós, nó sendo inserido)
 */
void push(Fila *fila, ArvNo* no);

/**
 * Remove 1 nó no início da fila;
 * Imprime o nó removido;
 * Adiciona os dois filhos não NULLs no nó removido;
 * Conta o número de nós em cada camada;
 * (Fila de nós, tamanho da camada)
 */
long eject(Fila *fila, long k);

/**
 * Percorre uma árvore por largura (vai camada por camada);
 * (Fila de nós, raíz da árvore (pode também ser qualquer outro nó), número de nós na árvore)
 */
void percorrer_largura(Fila *fila, ArvNo *no, long n);

#endif