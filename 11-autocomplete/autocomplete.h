#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

typedef struct no_arvore ArvNo;

struct no_arvore { // os nós de uma árvore 
    ArvNo *esquerda;
    ArvNo *direita;
    ArvNo *pai;
    int altura;
    char* palavra;
    long freq;
};

typedef struct arvore { // começo de uma árvore 
    ArvNo *raiz;
} Arvore;

typedef struct vetor{
    ArvNo **v;
    long n;
    long cap;
} Vetor;

/**
 * Cria a árvore T;
 */
Arvore* criar_arv(void); 

/**
 * Cria nós;
 */
ArvNo* criar_no(char *palavra, long freq); 

/**
 * Adiciona nós para uma árvore;
 * (Árvore T, o nó sendo inserido)
 */
void inserir_no_arv(Arvore *T, ArvNo *novo); 

/**
 * Remove nós de uma árvore;
 * (Árvore T, a palavra que deve ser removida)
 */
void remover_no(Arvore *T, char *lixo); 

/**
 * Remove a árvore;
 * (Árvore T)
 */
void remover_arv(Arvore *T);

/**
 * Busca nós de uma ávore;
 * (Raíz da árvore, a palavra sendo buscada)
 */
void buscar_no(ArvNo *raiz, char *palavra); 

/**
 * Procura todas as palavras com o prefixo e imprime baseado na frequencia;
 * (Lista L, Árvore T, o prefixo que queremos completar, o número de elementos para imprimir)
 */
void autocompletar(Arvore *T, char *prefixo, long k);

/**
 * Imprime a ávore em ordem;
 * (Raíz da árvore)
 */
void imprimir_arv(ArvNo *raiz);

#endif