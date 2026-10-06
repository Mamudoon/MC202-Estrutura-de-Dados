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

void buscar_no(ArvNo *raiz, char *palavra) {
    ArvNo *u = raiz;
    while (u != NULL && strcmp(u->palavra, palavra) != 0) { // percorre a árvore até achar um nó com a chave igual a palavra ou até não achar
        if (strcmp(u->palavra, palavra) > 0) {
            u = u->esquerda;
        } else {
            u = u->direita;
        }
    }
    if (u == NULL) {
        printf("%s not found\n", palavra);
    } else {
        printf("%s %ld\n", palavra, u->freq);
    }
}

void inserir_no(Arvore *T, ArvNo *novo) {
    ArvNo *u, *p;
    u = T->raiz;
    p = NULL;
    while (u != NULL) {
        p = u;
        if (strcmp(novo->palavra, u->palavra) == 0) {
            u->freq = novo->freq;
            return;
        } else if (strcmp(novo->palavra, u->palavra) < 0) {
            u = u->esquerda;
        } else {
            u = u->direita;
        }
    }
    if (p == NULL) {
        T->raiz = novo;
    } else if ((strcmp(novo->palavra, p->palavra) < 0)) {
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