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

void remover_no(Arvore* T, char* lixo) {
    ArvNo *u = T->raiz, *p = NULL;
    while (u != NULL && strcmp(u->palavra, lixo) != 0) { // percorre a árvore até achar um nó com a chave igual a lixo ou até não achar
        if (strcmp(u->palavra, lixo) > 0) {
            u = u->esquerda;
        } else {
            u = u->direita;
        }
    }
    if (u != NULL) {
        if (u->direita != NULL) {
            p = u->direita;
            while (p->esquerda != NULL) { // percorre até achar o sucessor de u
                p = p->esquerda;
            }
            if (p != u->direita) {
                p->pai->esquerda = p->direita;
                if (p->direita != NULL) {
                    p->direita->pai = p->pai;
                }
                p->direita = u->direita;
                p->esquerda = u->esquerda;
                if (u->esquerda != NULL) {
                    u->esquerda->pai = p;
                }
                u->direita->pai = p;
                p->pai = u->pai;
            } else {
                if (u->esquerda != NULL) {
                    u->esquerda->pai = p;
                }
                p->esquerda = u->esquerda;
                p->pai = u->pai;
            }
        } else if (u->esquerda != NULL) {
            p = u->esquerda;
            while (p->direita != NULL) { // percorre até achar o predecessor de u
                p = p->direita;
            }
            if (p != u->esquerda) {
                p->pai->direita = p->esquerda;
                if (p->esquerda != NULL) {
                    p->esquerda->pai = p->pai;
                }
                p->direita = u->direita;
                p->esquerda = u->esquerda;
                u->esquerda->pai = p;
                p->pai = u->pai;
            } else {
                p->direita = u->direita;
                p->pai = u->pai;
            }
        } 
        if (u == T->raiz) {
            T->raiz = p;
        } else if (u->pai->esquerda == u) {
            u->pai->esquerda = p;
        } else {
            u->pai->direita = p;
        }

        free(u->palavra);
        free(u);
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
            free(novo);
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