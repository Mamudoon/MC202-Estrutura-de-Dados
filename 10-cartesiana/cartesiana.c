#include <stdio.h>
#include <stdlib.h>

#include "cartesiana.h"

ArvNo* adicionar_no_arvore(ArvNo *no, long rotulo, long valor) {
    ArvNo *raiz = no;
    ArvNo *novo = (ArvNo*) malloc(sizeof(ArvNo));
    novo->rotulo = rotulo;
    novo->valor = valor;
    if (raiz == NULL) {
        novo->pai = NULL;
        novo->direita = NULL;
        novo->esquerda = NULL;
        return novo;
    }

    for (ArvNo *p = no; p != NULL; p = p->direita) { 
        if (valor < p->valor) { // significa que o valor do novo nó é menor que o p atual, e por isso fica em cima dele, pois é o mínimo
            novo->pai = p->pai;
            p->pai = novo;
            novo->esquerda = p;
            novo->direita = NULL;
            if (novo->pai != NULL) { // no caso do nó que está sendo inserido não ocupar a raiz
                novo->pai->direita = novo;
                return raiz;
            }
            return novo; // só é alcançado se o nó adicionado for a nova raiz
        }
        if (p->direita == NULL) { // significa que ele o valor do novo nó é maior que todos os que vieram desde a raíz
            p->direita = novo;
            novo->pai = p;
            novo->esquerda = NULL;
            novo->direita = NULL;
            return raiz;
        }
    }
    
    return raiz;
}

void push(Fila *fila, ArvNo *no) {
    fila->A[(fila->first + fila->tamanho)%fila->capacidade] = no;
    fila->tamanho += 1;
}

long eject(Fila *fila, long k) {
    ArvNo *no = fila->A[fila->first];
    ArvNo *esquerda = no->esquerda;
    ArvNo *direita = no->direita;
    if (no != NULL) {
        --fila->camada;
        printf("%ld ", no->rotulo);
        free(no);
        if (esquerda != NULL) {
            ++k;
            push(fila, esquerda);
        }
        if (direita != NULL) {
            ++k;
            push(fila, direita);
        }
        fila->tamanho -= 1;
        fila->first = (fila->first + 1)%fila->capacidade;
    }
    if (fila->camada == 0) { // indica que a camada atual acabou
        printf("\n");
        fila->camada = k; // atualiza o valor para o número de elementos da próxima camada
        k = 0; // volta a contar do 0 o número de elementos da próxima camada;
    }
    return k;
}

void percorrer_largura(Fila *fila, ArvNo *no, long n) {
    long k = 0; // número de elementos na próxima camada;
    fila->camada = 1;
    push(fila, no);
    for (long i = 0; i < n; ++i) {
        k = eject(fila, k);
    }
}