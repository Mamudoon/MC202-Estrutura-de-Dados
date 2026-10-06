#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "autocomplete.h"

Arvore* criar_arv(void) {
    Arvore *T = (Arvore*) malloc(sizeof(Arvore));
    T->raiz = NULL;
    return T;
}

ArvNo* criar_no(char *palavra, long freq) {
    ArvNo *novo = (ArvNo*) malloc(sizeof(ArvNo));
    novo->pai = NULL;
    novo->direita = NULL;
    novo->esquerda = NULL;
    char *temp = (char*) malloc((strlen(palavra) + 1)*sizeof(char));
    strcpy(temp, palavra);
    novo->palavra = temp;
    novo->freq = freq;
    return novo;
}

void inserir_no(Arvore *T, ArvNo *novo) {
    ArvNo *u, *p;
    u = T->raiz;
    p = NULL;
    while (u != NULL) {
        p = u;
        if (comparar_nos(novo, u) == 0) {
            u->freq = novo->freq;
            return;
        } else if (comparar_nos(novo, u) < 0) {
            u = u->esquerda;
        } else {
            u = u->direita;
        }
    }
    if (p == NULL) {
        T->raiz = novo;
    } else if ((comparar_nos(novo, p) < 0)) {
        p->esquerda = novo;
    } else {
        p->direita = novo;
    }
    novo->pai = p;
}

void imprimir_arv(ArvNo *raiz) {
    if (raiz != NULL) {
        imprimir_arv(raiz->esquerda);
        printf("%s ", raiz->palavra);
        imprimir_arv(raiz->direita);
    }
}

int comparar_nos(const void* a, const void *b) {
    const ArvNo *A = (ArvNo*) a;
    const ArvNo *B = (ArvNo*) b;
    return strcmp(A->palavra, B->palavra);
}