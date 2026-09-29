#ifndef AUTO_H
#define AUTO_H

typedef struct no No;
struct no {
    int buscado;
    int valor;
    No *next;
    No *prev;
};

typedef struct lista {
    No *primeiro;
    No *ultimo;
} Lista;

typedef enum tipo {
    SEQ,
    MTF,
    TRANSPOSE,
    COUNT
} Tipo;

/**
 Cria uma lista com n números de 1 até n
 **/
void criar(Lista *L, int n);

/** 
 Busca na lista L o número valor, retorna o número de comparações feitas até achar;
**/
int buscar(Lista *L, int valor, Tipo tipo);

/**
 Libera toda a memória alocada.
 **/
void remover_tudo(Lista *L);

/**
 Adiciona o valor na lista L
 **/
void adicionar(Lista *L, int valor, Tipo tipo);

/**
 Move o no na lista L
 **/
void mover(Lista *L, No *move, Tipo tipo);

#endif