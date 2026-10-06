#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

typedef struct no_arvore ArvNo;

struct no_arvore { // os nós de uma árvore 
    ArvNo *esquerda;
    ArvNo *direita;
    ArvNo *pai;
    char* palavra;
    long freq;
};

typedef struct arvore { // começo de uma árvore 
    ArvNo *raiz;
} Arvore;

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
void inserir_no(Arvore *T, ArvNo *novo); 

/**
 * Remove nós de uma árvore;
 * (Raíz da árvore, o nó sendo removido)
 */
ArvNo* remover_no(ArvNo *raiz, ArvNo *lixo); 

/**
 * Busca nós de uma ávore;
 * (Raíz da árvore, a palavra sendo buscada)
 */
void buscar_no(ArvNo *raiz, char *palavra); 

/**
 * Imprime a ávore em ordem;
 * (Raíz da árvore)
 */
void imprimir_arv(ArvNo *raiz);

#endif