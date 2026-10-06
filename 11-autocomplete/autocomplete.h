#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

typedef struct no_arvore ArvNo;
typedef struct no_lista LisNo;

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

struct no_lista { // os nós de uma lista
    ArvNo *no;
    LisNo *next;    
};

typedef struct lista { // começo de uma lista
    LisNo *head;
} Lista;

/**
 * Cria a árvore T;
 */
Arvore* criar_arv(void); 

/**
 * Cria nós;
 */
ArvNo* criar_no(char *palavra, long freq); 

/**
 * Cria a lista L;
 */
Lista* criar_lis(void);

/**
 * Adiciona nós para uma árvore;
 * (Árvore T, o nó sendo inserido)
 */
void inserir_no_arv(Arvore *T, ArvNo *novo); 

/**
 * Adiciona nós para uma lista;
 * Mantém eles em ordem decrescente;
 * (Lista L, o nó sendo inserido)
 */
void inserir_no_lis(Lista *L, LisNo *novo);

/**
 * Remove nós de uma árvore;
 * (Árvore T, a palavra que deve ser removida)
 */
void remover_no(Arvore *T, char *lixo); 

/**
 * Remove todos os nós da lista;
 * (Lista L)
 */
void remover_todos_nos_lis(Lista *L); 

/**
 * Remove todos os nós da árvore;
 * (Nó sendo removido)
 */
void remover_todos_nos_arv(ArvNo *lixo); 

/**
 * Remove a árvore;
 * (Árvore T)
 */
void remover_arv(Arvore *T); 

/**
 * Remove a lista;
 * (Lista L)
 */
void remover_lis(Lista *L); 

/**
 * Busca nós de uma ávore;
 * (Raíz da árvore, a palavra sendo buscada)
 */
void buscar_no(ArvNo *raiz, char *palavra); 

/**
 * Procura todas as palavras com o prefixo e imprime baseado na frequencia;
 * (Lista L, Árvore T, o prefixo que queremos completar, o número de elementos para imprimir)
 */
void autocompletar(Lista *L, Arvore *T, char *prefixo, long k);

/**
 * Imprime a ávore em ordem;
 * (Raíz da árvore)
 */
void imprimir_arv(ArvNo *raiz);

#endif