#include <stdio.h>
#include <stdlib.h>

#include "auto.h"
/**
 Faz com que os valores de 1 até n sejam adicionados para a lista
 **/
void criar(Lista *L, int n) {
    for (int i = 1; i <= n; ++i) {
        adicionar(L, i, SEQ);
    }
}

void buscar(Lista *L, int valor, Tipo tipo) {
    
}

void adicionar(Lista *L, int valor, Tipo tipo) {
    No* novo = (No*) malloc(sizeof(No));
    novo->buscado = 1;
    novo->valor = valor;
    switch (tipo) {
        case SEQ:
            if (L->primeiro == NULL) {
                L->primeiro = novo;
                novo->next = NULL;
            } else {
                for (No* p = L->primeiro; p != NULL; p = p->next) {
                    if (p->next == NULL) {
                        p->next = novo;
                        novo->next = NULL;
                        break;
                    }
                }
            }
            break;
        
        case MTF:
            novo->next = L->primeiro;
            L->primeiro = novo;
            break;
        
        case TRANSPOSE:
            novo->next = L->primeiro;
            L->primeiro = novo;
            break;
        
        case COUNT:

            break;

        default:
            break;
    }
}