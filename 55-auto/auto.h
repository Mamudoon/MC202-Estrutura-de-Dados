#ifndef AUTO_H
#define AUTO_H

typedef struct no No;
struct no {
    int buscado;
    int valor;
    No *next;
};

typedef struct lista {
    No *primeiro;
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
 Busca na lista L o número valor;
**/
void buscar(Lista *L, int valor, Tipo tipo);

/**
 Adiciona o valor na lista L
 **/
void adicionar(Lista *L, int valor, Tipo tipo);

/**
 Move o no na lista L
 **/
void mover(Lista *L, No *move, Tipo tipo);

#endif