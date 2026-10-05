#include <stdio.h>
#include <stdlib.h>

#include "cartesiana.h"

int main(void) {
    long n, valor;
    Arvore *T = (Arvore*) malloc(sizeof(Arvore));
    Fila *F = (Fila*) malloc(sizeof(Fila));
    while(scanf(" %ld", &n) == 1) {
        if (n == 0) {
            break;
        }
        T->raiz = NULL;
        F->capacidade = n/2 + 1; // n/2 + 1 é o máximo de elementos que o vetor da fila vai ter dado n elementos. Pois tiramos 1 e adicionamos 2 (no máximo).
        F->first = 0;
        F->tamanho = 0;
        F->A = (ArvNo**) malloc((F->capacidade)*sizeof(ArvNo*));
        for (long i = 0; i < n; ++i) {
            scanf(" %ld", &valor);
            T->raiz = adicionar_no_arvore(T->raiz, i, valor);
        }
        percorrer_largura(F, T->raiz, n);
        printf("\n");
        free(F->A);
    } 
    free(F);
    free(T);
}