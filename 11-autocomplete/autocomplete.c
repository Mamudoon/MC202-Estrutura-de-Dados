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

Lista* criar_lis(void) {
    Lista *L = (Lista*) malloc(sizeof(Lista));
    L->head = NULL;
    return L;
}

void procurar(Lista *L, ArvNo *raiz, char *prefixo) { // acha todas as palavra que começam com o prefixo e adiciona para uma lista
    if (raiz != NULL) {
        if (strstr(raiz->palavra, prefixo) == raiz->palavra) {
            LisNo* novo = (LisNo*) malloc(sizeof(LisNo));
            novo->no = raiz;
            inserir_no_lis(L, novo);
        }
        procurar(L, raiz->esquerda, prefixo);
        procurar(L, raiz->direita, prefixo);
    }
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
        printf("%s not found.\n", palavra);
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

void remover_todos_nos_lis(Lista *L) {
    LisNo* lixo;
    while (L->head != NULL) {
        lixo = L->head;
        L->head = L->head->next;
        free(lixo);
    }
}

void remover_todos_nos_arv(ArvNo *raiz) {
    if (raiz != NULL) {
        remover_todos_nos_arv(raiz->esquerda);
        remover_todos_nos_arv(raiz->direita);
        free(raiz->palavra);
        free(raiz);
    }
}

void remover_arv(Arvore *T) {
    remover_todos_nos_arv(T->raiz);
    free(T);
}

void remover_lis(Lista *L) {
    remover_todos_nos_lis(L); 
    free(L);
}

void inserir_no_arv(Arvore *T, ArvNo *novo) {
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

void inserir_no_lis(Lista *L, LisNo *novo) {
    LisNo* p;
    if (L->head == NULL) {
        L->head = novo;
        return;
    }
    if (novo->no->freq > L->head->no->freq) { // se for maior que o primeiro
        novo->next = L->head;
        L->head = novo;
        return;
    } else if (novo->no->freq == L->head->no->freq) { // se vier lexicograficamente antes que o primeiro
        if (strcmp(novo->no->palavra, L->head->no->palavra) < 0) {
            novo->next = L->head;
            L->head = novo;
            return;
        }
    }

    for (p = L->head; p->next != NULL; p = p->next) {
        if (novo->no->freq > p->next->no->freq) {
            novo->next = p->next;
            p->next = novo; 
            return;
        } else if (novo->no->freq == p->next->no->freq) {
            if (strcmp(novo->no->palavra, p->next->no->palavra) < 0) {
                novo->next = p->next;
                p->next = novo; 
                return;
            }         
        }
    }
    novo->next = NULL;
    p->next = novo;
}

void autocompletar(Lista *L, Arvore *T, char *prefixo, long k) {
    int i = 0;
    ArvNo *u = T->raiz;
    while (u != NULL) { // percorre a árvore até achar um nó com a chave igual a palavra ou até não achar
        if (strstr(u->palavra, prefixo) == u->palavra) {
            break;
        }
        if (strcmp(u->palavra, prefixo) > 0) {
            u = u->esquerda;
        } else {
            u = u->direita;
        }
    }
    if (u != NULL) {
        printf("oi\n");
        procurar(L, u, prefixo); // procura a partir da primeira instância do prefixo na árvore
        for (LisNo* p = L->head; p != NULL; p = p->next) {
            if (i == k) {
                break;
            }
            printf("(%s,%ld) ", p->no->palavra, p->no->freq);
            ++i;
        }
        printf("\n");
    } else {
        printf("nothing for %s.\n", prefixo);
    }
    remover_todos_nos_lis(L);
}

void imprimir_arv(ArvNo *raiz) {
    if (raiz != NULL) {
        imprimir_arv(raiz->esquerda);
        printf("%s ", raiz->palavra);
        imprimir_arv(raiz->direita);
    }
}