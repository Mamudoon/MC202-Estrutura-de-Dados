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

int buscar(Lista *L, int valor, Tipo tipo) {
    No *p;
    int primeiro = 0, comparacoes = 1, achou = 0;
    if (L->primeiro->valor == valor) {
        L->primeiro->buscado += 1;
        primeiro = achou = 1;
    } else {
        primeiro = 0;
        for (p = L->primeiro->next; p != NULL; p = p->next) {
            comparacoes += 1;
            if (p->valor == valor) {
                achou = 1;
                break;
            }
        }
    } 
    
    switch (tipo) {
        case SEQ:
            if (achou != 1) {
                adicionar(L, valor, SEQ);
            }
            return comparacoes;
            break;
        
        case MTF:
            if (achou == 1) {
                if (primeiro != 1) {
                    mover(L, p, MTF);
                }
            } else {
                adicionar(L, valor, MTF);
            }
            return comparacoes;
            break;
        
        case TRANSPOSE:
            if (achou == 1) {
                if (primeiro != 1) {
                    mover(L, p, TRANSPOSE);
                }
            } else {
                adicionar(L, valor, TRANSPOSE);
            }
            return comparacoes;
            break;
        
        case COUNT:
            if (achou == 1) {
                if (primeiro != 1) {
                    p->buscado += 1;
                    mover(L, p, COUNT);
                }
            } else {
                adicionar(L, valor, COUNT);
            }
            return comparacoes;
            break;

        default:
            break;
    }
}

void mover(Lista *L, No *p, Tipo tipo) {
    int moveu = 0;
    switch (tipo) {
        case MTF:
            if (p == L->ultimo) {
                L->ultimo = p->prev;
                p->prev->next = NULL;
                p->next = L->primeiro;
                p->prev = NULL;
                L->primeiro->prev = p;
                L->primeiro = p;
            } else {
                p->next->prev = p->prev;
                p->prev->next = p->next;
                p->next = L->primeiro;
                p->prev = NULL;
                L->primeiro->prev = p;
                L->primeiro = p;
            }
            break;
        
        case TRANSPOSE:
            if (p == L->ultimo) {
                p->prev->next = NULL;
                L->ultimo = p->prev;
                p->next = p->prev;
                p->prev = p->prev->prev;
                p->prev->next->prev = p;
                p->prev->next = p;
            } else if (p->prev == L->primeiro) {
                p->next->prev = p->prev;
                p->prev->next = p->next;
                p->next = L->primeiro;
                L->primeiro->prev = p;
                p->prev = NULL;
                L->primeiro = p;
            } else {
                p->next->prev = p->prev;
                p->prev->next = p->next;
                p->next = p->prev;
                p->prev = p->prev->prev;
                p->prev->next->prev = p;
                p->prev->next = p;
            }
            break;
        
        case COUNT:
            if (p == L->ultimo) {
                L->ultimo = p->prev;
                p->prev->next = p->next;
            } else {
                p->next->prev = p->prev;
                p->prev->next = p->next;
            }

            if (L->primeiro->buscado <= p->buscado) {
                p->next = L->primeiro;
                L->primeiro->prev = p;
                p->prev = NULL;
                L->primeiro = p;
                moveu = 1;
            } else {
                for (No* a = L->primeiro->next; a != NULL; a = a->next) {
                    if (a->buscado <= p->buscado) {
                        p->prev = a->prev;
                        a->prev->next = p;
                        p->next = a;
                        a->prev = p;
                        moveu = 1;
                        break;
                    }
                }
            }
            if (moveu != 1) {
                L->ultimo->next = p;
                p->prev = L->ultimo;
                p->next = NULL;
                L->ultimo = p;
            }
            break;

        default:
            break;
    }
}

void remover_tudo(Lista *L) {
    No* lixo;
    while (L->primeiro != NULL) {
        lixo = L->primeiro;
        L->primeiro = L->primeiro->next;
        free(lixo);
    }
    free(L);
} 

void adicionar(Lista *L, int valor, Tipo tipo) {
    int adicionou = 0;
    No* novo = (No*) malloc(sizeof(No));
    novo->buscado = 0;
    novo->valor = valor;
    switch (tipo) {
        case SEQ:
            if (L->primeiro == NULL) {
                L->primeiro = novo;
                L->ultimo = novo;
                novo->next = NULL;
                novo->prev = NULL;
            } else {
                novo->prev = L->ultimo;
                L->ultimo->next = novo; 
                novo->next = NULL;
                L->ultimo = novo;
            }
            break;
        
        case MTF:
            novo->next = L->primeiro;
            L->primeiro->prev = novo;
            novo->prev = NULL;
            L->primeiro = novo;
            break;
        
        case TRANSPOSE:
            novo->next = L->primeiro;
            L->primeiro->prev = novo;
            novo->prev = NULL;
            L->primeiro = novo;
            break;
        
        case COUNT:
            if (L->primeiro->buscado <= 1) {
                novo->next = L->primeiro;
                L->primeiro->prev = novo;
                novo->prev = NULL;
                L->primeiro = novo;
                adicionou = 1;
            } else {
                for (No* p = L->primeiro; p != NULL; p = p->next) {
                    if (p->next->buscado <= 1) {
                        novo->prev = p;
                        novo->next = p->next;
                        p->next->prev = novo;
                        p->next = novo;
                        adicionou = 1;
                        break;
                    }
                }
            }
            if (adicionou != 1) {
                L->ultimo->next = novo;
                novo->prev = L->ultimo;
                novo->next = NULL;
                L->ultimo = novo;                
            }
            break;

        default:
            break;
    }
}